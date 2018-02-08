/*
 * patterns.c
 *
 * Created: 08-Feb-18 04:41:20 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0xFF;					//All pins PORTD set to output
	int i = 0x01;					//Init start bits
	int d = 0;						//Init flow direction

	while(1)
	{
		PORTD = i;				//Set bits on PORTD to i
	
		if(i & 0x01) { d = 0;}			//If first bit, change direction
		if(i & 0x80) { d = 1;}			//If last bit, change direction
	
		if(0 == d) { i = i << 1;}      		//If direction, bit shift 1 to the left
		else { i = i >> 1;}			//If direction, bit shift 1 to the right
	
		_delay_ms( 50 );
	}

	return 1;
}

