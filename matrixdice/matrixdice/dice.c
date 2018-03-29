/*
 * dice.c
 *
 * Created: 22-Mar-18 01:21:42 PM
 *  Author: Lois Gussenhoven en Nick van Endhoven
 */ 

#include "dice.h"

int current;
int rolling;
int cancel;

void dice_init() {
	current = -1;
	rolling = -1;
	cancel = 0;
	srand(time(NULL));
}

void dice_roll() {
	rolling = 1;
	cancel = 0;
	
	int delay = 10;
	while(delay < 500){				
		mtr_write_arr(dice_data(dice_rand()));
		wait(delay);
		delay *= 1.1;
	}
	
	rolling = 0;
	dice_blink();
}

int dice_is_rolling(){
	return rolling;
}

void dice_blink(){	
	int b = 0;
	
	while(0 == rolling){
		if(1 == cancel)
			break;
				
		if(1 == b){
			mtr_write_to_address(0x00, 0xE1);
			mtr_write_to_address(0x0e, 0xE1);
					
			mtr_write_to_address(0x02, dice_top_arr(current) + 0xC0);
			mtr_write_to_address(0x0c, dice_bottom_arr(current) + 0xC0);
			b = 0;
		}else{
			mtr_write_to_address(0x00, 0x00);
			mtr_write_to_address(0x0e, 0x00);
						
			mtr_write_to_address(0x02, dice_top_arr(current));
			mtr_write_to_address(0x0c, dice_bottom_arr(current));
			b = 1;
		}

		wait(500);
	}
	dice_roll();
}

void dice_cancel(){
	cancel = 1;
}

int dice_rand() {

	int random = (rand() % (MAX +1 - MIN)+ MIN);

	if (random == current) {
		if (1 == random) 
			random++;
		else
			random--;
	}

	current = random;
	
	return random;
}

int* dice_data(int num){		
	
	int* data = malloc(8 * sizeof(int));
	
	switch(num){
		case 1:
			data[0] = 0x00; data[1] = 0x0c; data[2] = 0x08; data[3] = 0x08;
			data[4] = 0x08; data[5] = 0x08; data[6] = 0x1c; data[7] = 0x00;
		break;
		case 2:
			data[0] = 0x00; data[1] = 0x1E; data[2] = 0x10; data[3] = 0x1E;
			data[4] = 0x02; data[5] = 0x02; data[6] = 0x1E; data[7] = 0x00;
		break;
		case 3: 
			data[0] = 0x00; data[1] = 0x1E; data[2] = 0x10; data[3] = 0x1E;
			data[4] = 0x10; data[5] = 0x10; data[6] = 0x1E; data[7] = 0x00;
		break;
		case 4:
			data[0] = 0x00; data[1] = 0x12; data[2] = 0x12; data[3] = 0x12;
			data[4] = 0x1E; data[5] = 0x10; data[6] = 0x10; data[7] = 0x00;
		break;
		case 5:
			data[0] = 0x00; data[1] = 0x1E; data[2] = 0x02; data[3] = 0x1E;
			data[4] = 0x10; data[5] = 0x10; data[6] = 0x1E; data[7] = 0x00;
		break;
		case 6:
			data[0] = 0x00; data[1] = 0x1E; data[2] = 0x02; data[3] = 0x1E;
			data[4] = 0x12; data[5] = 0x12; data[6] = 0x1E; data[7] = 0x00;
		break;
	}
	
	return data;
}

int dice_top_arr(int num){
	switch(num){
		case 1: return 0x0c;
		case 2: return 0x1E;
		case 3: return 0x1E;
		case 4: return 0x12;
		case 5: return 0x1E;
		case 6: return 0x1E;
	}
	return 0x00;
}

int dice_bottom_arr(int num){
	switch(num){
		case 1: return 0x1c;
		case 2: return 0x1E;
		case 3: return 0x1E;
		case 4: return 0x10;
		case 5: return 0x1E;
		case 6: return 0x1E;
	}
	return 0x00;
}
