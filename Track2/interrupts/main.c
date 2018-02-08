/*
 * interrupts.c
 *
 * Created: 08-Feb-18 04:33:25 PM
 * Author : Nick van Endhoven
 */ 

#include <avr/io.h>

/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
*******************************************************************/
{
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input

	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x06;			// Enable INT1 & INT2
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();

	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 500 );
	}

	return 1;
}