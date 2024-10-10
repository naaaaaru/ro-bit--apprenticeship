#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char led = 0xff;
void UART0_init();
void UART0_transmit(char data);
char UART0_receive();

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

int main()
{
	UART0_init();
	
	DDRA = 0xff;
	DDRD = 0x00;
	EIMSK=(1<<INT0);
	EICRA=(ISC01>>1)|(ISC00>>1);
	sei();

	while (1)
	{
		switch (UART0_receive())
		{
			case '0':
			led -= 0x01;
			UART0_transmit('0');
			UART0_transmit(' ');
			UART0_transmit('l');
			UART0_transmit('e');
			UART0_transmit('d');
			UART0_transmit(' ');
			UART0_transmit('o');
			UART0_transmit('n');
			UART0_transmit(' ');
			break;
			case '1':
			led -= 0x02;
			UART0_transmit('1');
			UART0_transmit(' ');
			UART0_transmit('l');
			UART0_transmit('e');
			UART0_transmit('d');
			UART0_transmit(' ');
			UART0_transmit('o');
			UART0_transmit('n');
			UART0_transmit(' ');
			break;
			case '2':
			led -= 0x04;
			UART0_transmit('2');
			UART0_transmit(' ');
			UART0_transmit('l');
			UART0_transmit('e');
			UART0_transmit('d');
			UART0_transmit(' ');
			UART0_transmit('o');
			UART0_transmit('n');
			UART0_transmit(' ');
			break;
			case '3':
			led -= 0x08;
			UART0_transmit('3');
			UART0_transmit(' ');
			UART0_transmit('l');
			UART0_transmit('e');
			UART0_transmit('d');
			UART0_transmit(' ');
			UART0_transmit('o');
			UART0_transmit('n');
			UART0_transmit(' ');
			break;
			case '4':
			led -= 0x10;
			UART0_transmit('4');
			UART0_transmit(' ');
			UART0_transmit('l');
			UART0_transmit('e');
			UART0_transmit('d');
			UART0_transmit(' ');
			UART0_transmit('o');
			UART0_transmit('n');
			UART0_transmit(' ');
			break;
			case '5':
			led -= 0x20;
			UART0_transmit('5');
			UART0_transmit(' ');
			UART0_transmit('l');
			UART0_transmit('e');
			UART0_transmit('d');
			UART0_transmit(' ');
			UART0_transmit('o');
			UART0_transmit('n');
			UART0_transmit(' ');
			break;
			case '6':
			led -= 0x40;
			UART0_transmit('6');
			UART0_transmit(' ');
			UART0_transmit('l');
			UART0_transmit('e');
			UART0_transmit('d');
			UART0_transmit(' ');
			UART0_transmit('o');
			UART0_transmit('n');
			UART0_transmit(' ');
			break;
			case '7':
			led -= 0x80;
			UART0_transmit('7');
			UART0_transmit(' ');
			UART0_transmit('l');
			UART0_transmit('e');
			UART0_transmit('d');
			UART0_transmit(' ');
			UART0_transmit('o');
			UART0_transmit('n');
			UART0_transmit(' ');
			break;
			case '8':
			UART0_transmit('L');
			UART0_transmit('E');
			UART0_transmit('F');
			UART0_transmit('T');
			UART0_transmit(' ');
			led <<= 1;
			break;
			case '9':
			UART0_transmit('R');
			UART0_transmit('I');
			UART0_transmit('G');
			UART0_transmit('H');
			UART0_transmit('T');
			UART0_transmit(' ');
			led >>= 1;
			break;
		}
		PORTA = led;
	}
	return 0;
}

ISR(INT0_vect)
{
	_delay_ms(200);
	led = 0xff;
	UART0_transmit('R');
	UART0_transmit('E');
	UART0_transmit('S');
	UART0_transmit('E');
	UART0_transmit('T');
	UART0_transmit(' ');
}