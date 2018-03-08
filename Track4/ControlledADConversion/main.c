/*
 * ControlledADConversion.c
 *
 * Created: 08-Mar-18 10:56:48 AM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000
#define Vref 5120

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>

typedef unsigned long int u_int32;
typedef unsigned int u_int16;
typedef unsigned char u_char;

u_int16 voltage = 0x0000;
int vFlag = 0;

ISR(ADC_vect)
{
	u_int32 result = ADCH << 2; 
	result *= Vref;
	result /= 1023;
	
	voltage = result;
	vFlag = 1;
}

int main(void)
{
	DDRA = DDRB = 0xFF;
	DDRF &= ~0x08;	// PF3
	
	ADMUX = 0x23;
	ADCSRA = 0x8A;
	
	sei();

	ADCSRA |= 0x40;
	
	while (1)
	{
		if (vFlag)
		{
			vFlag = 0;
			_delay_ms(50);
			ADCSRA |= 0x40;
			PORTA = PORTB = (0xFF << (8 - voltage * 8 / Vref));
		}
		
		asm("");
	}
}
