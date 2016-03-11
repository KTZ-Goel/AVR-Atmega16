/*
 * LED_blink.c
 *
 * Created: 07-03-2016 11:34:51
 *  Author: Kshitiz
 */ 

#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC|=(1<<PC0);
	PORTC=0x00;
    while(1)
    {
		
		PORTC^=(1<<PC0);
		_delay_ms(100);
	}
	
	return 0;
}