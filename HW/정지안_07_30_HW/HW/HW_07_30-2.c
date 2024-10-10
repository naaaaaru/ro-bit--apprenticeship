#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"

volatile unsigned char RxBuffer;

void UART0_init();
void UART0_transmit(unsigned int data);
unsigned char UART0_receive();

void UART0_init()
{
	UBRR0H = 0x00;
	UBRR0L = 103;
	UCSR0A |= 0x20;
	UCSR0B |= 0x18;
	UCSR0C |= 0x06;
	DDRE = 0x02;
	UCSR0B |= (1 << RXCIE0); 
}

unsigned char UART0_receive()
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void UART0_transmit(unsigned int data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

ISR(USART0_RX_vect)
{
	RxBuffer = UART0_receive();
	switch (RxBuffer)
	{
		case '0':
		PORTA = 0b01111111;
		break;
		case '1':
		PORTA = 0b10111111;
		break;
		case '2':
		PORTA = 0b11011111;
		break;
		case '3':
		PORTA = 0b11101111;
		break;
		case '4':
		PORTA = 0b11110111;
		break;
		case '5':
		PORTA = 0b11111011;
		break;
		case '6':
		PORTA = 0b11111101;
		break;
		case '7':
		PORTA = 0b11111110;
		break;
		default:
		break;
	}
}

int main()
{
	sei();
	PORTA = 0xff;
	UART0_init();
	DDRF = 0x00;
	ADMUX = 0x40;
	ADCSRA = 0x87;
	DDRA = 0xFF;
	lcdInit();
	lcdClear();

	while (1)
	{
		unsigned int adcValue = 0;
		unsigned char channel = 0x00;
		ADMUX = 0x40 | channel;
		ADCSRA |= 0x40;

		while ((ADCSRA & 0x10) == 0);
		adcValue = ADC;
		_delay_ms(100);

		UART0_transmit(adcValue & 0xFF); 
		lcdString(0, 0, "ADC Value :");
		lcdNumber(0, 12, adcValue);
		lcdString(1, 0, "LED Value :");
		lcdNumber(1, 12, RxBuffer-48);
		_delay_ms(100);
		lcdClear();
	}
	return 0;
}
