#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"

unsigned int count1ms = 0;
int flow = 0;
int year = 0;
int month = 1, day = 1, hour = 0, min = 0, sec = 0;
int mode = 0;

void count(int *month, int *day, int *hour, int *min, int *sec);

int main()
{
	DDRD = 0x00;
	lcdInit();
	lcdClear();
	
	TCCR0 = 0x04;
	TCNT0 = 0x06;
	TIMSK = 1;
	
	ADMUX = 0x40;
	ADCSRA = 0x87;
	
	sei();
	
	while(1)
	{
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC));
		
		unsigned int adcValue = ADC;
		
		if((PIND & 0x01) == 0)
		{
			mode++;
			mode = mode % 6;
			_delay_ms(200);
		}
		else if((PIND & 0x02) == 0)
		{
			_delay_ms(200);
			if(flow == 0)
			flow = 1;
			else if(flow == 1)
			flow = 0;
		}
		if (flow == 0)
		{
			switch (mode)
			{
				case 0:
				year = adcValue+1000;
				break;
				case 1:
				month = adcValue * 12 / 1023;
				break;
				case 2:
				day = adcValue * 31 / 1023;
				break;
				case 3:
				hour = adcValue * 23 / 1023;
				break;
				case 4:
				min = adcValue * 59 / 1023;
				break;
				case 5:
				sec = adcValue * 59 / 1023;
				break;
			}
		}

		count(&month, &day, &hour, &min, &sec);
		lcdNumber(0, 0, year);
		lcdNumber(0, 4, month);
		lcdNumber(0, 6, day);
		lcdNumber(1, 0, hour);
		lcdString(1, 2, ":");
		lcdNumber(1, 3, min);
		lcdString(1, 5, ":");
		lcdNumber(1, 6, sec);
		lcdString(1, 8, ".");
		lcdNumber(1, 9, count1ms);
		lcdNumber(0, 10, mode);
		_delay_ms(50);
		lcdClear();
	}
}

ISR(TIMER0_OVF_vect)
{
	if (flow == 1)
	{
		count1ms++;
		if (count1ms >= 1000)
		{
			count1ms = 0;
			sec++;
		}
	}
	TCNT0 = 6;
}

void count(int *month, int *day, int *hour, int *min, int *sec)
{
	if (*sec >= 60)
	{
		(*min)++;
		*sec = 0;
	}
	if (*min >= 60)
	{
		(*hour)++;
		*min = 0;
	}
	if (*hour >= 24)
	{
		(*day)++;
		*hour = 0;
	}
	if (*day > 31)
	{
		(*month)++;
		*day = 1;
	}
}