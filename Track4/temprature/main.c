/*
 * temprature.c
 *
 * Created: 08-Mar-18 02:16:13 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>

#include "lcd.h"

#define Vref 2560

typedef unsigned long int u_int32;
typedef unsigned int u_int16;
typedef unsigned char u_char;

int temp = 0;
int flag = 0;


ISR(ADC_vect)
{
	u_int32 result = ADCH << 2; 
	PORTA = result;
	result *= Vref;
	result /= 1023;
	temp = result;
	flag = 1;
}

int main(void)
{
	DDRA = 0xFF;
	DDRF &= ~0x01;
	
	ADMUX = 0xE0;	
	ADCSRA = 0x8A;	
	
	sei();	
	
	lcd_init();
	
	ADCSRA |= 0x40; 
	
	while (1)
	{
		if (flag)
		{
			lcd_set_cursor(1,1);
			char out[4] = "";
			
			sprintf(out,"%dC",temp/10);
			lcd_display_text(out);
			
			flag = 0;
			_delay_ms(2000);
			ADCSRA |= 0x40; 
		}
		asm("NOP");
	}
}
