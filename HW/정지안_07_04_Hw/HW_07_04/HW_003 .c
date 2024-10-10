#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

float avr(int score1, int score2, int score3);

int main()
{
	float num = 0;
	float* pArr;
	float s1, s2, s3;
	float result;
	float temp;
	char* name;
	char nameInput;
	char nameTemp;
	printf("입력 : ");
	scanf_s("%d", &num);
	name = (char*)malloc(sizeof(char) * num);
	pArr = (float*)malloc(sizeof(float) * num);
	for (int j = 0; j < num; j++)
	{
		nameInput = 0;
		scanf_s("%s", nameInput);
		name[j] = nameInput;
		for (int i = 0; i < 3; i++)
		{
			scanf_s("%d %d %d", &s1, &s2, &s3);
			result = avr(s1, s2, s3);
		}
		pArr[j] = result;
	}
	for (int p = 0; p < num; p++)
	{
		for (int k = 0; k < num; k++)
		{
			if (pArr[k] > pArr[k + 1])
			{
				temp = pArr[k];
				pArr[k] = pArr[k + 1];
				pArr[k + 1] = temp;
				nameTemp = name[k];
				name[k] = name[k + 1];
				name[k + 1] = nameTemp;
			}
		}
	}
	for (int t = 0; t < num; t++)
	{
		printf("%s %f", name[t], pArr[t]);
	}

}
float avr(int score1, int score2, int score3)
{
	float avrResult;
	avrResult = (float)(score1 + score2 + score3) / 3;
	return avrResult;
}