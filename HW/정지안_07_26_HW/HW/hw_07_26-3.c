#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char counter = 0xff;

int main()
{
	DDRA = 0xff; 

	EIMSK = (1 << INT0) | (1 << INT1) | (1 << INT2) | (1 << INT3); 
	EICRA = (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10) | (1 << ISC21) | (1 << ISC20) | (1 << ISC31) | (1 << ISC30); 
	sei(); 
	
	while(1)
	{
		counter =  counter - 0x01;
		_delay_ms(100);
		PORTA = counter;
	}
}

ISR(INT0_vect)
{
	char buff = 0x1f;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			PORTA = buff;
			_delay_ms(100);
			buff <<= 1;
		}
	}
}

ISR(INT1_vect)
{
	char buff = 0xf8;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			PORTA = buff;
			_delay_ms(100);
			buff >>= 1;
		}
	}
}

ISR(INT2_vect)
{
	char buff = 0xfe;
	for (int i = 0; i < 7; i++)
	{
		PORTA = buff;
		_delay_ms(100);
		buff >>= 1;
	}
	for (int i = 0; i < 7; i++)
	{
		buff <<= 1;
		PORTA = buff;
		_delay_ms(100);
	}
}

ISR(INT3_vect)
{
	counter = 0xff;
}
