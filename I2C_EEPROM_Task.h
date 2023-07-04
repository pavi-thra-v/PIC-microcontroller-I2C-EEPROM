//Function Declarations are present here

//For I2C
void I2C_Master_Init(const unsigned long baud);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_ACK();
void I2C_NACK();
unsigned char I2C_Master_Write(unsigned char data);
unsigned char I2C_Read_Byte(void);

//For EEPROM
void EEPROM_Write(unsigned int add, unsigned char data);
unsigned char EEPROM_Read(unsigned int add);

