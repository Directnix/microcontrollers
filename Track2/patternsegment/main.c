/*
 * patternsegment.c
 *
 * Created: 22-Feb-18 03:40:41 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

typedef struct { 	   
	int bits;   
	int delay; 
} PATTERN;

PATTERN pattern[] = { 
	{0x00, 150},
	{0x01, 100}, {0x02, 100}, {0x04, 100}, {0x08, 100}, {0x10, 100}, {0x20, 100},
	{0x7F, 250}, {0x00, 250}, {0x7F, 250}, {0x00, 250},
	{0x20, 100}, {0x10, 100}, {0x08, 100}, {0x04, 100}, {0x02, 100}, {0x01, 100},
	{0x00, 0},
};

void wait( int ms ){
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

int main(void)
{
	DDRC = 0xFF;

    while (1) 
    {
		int i = 0;
		while(pattern[i].delay != 0 ) {   
			PORTC = pattern[i].bits;
			wait(pattern[i].delay); 
			i++;
		}
    }
}

