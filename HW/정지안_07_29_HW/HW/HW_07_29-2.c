#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"
int main()
{
	DDRF = 0x00;
	ADMUX = 0x40;
	ADCSRA = 0x87;
	DDRA = 0xFF;
	lcdInit();
	lcdClear();
	while(1)
	{
		unsigned int adcValue = 0;
		unsigned char channel = 0x00;
		ADMUX = 0x40 | channel;
		ADCSRA |= 0x40;
		while((ADCSRA & 0x10) == 0);
		{
			adcValue = ADC;
			_delay_ms(100);
		}
		float volt = adcValue * 5 / 1024;
		int num = (int)volt;
		int _num = (volt - num) * 1000;
		lcdNumber(0, 0, adcValue);
		lcdNumber(0, 7, num);
		lcdString(0, 8, ".");
		lcdNumber(0, 9, _num);
		lcdString(1, 0, "19th_jj");
		_delay_ms(100);
		lcdClear();
		if (adcValue > 896 && adcValue <= 1024)
		{
			PORTA = 0b01111111;
		}
		else if (adcValue > 768 && adcValue <= 896)
		{
			PORTA = 0b10111111;
		}
		else if (adcValue > 640 && adcValue <= 768)
		{
			PORTA = 0b11011111;
		}
		else if (adcValue > 512 && adcValue <= 640)
		{
			PORTA = 0b11101111;
		}
		else if (adcValue > 384 && adcValue <= 512)
		{
			PORTA = 0b11110111;
		}
		else if (adcValue > 256 && adcValue <= 384)
		{
			PORTA = 0b11111011;
		}
		else if (adcValue > 128 && adcValue <= 256)
		{
			PORTA = 0b11111101;
		}
		else if (adcValue >= 0 && adcValue <= 128)
		{
			PORTA = 0b11111110;
		}
	}
}