/*
 * matrix.c
 *
 * Created: 22-Mar-18 12:31:43 PM
 * Author: Nick van Endhoven
 */ 

#include "matrix.h"

void mtr_init(){
	twi_init();	
	
	// Init HT16K22. Page 32 datasheet
	mtr_write(0x21);	// Internal osc on (page 10 HT16K33)
	mtr_write(0xA0);	// HT16K33 pins all output
	mtr_write(0xE3);	// Display Dimming 4/16 duty cycle
	mtr_write(0x81);	// Display OFF - Blink On
}

void mtr_write(int data){
		twi_start();
		twi_tx(0xE0);	// Display I2C address + R/W bit
		twi_tx(data);
		twi_stop();
}

void mtr_write_to_address(int address, int data){
		twi_start();
		twi_tx(0xE0);		// Display I2C addres + R/W bit
		twi_tx(address);	// Address
		twi_tx(data);		// data
		twi_stop();
}

void mtr_clear(){
	int i;
	for(i = 0; i < 0x0F; i++)
		mtr_write_to_address(i, 0x00);
}

void mtr_write_arr(int* data){		
	mtr_clear();
	int addr, i = 0;
	for(addr = 0x00; addr <= 0x0e; addr += 0x02){
		mtr_write_to_address(addr, data[i]);
		i++;
	}
	
	free(data);
}

/******************************************************************/
void twi_init(void)
/* 
short:			Init AVR TWI interface and set bitrate
inputs:			
outputs:	
notes:			TWI clock is set to 100 kHz
Version :    	DMK, Initial code
*******************************************************************/
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

/******************************************************************/
void twi_start(void)
/* 
short:			Generate TWI start condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

/******************************************************************/
void twi_stop(void)
/* 
short:			Generate TWI stop condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x10 | 0x04);
}

/******************************************************************/
void twi_tx(unsigned char data)
/* 
short:			transmit 8 bits data
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
