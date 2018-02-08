/*
 * inputblink.c
 *
 * Created: 08-Feb-18 04:39:49 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{

	DDRD = 0xFF;
	DDRC = 0x00;

    while (1) 
    {
		if(PINC & 0x10)
		{
			PORTD = 0x80;
			_delay_ms( 100 );
			PORTD = 0x00;
			_delay_ms( 100 );
		}
    }
	
	return 1;
}

