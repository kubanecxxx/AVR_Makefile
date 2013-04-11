#ifndef eeprom_set
#define eeprom_set

#include "main.h"

//Prototypes
unsigned char eepromWrite(unsigned short address, unsigned char data);
void eepromWriteStupid(unsigned short address, unsigned char data);
unsigned char eepromRead(unsigned short address);


#endif

