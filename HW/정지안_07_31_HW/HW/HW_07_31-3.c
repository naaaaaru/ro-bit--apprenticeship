#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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
	int pos,spd;
	while(1)
	{
		UART0_transmit('p');
		UART0_transmit('o');
		UART0_transmit('s');
		pos = UART0_receive();
		UART0_transmit('s');
		UART0_transmit('p');
		UART0_transmit('d');
		spd = UART0_receive();
		Driving_AX(100,pos,spd);
	}
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
		UART0_transmit(txbuf[i]);
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
