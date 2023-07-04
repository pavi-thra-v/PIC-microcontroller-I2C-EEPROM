

#include <xc.h>
#include "I2C_EEPROM_Task.h"
#define _XTAL_FREQ 6000000
#define EEPROM_Address_R  0xA1 //1010 0001
#define EEPROM_Address_W  0xA0 //1010 0000
//---------------[ I2C Routines ]-------------------
//--------------------------------------------------
void I2C_Master_Init(const unsigned long baud)
{
    SSPCON = 0b00101000; //28
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*baud))-1;
    SSPSTAT = 0;
    TRISC3 = 1; //SCL set as input
    TRISC4 = 1; //SDL set as input
}
void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;
}
void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;
}
void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;
}
unsigned char I2C_Master_Write(unsigned char data)
{
    I2C_Master_Wait();
    SSPBUF = data;
    while(!SSPIF);  // Wait Until Completion
	SSPIF = 0;
    return ACKSTAT;
}
unsigned char I2C_Read_Byte(void)
{
    //---[ Receive & Return A Byte ]---
	I2C_Master_Wait();
    RCEN = 1;		  // Enable & Start Reception
	while(!SSPIF);	  // Wait Until Completion
	SSPIF = 0;		  // Clear The Interrupt Flag Bit
    I2C_Master_Wait();
    return SSPBUF;	  // Return The Received Byte
}
void I2C_ACK(void)
{
	ACKDT = 0;			// 0 -> ACK
	I2C_Master_Wait();
    ACKEN = 1;			// Send ACK
}
void I2C_NACK(void)
{
	ACKDT = 1;			// 1 -> NACK
    I2C_Master_Wait();
	ACKEN = 1;			// Send NACK
}

// EEPROM Write Byte
void EEPROM_Write(unsigned int add, unsigned char data)
{
   I2C_Master_Start();
   
   // Wait Until EEPROM Is IDLE
   while(I2C_Master_Write(EEPROM_Address_W))
     I2C_Master_RepeatedStart();
    I2C_Master_Write(add>>8);
    I2C_Master_Write((unsigned char)add);
    I2C_Master_Write(data);
    I2C_Master_Stop();
}

//---[ Byte Read ]---
unsigned char EEPROM_Read(unsigned int add)
{
   unsigned char Data;
   I2C_Master_Start();
   
   // Wait Until EEPROM Is IDLE
   while(I2C_Master_Write(EEPROM_Address_W))
     I2C_Master_RepeatedStart();
   I2C_Master_Write(add>>8);
   I2C_Master_Write((unsigned char)add);
   I2C_Master_RepeatedStart();

   I2C_Master_Write(EEPROM_Address_R);
   Data = I2C_Read_Byte();
   I2C_NACK();
   I2C_Master_Stop();
   
   return Data;
}
