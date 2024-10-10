#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <math.h>
#include "LCD_Text.h"

volatile uint8_t irArr = 0;
volatile uint16_t distance;

int adcNormalized[6];
int irValue[6];
int adcMax[6] = {0, 0, 0, 0, 0, 0};
int adcMin[6] = {1024, 1024, 1024, 1024, 1024, 1024};
int mode = 0;
int leftcount = 0;
int psd[2];
int lineFound;

volatile uint16_t start_time = 0;
volatile uint16_t end_time = 0;
volatile uint8_t captured = 0;

void init_ultrasonic_sensor()
{
	DDRE |= (1 << PE3);
	DDRE &= ~(1 << PE7);

	TCCR3A = 0x00;
	TCCR3B |= (1 << ICNC3) | (1 << ICES3) | (1 << CS31);
	TCCR3C = 0x00;

	ETIMSK |= (1 << TICIE3);
}

void trigger_ultrasonic()
{
	PORTE |= (1 << PE3);
	_delay_us(10);
	PORTE &= ~(1 << PE3);
}

ISR(TIMER3_CAPT_vect)
{
	if (captured == 0)
	{
		start_time = ICR3;
		TCCR3B &= ~(1 << ICES3);
		captured = 1;
	}
	else if (captured == 1)
	{
		end_time = ICR3;
		TCCR3B |= (1 << ICES3);
		captured = 2;
	}
}

uint16_t get_distance()
{
	trigger_ultrasonic();

	uint32_t timeout = 30000;
	while (captured < 2 && timeout > 0)
	{
		_delay_us(1);
		timeout--;
	}

	if (timeout == 0)
	{
		return 0xFFFF;
	}

	uint16_t time_diff = end_time - start_time;
	uint16_t distance = (time_diff * 340UL) / 58;

	captured = 0;
	if (distance == -1)
	{
		return 10000;
	}
	else
	{
		return (abs(distance)/10);
	}
}

void motorInit()
{
	DDRB = 0x6F;
	TCCR1A = 0xA2;
	TCCR1B = 0x1A;
	TCCR1C = 0x00;
	
	ICR1 = 199;
	TCNT1 = 0x00;
}

void adcInit()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t readAdc(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

void irVisual(void)
{
	irArr = 0b00000011;
	for (int i = 0; i < 6; i++)
	{
		if (adcNormalized[i] > 40) irArr |= (1 << i);
		else irArr &= ~(1 << i);
	}
	PORTA = irArr;
}

void adcMinMax(void)
{
	for (int i = 0; i < 6; i++)
	{
		if (adcMax[i] < irValue[i])
		{
			adcMax[i] = irValue[i];
		}
		if (adcMin[i] > irValue[i])
		{
			adcMin[i] = irValue[i];
		}
	}
}

void adcNomalize(void)
{
	for (int i = 0; i < 6; i++)
	{
		adcNormalized[i] = (int)((double)(irValue[i] - adcMin[i]) / (adcMax[i] - adcMin[i]) * 100.0);
	}
}

double motorControl(int adcNormalized[])
{
	double Weight = 0;
	lineFound = 0;

	for (int i = 0; i < 6; i++)
	{
		if (adcNormalized[i] < 55)
		{
			adcNormalized[i] = 1;
			lineFound++;
		}
		else
		{
			adcNormalized[i] = 0;
		}
	}
	
	if (distance <= 600 && distance >= 200)
	{
		return 300;
	}
	 else if (distance <= 700 && lineFound == 0 && distance >= 300)
	{
		return 900;
	}
	else
	{
		if (lineFound == 0)
		{
			return 999;
		}
		else if (lineFound >= 5)
		{
			return 100;
		}
		else
		{
			Weight = -4 * adcNormalized[0] + -2 * adcNormalized[1] + -1 * adcNormalized[2] + 1 * adcNormalized[3] + 2 * adcNormalized[4] + 4 * adcNormalized[5];
			return Weight;
		}
	}
}

double whiteLineFollow(int adcNormalized[])
{
	double Weight = 0;
	lineFound = 0;

	for (int i = 0; i < 6; i++)
	{
		if (adcNormalized[i] > 40 || irValue[i] > 120)
		{
			adcNormalized[i] = 1;
			lineFound++;
		}
		else
		adcNormalized[i] = 0;
	}
	
	if(psd[0] < 280 && psd[0] > 150)
	{
		return 200;
	}
	else if (psd[0] >= 280)
	{
		return 400;
	}
	else if (psd[0] <= 150 && psd[0] > 80)
	{
		return 401;
	}
	else
	{
		if (lineFound == 0)
		{
			return 999;
		}
		else if (lineFound == 6)
		{
			PORTB = (PORTB & 0xF0) | 0x05;
			OCR1A = ICR1 * 0;
			OCR1B = ICR1 * 0;
			_delay_ms(2000);
			if (distance <= 600 && distance >= 200)
			{
				return 300;
			}
			else
			{
				return 500;
			}
		}
		else
		{
			Weight = -4 * adcNormalized[0] + -2 * adcNormalized[1] + -1 * adcNormalized[2] + 1 * adcNormalized[3] + 2 * adcNormalized[4] + 4 * adcNormalized[5];
			return Weight;
		}
	}
}

void motorRun(double Weight)
{
	/*if (leftcount >= 7)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1;
		OCR1B = ICR1 * 0;
		_delay_ms(1000);
		leftcount = 0;
	}*/
	
	if (Weight == 999)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0;
		OCR1B = ICR1 * 0;
		_delay_ms(20);
		PORTB = (PORTB & 0xF0) | 0x0A;
		OCR1A = ICR1 * 0.8;
		OCR1B = ICR1 * 0.8;
		_delay_ms(80);
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0;
		OCR1B = ICR1 * 0;
		_delay_ms(20);
	}
	else if (Weight == 900)
	{
		_delay_ms(2000);
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0;
		OCR1B = ICR1 * 0;
		_delay_ms(20);
		PORTB = (PORTB & 0xF0) | 0x06;
		OCR1A = ICR1 * 1;
		OCR1B = ICR1 * 1;
		_delay_ms(1200);
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0;
		OCR1B = ICR1 * 0;
		_delay_ms(20);
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 1;
		OCR1B = ICR1 * 1;
		_delay_ms(800);
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0;
		OCR1B = ICR1 * 0;
		_delay_ms(20);
	}
	else if (Weight == 100)
	{
		leftcount++;
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0.6;
		OCR1B = ICR1;
		_delay_ms(500);
	}
	else if (Weight == 200)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1;
		OCR1B = ICR1;
	}
	else if (Weight == 300)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0;
		OCR1B = ICR1 * 0;
	}
	else if (Weight == 400)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 1;
		OCR1B = ICR1 * 0.8;
	}
	else if (Weight == 401)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0.8;
		OCR1B = ICR1 * 1;
	}
	else if (Weight == 500)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1;
		OCR1B = ICR1;
		_delay_ms(1000);
	}
	else if (Weight <= 1 && Weight >= -1)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1;
		OCR1B = ICR1;
	}
	else if (Weight < -1 && Weight >= -3)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0.6;
		OCR1B = ICR1 * 1.2;
	}
	else if (Weight > 1 && Weight <= 3)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 1.2;
		OCR1B = ICR1 * 0.6;
	}
	else if (Weight < -3)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 0;
		OCR1B = ICR1 * 1.2;
	}
	else if (Weight > 3 && Weight < 10)
	{
		PORTB = (PORTB & 0xF0) | 0x05;
		OCR1A = ICR1 * 1.2;
		OCR1B = ICR1 * 0;
	}
}

