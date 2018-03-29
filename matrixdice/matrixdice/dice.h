/*
 * dice.h
 *
 * Created: 22-Mar-18 01:22:03 PM
 *  Author: Lois Gussenhoven en Nick van Endhoven
 */ 

#ifndef DICE_H_
#define DICE_H_

#define MIN 1
#define MAX 6

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "matrix.h"

extern void dice_init(void);
extern void dice_roll(void);
extern void dice_cancel(void);

extern int dice_is_rolling(void);

int dice_rand(void);
int* dice_data(int);
void dice_blink(void);

int dice_top_arr(int);
int dice_bottom_arr(int);

#endif /* DICE_H_ */