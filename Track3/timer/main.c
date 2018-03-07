/*
 * timer.c
 *
 * Created: 07-Mar-18 11:58:37 AM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int tick = 0;
int high = 1;

ISR( TIMER2_COMP_vect )
{
	tick++;
	
	if(high && 15 == tick){
		PORTD = 0x00;
		tick = 0;
		high = 0;
	}else if(25 == tick){
		PORTD = 0xFF;
		tick = 0;
		high = 1;
	}
}

int main(void)
{
    DDRD = 0xFF;

    OCR2 = 519;
    TCCR2 = 1<<WGM21;           
	
    TIMSK = TIMSK | 1<<TOIE1 | 1<<OCIE2;
    TCCR2 |= 1<<CS22 | 0<<CS21 | 1<<CS20;
	TCNT2 = 0;
	
    sei();

    while (1) 
    {
    }
}

