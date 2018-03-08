/*
 * ADleds.c
 *
 * Created: 08-Mar-18 10:49:46 AM
 * Author : Nick van Endhoven
 */ 

#define Vref 5120

#include <avr/io.h>
#include <avr/interrupt.h>

typedef unsigned long int u_int32;
typedef unsigned int u_int16;

/* Measured voltage (mV) */
u_int16 v = 0x0000;

ISR(ADC_vect)
{
	u_int32 result = ADC;
	result *= Vref;
	result /= 1023;
	v = result;
}

int main(void)
{
	DDRA = 0xFF, DDRB = 0xFF;
	DDRF &= ~0x02;	// PF1(ADC1) Read
	
	ADMUX = 0x01;
	ADCSRA = 0xEE;
	
	sei();
	
	while (1){
		PORTA = PORTB = (0xFF << (8 - v * 8 / Vref));
	}
}

