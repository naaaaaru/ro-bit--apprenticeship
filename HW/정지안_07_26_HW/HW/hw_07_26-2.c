#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main()
{
	DDRA=0xFF;
	DDRD=0x00;
	
	EIMSK=(1<<INT2)|(1<<INT3);
	EICRA=(ISC21>>1)|(ISC20>>1)|(ISC31>>1)|(ISC30>>1);
	
	sei();
	
	while (1)
	{	
		if((PIND & 0x01)==0)
		{
			PORTA=0x0F;
			if((PIND & 0x02)==0)
			{
				PORTA=0x00;
			}
		}
		else if((PIND & 0x02)==0)
		{
			PORTA=0xF0;
		}
		else
		{
			PORTA=0xff;
			_delay_ms(500);
			PORTA=0x00;
			_delay_ms(500);
		}
	}
}

ISR(INT2_vect)
{
	PORTA= 0xFF;
	unsigned char left=0x80;
	for(int i=0;i<8;i++)
	{
		PORTA= left;
		_delay_ms(500);
		left=left>>1;
	}
}

ISR(INT3_vect)
{
	PORTA= 0xFF;
	unsigned char right=0x01;
	for(int i=0;i<8;i++)
	{
		PORTA= right;
		_delay_ms(500);
		right=right<<1;
		
	}
}

