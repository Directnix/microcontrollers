/*
 * counter.c
 *
 * Created: 01-Mar-18 01:29:19 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000
#define REACH_VALUE 1

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "lcd.h"

int count = 0;

ISR( TIMER2_OVF_vect  )
{
	count++;
}

void timer2_init()
{
	OCR2 = REACH_VALUE;	
	TIMSK |= 0x08;		
	SREG  |= 0x08;
	TCCR2 = 0x1F;			
}

int main(void)
{	
	char buffer[20];
	DDRD = 0x00;		
	
	DDRA = 0xFF; 
	
	lcd_init();
	timer2_init();
	
	while (1)
	{
		PORTA = TCNT2;
		
		lcd_set_cursor(7,1);
		lcd_display_text(itoa(count, buffer, 10));
		_delay_ms(10);
	}
}

