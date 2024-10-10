#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"

void Uart_Putch(unsigned char Putdata);
void Driving_AX(unsigned char id, unsigned int position, unsigned int spd);
void UART0_init();
void UART0_transmit(char data);
char UART0_receive();

int main()
{
	UART0_init();
	UBRR0L = 103;
	UBRR0H = 0;
	UCSR0A = 0x20;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	DDRF = 0x00;
	ADMUX = 0x40;
	ADCSRA = 0x87;
	DDRA = 0xFF;
	DDRD = 0x00;
	lcdInit();
	lcdClear();
	DDRE = 0x02;

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
		int _spd;
		_spd = UART0_receive() / 9 * 300;
		Driving_AX(100, adcValue, _spd);
		lcdNumber(0, 0, _spd);
		lcdNumber(1, 0, adcValue);
	}
}

void Uart_Putch(unsigned char Putdata)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = Putdata;
}

void Driving_AX(unsigned char id, unsigned int position, unsigned int spd)
{
	unsigned char i;
	unsigned char Pos_L, Pos_H, Spd_L, Spd_H;
	unsigned char txbuf[11];

	Pos_L = position & 0xFF;
	Pos_H = (position >> 8) & 0xFF;
	Spd_L = spd & 0xFF;
	Spd_H = (spd >> 8) & 0xFF;

	txbuf[0] = 0xFF;
	txbuf[1] = 0xFF;
	txbuf[2] = id;
	txbuf[3] = 7;
	txbuf[4] = 3;
	txbuf[5] = 30;
	txbuf[6] = Pos_L;
	txbuf[7] = Pos_H;
	txbuf[8] = Spd_L;
	txbuf[9] = Spd_H;

	txbuf[10] = 0;
	for (i = 2; i < 10; i++)
	txbuf[10] += txbuf[i];
	txbuf[10] = ~txbuf[10];

	for (i = 0; i < 11; i++)
	{
		Uart_Putch(txbuf[i]);
		_delay_ms(1);
	}
}

void UART0_init()
{
	UBRR0H = 0x00;
	UBRR0L = 103;
	UCSR0A |= 0x20;
	UCSR0B |= 0x18;
	UCSR0C |= 0x06;
	DDRE |= 0x02;
}

char UART0_receive()
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void UART0_transmit(char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}
