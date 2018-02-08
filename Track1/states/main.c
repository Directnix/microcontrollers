/*
 * states.c
 *
 * Created: 08-Feb-18 04:43:29 PM
 * Author : Nick van Endhoven
 */

 #define F_CPU 8000000

 #include <avr/io.h>
 #include <util/delay.h>


/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
*******************************************************************/
{

	DDRD = 0xFF; 					// All pins PORTD are set to output
	DDRC = 0x00;					// All pins PORTC are set to input
	
	int s = 0;					// init state
	long t = 0;					// init tick
	int o = 0;					// init on/off
	
	while (1)
	{
		
		if(PINC & 0x10) { 			// if pin 4 on C is pressed
			if (0 == s) { s = 1; }    	// switch state
			else { s = 0;}
		}
		
		if(s) 				       	// check state
		{
			if(0 == t % 1000 ){              	// if tick change on/off
				if (0 == o) { o = 1; }
				else { o = 0;}
			}
		}
		else
		{
			if(0 == t % 250 ){                	// if tick change on/off
				if (0 == o) { o = 1; }
				else { o = 0;}
			}
		}
		
		if(0 == o){				// checks if on or off
			PORTD = 0x00;
			} else {
			PORTD = 0x80;
		}
		
		t++;					//increases tick
		_delay_ms( 1 );
	}

	return 1;
}


