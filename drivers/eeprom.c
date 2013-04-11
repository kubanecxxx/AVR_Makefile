#include "eeprom.h"

unsigned short eepromAddressBuffer[8];
unsigned char eepromDataBuffer[8];
unsigned char eepromIndex=0;
unsigned char eepromIndex2=0;

unsigned char eepromWrite(unsigned short address, unsigned char data){
	cli();
	if (eepromIndex != eepromIndex2 || bit_is_clear(EECR,EERIE)){
		bit_clr(EECR,EERIE);
		sei();

		eepromAddressBuffer[eepromIndex]=address;
		eepromDataBuffer[eepromIndex]=data;

		eepromIndex++;

		if (eepromIndex==sizeof(eepromDataBuffer)){
			eepromIndex=0;
		} 
	} else {
		sei();
		return 1;		//buffer overflow
	}

	bit_set(EECR,EERIE);

	return 0;
}

ISR(EE_READY_vect){

	EEDR=eepromDataBuffer[eepromIndex2];
	EEAR=eepromAddressBuffer[eepromIndex2];

	bit_set(EECR,EEMWE);
	bit_set(EECR,EEWE);

	eepromIndex2++;

	if(eepromIndex2 == sizeof(eepromDataBuffer))
		eepromIndex2=0;
	
	if(eepromIndex2 == eepromIndex){
		bit_clr(EECR,EERIE);
	}
}


unsigned char eepromRead (unsigned short address){
	while(bit_is_set(EECR,EEWE));
	EEAR=address;
	bit_set(EECR,EERE);

	return EEDR;
}

void eepromWriteStupid(unsigned short address, unsigned char data){
	EEAR=address;
	EEDR=data;
	bit_set(EECR,EEMWE);
	bit_set(EECR,EEWE);
	while(bit_is_set(EECR,EEWE));
	bit_clr(EECR,EEMWE);
}

