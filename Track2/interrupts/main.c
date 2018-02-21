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

ISR( INT1_vect )
{
	PORTC = PORTC << 1;
}

ISR( INT2_vect )
{
	PORTC = PORTC >> 1;
}


/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
*******************************************************************/
{
	DDRD = 0x00;	
	DDRC = 0xFF;	

	EICRA |= 0x3C;			// INT1 falling edge, INT2 rising edge
	EIMSK |= 0x06;			// Enable INT1 & INT2
	
	sei();
	
	PORTC = 0x01;

	while (1 == 1)
	{

	}

	return 1;
}