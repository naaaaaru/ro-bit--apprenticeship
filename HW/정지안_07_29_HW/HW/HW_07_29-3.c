#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_Text.h"

int main()
{
	DDRA = 0xff; 
	DDRD = 0x00; 
	int num1 = 0;
	int num2 = 0;
	int _case = 0;
	int result = 0;
	lcdInit();
	lcdClear();
	
	while(1)
	{
		if((PIND & 0x01) == 0)
		{
			_delay_ms(200);//다중 입력 방지
			num1++;
		}
		if((PIND & 0x02) == 0)
		{
			_delay_ms(200);
			_case++;
			_case = _case % 4;
		}
		if((PIND & 0x04) == 0)
		{
			_delay_ms(200);
			num2++;
		}
		if((PIND & 0x08) == 0)
		{
			lcdClear();//예외처리 ex)이전 계산 결과가 3자리 넘어가는데 결과가 2자리수일경우 마지막 숫자가 지워지지 않고 그래도 남음
			_delay_ms(200);
			switch(_case)
			{
				case 0:
				result = num1 + num2;
				break;
				case 1:
				result = num1 - num2;
				break;
				case 2:
				result = num1 * num2;
				break;
				case 3:
				result = num1 / num2;
				break;
			}
		}

		lcdNumber(0, 0, num1);
		switch(_case)
		{
			case 0:
			lcdString(0, 3, "+");
			break;
			case 1:
			lcdString(0, 3, "-");
			break;
			case 2:
			lcdString(0, 3, "*");
			break;
			case 3:
			lcdString(0, 3, "/");
			break;
		}
		lcdNumber(0, 4, num2);
		lcdString(0, 7, "=");
		lcdNumber(0, 8, result);
	}
}
