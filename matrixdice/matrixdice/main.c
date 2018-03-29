/*
 * matrixdice.c
 *
 * Created: 22-Mar-18 12:05:14 PM
 * Author : Nick van Endhoven en Lois Gussenhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "matrix.h"
#include "dice.h"

ISR( INT2_vect )
{
	if(1 == dice_is_rolling())
		return;
		
	dice_cancel();
}

int main( void )
{
	DDRD = 0x00;

	EICRA |= 0x30;			// INT2 rising edge
	EIMSK |= 0x04;			// Enable INT2
	    
	sei();
	
	mtr_init();	
	mtr_clear();
	dice_init();
	
	dice_roll();
	
	while (1)
	{
	}

	return 1;
}