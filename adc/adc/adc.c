/*
 * adc.c
 *
 * Created: 09-03-2016 16:36:46
 *  Author: Kshitiz
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
uint8_t data,data1;

void adcinit()																//initializing ADC
{
	ADMUX|=(1<<REFS0)|(1<<ADLAR);
	ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
}

void adcstart(uint8_t channel)						//start ADC through channel and store the values in data and data1 
{
	channel &=0b00000111;
	ADMUX|=(channel);
	
	ADCSRA|=(1<<ADSC);                 //start conversion signal given... ADSC bit is reset once conversion is done
	while(ADCSRA & (1<<ADSC));       //this stalls the program till conversion is complete....called polling
	
	data=ADCL;
	data1=ADCH;       //left shifted  thus this contains the last 8 bits..
	
}
/*

//to use adc via an interrupt call  -- whenever the data convrsion is complete the flag ADIF is high and the interrupt call is made
ISR(ADC_vect)
{
	data=ADC;
	PORTC=1;
	return 0;
}*/

int main(void)
{
	TCCR1A|=(1<<COM1A1)|(1<<COM1A0)|(1<<WGM11);
	TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS12);
	
	ICR1=1023;
	
	
	DDRD=0xff;
	PORTD=0x01;
	adcinit();
	TCNT1=0;
   while(1)
    {
		
         adcstart(0b00000000);             //running conversion on channel 1
		 OCR1A=data1; //control the brightness of the led through pwm according to input adc values
    }
}