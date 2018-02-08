/*
 * interrupts.c
 *
 * Created: 08-Feb-18 04:33:25 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
*******************************************************************/
{
	DDRD = 0xFF;	
	DDRC = 0x00;	

	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x06;			// Enable INT1 & INT2
	

	sei();

	while (1)
	{

	}

	return 1;
}