#include "main.h"
#include "scheduler.h"
#include "uart.h"

//aby to neházelo warning že v eepromě nic neni
unsigned char EEMEM __nic = 60;

static void mcu_init(void);
static void timer0_init(void);
static void blik(arg_t arg);

systime_t time = 0;

#define MS2ST(x) (x/2)

//main code here
int main(void)
{
	mcu_init();

	static delay_t del;
	static delay_t del2;

	shFillStruct(&del, blik, (arg_t) 5, MS2ST(100), PERIODIC);
	shFillStruct(&del2, blik, (arg_t) 7, MS2ST(700), PERIODIC);

	shRegisterStruct(&del);
	shRegisterStruct(&del2);

	while (1)
	{
		shPlay();
	}

	return 1;
}

//init code here
void mcu_init(void)
{
	DDRD |= _BV(7) | _BV(5);
	PORTD ^= _BV(7);

	timer0_init();
	MCUCR = 0b00000000;
	GICR = 0b00000000;
	TIMSK = 0b00000001;
	SFIOR = 0b00000000;

	shInit(&time);

	uart_init(UART_BAUD_SELECT(9600,F_CPU));

	sei();
}

ISR(TIMER0_OVF_vect)
{
	time++;
}

void timer0_init(void)
{
	 TCCR0 = 0x00; // Stop the timer
	 TCNT0 = 0x00; // 8-bit counter
	 //interrupt 2ms na 8MHz
	 TCCR0 = 0b00001011;
}

void blik(arg_t arg)
{
	PORTD ^= _BV(((uint16_t) arg));
}
