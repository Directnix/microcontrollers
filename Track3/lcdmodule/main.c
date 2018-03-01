/*
 * lcdmodule.c
 *
 * Created: 22-Feb-18 04:18:09 PM
 * Author : Nick van Endhoven
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"

int main(void)
{
    lcd_init();
	
	lcd_set_cursor(0, 1);
	lcd_display_text("Hello");
	
	lcd_set_cursor(0, 2);
	lcd_display_text("Ma name Nick!!");

	lcd_set_cursor(8, 1);
	lcd_display_text("World!");
	
    while (1) 
    {
    }
}

