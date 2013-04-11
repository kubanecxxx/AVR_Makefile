/*
 * scheduler.h
 *
 *  Created on: 11.4.2013
 *      Author: kubanec
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "makra.h"

typedef enum {ONCE, PERIODIC} sh_t;
typedef uint32_t systime_t;
typedef void * arg_t;
typedef void (*method_t)(arg_t);

typedef struct delay_t delay_t;

struct delay_t
{
	method_t method;
	arg_t arg;
	systime_t period;
	systime_t last;
	sh_t type;
	delay_t * next;
};

void shFillStruct(delay_t * del, method_t method, arg_t arg, systime_t cycles, sh_t type);
void shRegisterStruct(delay_t * del);
void shUnregisterStruct(delay_t * del);
void shPlay(void);
void shInit(systime_t * systemTick);
void shRearm(delay_t * del);

#endif /* SCHEDULER_H_ */
