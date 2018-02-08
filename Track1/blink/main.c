/*
 * blink.c
 *
 * Created: 08-Feb-18 04:37:17 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0xFF;
	
    while (1) 
    {
		PORTD = 0x80;
		_delay_ms( 500 );
		PORTD = 0x40;
		_delay_ms( 500 );
    }
	
	return 1;
}

