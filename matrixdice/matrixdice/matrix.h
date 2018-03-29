/*
 * matrix.h
 *
 * Created: 22-Mar-18 12:32:29 PM
 *  Author: Nick van Endhoven
 */ 


#ifndef MATRIX_H_
#define MATRIX_H_

#define F_CPU 8000000

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

extern void mtr_init(void);
extern void mtr_write(int);
extern void mtr_write_arr(int*);
extern void mtr_write_to_address(int, int);

extern void mtr_clear(void);

extern void wait(int);

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char);

#endif /* MATRIX_H_ */
