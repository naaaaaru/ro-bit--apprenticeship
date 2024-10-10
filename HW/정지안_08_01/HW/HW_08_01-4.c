#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"

unsigned int count1ms;
unsigned int time = 0;
char led = 0x02;
unsigned int ms;
unsigned int sec;
unsigned int min;

void UART0_init();
void UART0_transmit(unsigned int data);
unsigned char UART0_receive();
void ledOn(char led);
void updateLCD(unsigned int time);

void ledOn(char led)
{
	char _led = 0xff;
	_led = _led - led;
	PORTA = _led;
}

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

int main()
{
	DDRA = 0xff;
	TCNT0 = 0x04;
	TCCR0 = 0x06;
	TIMSK = 0x01;
	lcdInit();
	lcdClear();
	
	UART0_init();
	sei();
	
	while(1)
	{
		for (int i = 0; i < 5; i++)
		{
			led <<= 1;
			_delay_ms(1000);
			ledOn(led);
			led <<= 1;
			_delay_ms(1000);
			ledOn(led);
			led >>= 1;
			_delay_ms(1000);
			ledOn(led);
			if (led == 0x00)
			{
				led = 0b00000001;
				break;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			led >>= 1;
			_delay_ms(1000);
			ledOn(led);
			led >>= 1;
			_delay_ms(1000);
			ledOn(led);
			led <<= 1;
			_delay_ms(1000);
			ledOn(led);
			if (led == 0x00)
			{
				led = 0b10000000;
				break;
			}
		}
	}
}

ISR(USART0_RX_vect)
{
	if (UART0_receive() == 48)
	{
		led = 0x01;
	}
	else if (UART0_receive() == 49)
	{
		led = 0x02;
	}
	else if (UART0_receive() == 50)
	{
		led = 0x04;
	}
	else if (UART0_receive() == 51)
	{
		led = 0x08;
	}
	else if (UART0_receive() == 52)
	{
		led = 0x10;
	}
	else if (UART0_receive() == 53)
	{
		led = 0x20;
	}
	else if (UART0_receive() == 54)
	{
		led = 0x40;
	}
	else if (UART0_receive() == 55)
	{
		led = 0x80;
	}
}

ISR(TIMER0_OVF_vect)
{
	count1ms++;
	if (count1ms >= 2)
	{
		count1ms = 0;
		time++;
		if (time % 50 == 0)
		{
			UART0_transmit(led);
		}
		ms = time % 100;
		sec = (time / 100) % 60;
		min = (time / 6000) % 60;
		lcdNumber(0, 0, min);
		lcdString(0, 2, ":");
		lcdNumber(0, 3, sec);
		lcdString(0, 5, ":");
		lcdNumber(0, 6, ms);
	}
}
