/*
 * scheduler.c
 *
 *  Created on: 11.4.2013
 *      Author: kubanec
 */

#include "scheduler.h"

static void shRunMethod(delay_t * method);
static const systime_t * sysTime;
static delay_t * first = NULL;
static delay_t * last ;



void shInit(systime_t * sysTick)
{
	sysTime = sysTick;
	last = first;
}

void shPlay(void)
{
//projet celej seznam
	//zavolat shRunMethod
	delay_t * del = first;
	while(del)
	{
		shRunMethod(del);
		del = del->next;
	}
}

void shFillStruct(delay_t * del, method_t method, arg_t arg, systime_t cycles, sh_t type)
{
	del->method = method;
	del->arg = arg;
	del->type = type;
	del->next = NULL;
	del->period = cycles;
	del->last = 0;
}

/*
 * nastavit posledni pointer na tuhle strukturu
 */
void shRegisterStruct(delay_t * del)
{
	if (first == NULL)
		first = del;
	if (last)
		last->next = del;
	last = del;
	del->last = *sysTime;
}

void shUnregisterStruct(delay_t * del)
{
	delay_t * temp = first;

	if (del == first)
	{
		first = del->next;
		return;
	}

	while(temp)
	{
		if (temp->next == del)
		{
			temp->next = del->next;
			if (del == last)
				last = temp;

			return;
		}
		temp = temp->next;
	}
}

void shRunMethod(delay_t * method)
{
	if(*sysTime - method->last > method->period)
	{
		method->last = *sysTime;
		method->method(method->arg);
		if (method->type == ONCE)
			shUnregisterStruct(method);
	}
}
