/*
 * SegmentDisplay.c
 *
 * Created: 21-Feb-18 02:00:51 PM
 * Author : Nick van Endhoven
 */ 


#define F_CPU 8000000	

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const char numbers[15] = {
/*0*/	0b00111111,
/*1*/	0b00000110,	
/*2*/	0b01011011,
/*3*/	0b01001111,
/*4*/	0b01100110,	
/*5*/	0b01101101,	
/*6*/	0b01111101,	
/*7*/	0b00000111,	
/*8*/	0b01111111, 
/*9*/	0b01101111,	
/*A*/	0b01110111,	
/*B*/	0b01111100, 
/*C*/	0b00111001, 
/*D*/	0b01011110, 
/*E*/	0b01111001
};

const char segments[7] = {
	0b00000001, // BOVEN
	0b00000010, // RECHTS BOVEN
	0b00000100, // ONDER
	0b00001000, // RECHTS ONDER
	0b00010000, // LINKS ONDER
	0b00100000, // LINKS BOVEN
	0b01000000  // MIDDEN
};

int current;

void display( int digit )
{
	PORTC = numbers[digit];
}

ISR( INT1_vect )
{
	if(current < (sizeof(numbers) - 1)){
		current = current + 1;
		display(current);
	}
}

ISR( INT2_vect )
{
	if(current > 0){
		current = current - 1;
		display(current);		
	}
}


int main(void)
{
	current = 0;
	
    DDRD = 0x00;		
    DDRC = 0xFF;
	
	EICRA |= 0x3C;	
	EIMSK |= 0x06;		

	sei();

	display(current);
	
    while (1) 
    {
    }
}