void phaseControl(int adcNormalized[])
{
	int maxValue = 0;
	int min_value = 1023;
	int max_value = 0;
	int minValue = 100;

	for (int i = 1; i < 6; i++)
	{
		if (adcNormalized[i] > maxValue)
		{
			maxValue = adcNormalized[i];
		}
	}
	
	for (int i = 1; i < 6; i++)
	{
		if (irValue[i] > max_value)
		{
			max_value = irValue[i];
		}
	}
	
	for (int i = 1; i < 6; i++)
	{
		if (adcNormalized[i] < minValue)
		{
			minValue = adcNormalized[i];
		}
	}
	
	for (int i = 1; i < 6; i++)
	{
		if (irValue[i] < min_value)
		{
			min_value = irValue[i];
		}
	}

	if (maxValue < 90 && min_value < 170 && max_value < 220 && minValue <= 75)
	{
		mode = 1;
	}
	else if (maxValue > 80 && min_value > 100 && max_value > 200)
	{
		mode = 0;
	}
}

void psdRead()
{
	psd[0] = readAdc(0);
	psd[1] = readAdc(7);
}

int main(void)
{
	adcInit();
	motorInit();
	lcdInit();
	lcdClear();
	init_ultrasonic_sensor();

	DDRA = 0xff;
	DDRD = 0x00;
	int toggle = 0;
	sei();
	
	double Weight = 0;

	while (1)
	{
		if ((PIND & 0x01) == 0)
		{
			toggle = 1;
		}

		irValue[0] = (readAdc(1) * 1.7);
		irValue[1] = readAdc(2);
		irValue[2] = readAdc(3);
		irValue[3] = readAdc(4);
		irValue[4] = (readAdc(5) / 1.4);
		irValue[5] = (readAdc(6) * 1.2);

		distance = get_distance();
		psdRead();

		adcMinMax();
		adcNomalize();
		irVisual();
		
		/*lcdNumber(0, 0, adcNormalized[0]);
		lcdNumber(0, 3, adcNormalized[1]);
		lcdNumber(0, 6, adcNormalized[2]);
		lcdNumber(1, 0, adcNormalized[3]);
		lcdNumber(1, 3, adcNormalized[4]);
		lcdNumber(1, 6, adcNormalized[5]);
		lcdNumber(0, 9, psd[0]);
		lcdNumber(0,13,mode);
		
		lcdNumber(1,9,distance);
		lcdNumber(1,13,Weight);*/
		
		lcdNumber(0, 0, irValue[0]);
		lcdNumber(0, 5, irValue[1]);
		lcdNumber(0, 10, irValue[2]);
		lcdNumber(1, 0, irValue[3]);
		lcdNumber(1, 5, irValue[4]);
		lcdNumber(1, 10, irValue[5]);
		
		phaseControl(adcNormalized);

		if (mode == 0)
		{
			Weight = motorControl(adcNormalized);
		}
		else if (mode == 1)
		{
			Weight = whiteLineFollow(adcNormalized);
		}
		
		if (toggle == 1)
		{
			motorRun(Weight);
		}
		
		_delay_ms(50);
		
		lcdClear();
	}
}