/*
 * lookuppatterns.c
 *
 * Created: 08-Feb-18 04:42:19 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>


typedef struct { 	   // struct to capsulize a pattern
	int bits;   // given bit configuration
	int delay;  // delay in ms
} PATTERN;

PATTERN pattern[] = { // Animation of patterns, step by step
	{0x00, 300},
	{0x81, 100}, {0xC3, 100}, {0xE7, 100}, {0xFF, 300},
	{0x7E, 100}, {0x3C, 100}, {0x18, 100},
	{0x00, 300},
	{0x81, 100}, {0xC3, 100}, {0xE7, 100}, {0xFF, 300},
	{0x7E, 100}, {0x3C, 100}, {0x38, 100},
	{0x00, 0x00}
};
/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
*******************************************************************/
{

	DDRA = 0xFF;				// All pins PORTA to PORTD are set to output
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	while (1)
	{
		int i = 0;
		while( pattern[i].delay != 0 ) {   // Loop till delay 0 is detected
			PORTA = pattern[i].bits;
			PORTB = pattern[i].bits;  // Set LEDs to given pattern
			PORTC = pattern[i].bits;
			PORTD = pattern[i].bits;

			_delay_ms(pattern[i].delay);   // Wait the delay given

			i++;
		}
	}

	return 1;
}


