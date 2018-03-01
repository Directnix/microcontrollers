/*
 * lcd.c
 *
 * Created: 01-Mar-18 09:47:48 AM
 *  Author: Nick van Endhoven
 */ 


#include "lcd.h"


void lcd_command ( unsigned char dat, bool isChar)
{
	char type; 
	if(isChar)
		type = 0x0C;
	else
		type = 0x08;
	
	PORTC = dat & 0xF0;			  
	PORTC = PORTC | type;			
	_delay_ms(1);					
	PORTC = 0x04;					
	
	PORTC = (dat & 0x0F) << 4;	   
	PORTC = PORTC | type;			
	_delay_ms(1);					
	PORTC = 0x00;					
}


void lcd_clear(){
	lcd_command(0x01, false);
	lcd_command(0x08, false);
}


void lcd_init(){
	DDRC = 0xFF;
	PORTC = 0x00;
	
	lcd_clear();
		
	lcd_command(0x02, false);
	lcd_command(0x28, false);
	lcd_command(0x0C, false);
	lcd_command(0x06, false);
	lcd_command(0x80, false);
}


void lcd_display_text(char *str){
	for (int i=0; i < strlen(str); i++) 
		lcd_command( str[i], true );
}

void lcd_set_cursor(int position, int line){
	if(line == 2)
		lcd_command(0xC0, false);
	else
		lcd_command(0x80, false);
		
	for(int i=0; i < position; i++)
		lcd_command(0x14, false);
	
}