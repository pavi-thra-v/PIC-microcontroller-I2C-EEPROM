#include <xc.h>
#include "configuration.h"
#include "I2C_EEPROM_Task.h"
#define _XTAL_FREQ 6000000

void main(void) {

    I2C_Master_Init(100000);
    unsigned int Add1 = 0x0023, Add2 = 0x0028, Add3 = 0x0036; 
    unsigned char Data1 = 'A', Data2 = 'B', Data3 = 'C';     
    
    EEPROM_Write(Add1, Data1); // Write "A" : 0x41 @ 0x0023
    __delay_ms(1000);                  // Wait tWR=1000ms For Write To Complete
    EEPROM_Write(Add2, Data2); // Write "B" : 0x42 @ 0x0028
    __delay_ms(1000);                  // Wait tWR=1000ms For Write To Complete
    EEPROM_Write(Add3, Data3);     // Write "C" : 0x43 @ 0x0036
    __delay_ms(1000);                  // Wait tWR=1000ms For Write To Complete
    
    TRISD = 0x00;   
    PORTD = EEPROM_Read(Add1);  // Should Read 0x41 "A"
    __delay_ms(2000);
    PORTD=0x00;
    __delay_ms(2000);
    PORTD = EEPROM_Read(Add2);  // Should Read 0x42 "B"
    __delay_ms(2000);
    PORTD=0x00;
    __delay_ms(2000);
    PORTD = EEPROM_Read(Add3);    // Should Read 0x43 "C"
    __delay_ms(2000);
    PORTD=0x00;
    while(1)
    {
        
    }
    return;
}
