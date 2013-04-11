#ifndef __makra_set
#define __makra_set

#include <avr/io.h>

#define NULL ((void*) 0)

#define bit_set(var,bitno) ((var) |= 1<<(bitno))
#define testbit_on(data,bitno) ((data>>bitno)&0x01)
#define bit_clr(var,bitno) ((var) &= ~(1<<(bitno)))
#define bit_inv(var,bitno) var^=(1<<bitno)

#define INPUT 0
#define OUTPUT 1

	//                      Bit access of IO bits:
	struct bits {
		uint8_t b0:1;
		uint8_t b1:1;
		uint8_t b2:1;
		uint8_t b3:1;
		uint8_t b4:1;
		uint8_t b5:1;
		uint8_t b6:1;
		uint8_t b7:1;
	} __attribute__((__packed__));

	#define SBIT_(port,pin)	((*(volatile struct bits*)&port).b##pin)
	#define SBIT(x,y)	SBIT_(x,y)

#endif
