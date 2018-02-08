/*
 * finiteStateMachine.c
 *
 * Created: 08-Feb-18 04:44:28 PM
 * Author : Nick van Endhoven
 */

 #define F_CPU 8000000

 #include <avr/io.h>
 #include <util/delay.h>


enum STATES {START, STATE1, STATE2, STATE3, END};
enum BUTTONS {D5, D6, D7};
void changestate(int*, int);

/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
*******************************************************************/
{
	DDRD = 0x00;			// Set all pins on PORTD to input
	DDRC = 0xFF;			// Set all pins on PORTD to output
	int state = START;		// set state
	
	while (1)
	{
		if(PIND & 0x20){		// PD 5 is pressed
			changestate(&state, D5);
		}
		else if(PIND & 0x40){		// PD 6 is pressed
			changestate(&state, D6);
		}
		else if(PIND & 0x80){		// PD 7 is pressed
			changestate(&state, D7);
		}
		
		switch(state)
		{
			case START: PORTC = 0x01;
			break;
			case STATE1: PORTC = 0x02;
			break;
			case STATE2: PORTC = 0x04;
			break;
			case STATE3: PORTC = 0x08;
			break;
			case END: PORTC = 0x10;
			break;
		}
		
		_delay_ms(500);
	}
	
	return 1;
}

void changestate(int* s, int b)
{
	switch(*s)
	{
		case START:
		switch(b)
		{
			case D5: *s = STATE2;
			break;
			case D6: *s = STATE1;
			break;
		}
		break;
		case STATE1:
		switch(b)
		{
			case D5: *s = STATE2;
			break;
			case D7: *s = START;
			break;
		}
		break;
		case STATE2:
		switch(b)
		{
			case D5: *s = STATE3;
			break;
			case D6: *s = STATE1;
			break;
			case D7: *s = START;
			break;
		}
		break;
		case STATE3:
		switch(b)
		{
			case D5: *s = END;
			break;
			case D6: *s = END;
			break;
			case D7: *s = START;
			break;
		}
		break;
		case END:
		switch(b)
		{
			case D7: *s = START;
			break;
		}
		break;
	}
}
