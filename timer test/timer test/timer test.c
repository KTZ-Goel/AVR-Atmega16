/*
 * timer_test.c
 *
 * Created: 07-03-2016 17:43:18
 *  Author: Kshitiz
 */ 
#define pi 3.141592653589
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

void timerinit()                //initialise the timer
{
	TCCR0|=(1<<CS00)|(1<<CS02)|(1<<WGM00)|(1<<WGM01)|(1<<COM00)|(1<<COM01);
}

ISR(INT0_vect)              //interrupt call to stop the pwm cycle and give a delay -- show that interrupt is working
{
	TCCR0=0x00;
	_delay_ms(3000);
	timerinit();        //reinitilaise the timer so that the process continues after the interrupt is done
	TCNT0=0;
}

int main(void)
{
	timerinit();       //on pinB3
	
	sei();                                 //interrupt settings
	GICR|=(1<<INT0);
	MCUCR|=(1<<ISC01)|(1<<ISC00);
	DDRD&=(0<<PD2);   //interrupt at pd2
	
	DDRB|=(1<<PB3)|(1<<PB2);    //pb3 - pwm
	PORTB|=(1<<PB2);
	TCNT0=0;
	OCR0=0;
	int i=0;
    while(1)
    {
		OCR0=(int)(255*sin(i*(pi/180)));      //     giving sinusodial variations
		if (i>179)
		{
			i=0;
		}
		i++;
		_delay_ms(15);
    }
}