#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"

unsigned int count50us;
int timer;
char led = 0x00;

int main()
{
	DDRA = 0xFF;  
	DDRF = 0x00;  

	TCNT0 = 156;   
	TCCR0 = 0x02;  
	TIMSK = 0x01; 
	ADMUX = 0x40;  
	ADCSRA = 0x87; 

	lcdInit();
	lcdClear();
	PORTA = led;

	sei(); 

	while(1)
	{
		ADCSRA |= (1 << ADSC); 
		while (ADCSRA & (1 << ADSC)); 

		unsigned int adcValue = ADC;
		timer = ((adcValue + 1) / 128) * 200 + 700; 

		lcdNumber(0, 0, timer);
		lcdString(0, 6, "us");
		_delay_ms(100);
		lcdClear();
	}
}

ISR(TIMER0_OVF_vect)
{
	count50us++;
	if (count50us * 100 >= timer - 200)
	{
		if (led == 0x00)
		{
			led = 0xFF;
		}
		else
		{
			led = 0x00; 
		}
		PORTA = led;
		count50us = 0;
	}
}