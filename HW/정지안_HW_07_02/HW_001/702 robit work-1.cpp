#include<stdio.h>

int type1(int size);
int type2(int size);
int type3(int size);
int type4(int size);


int main()
{
	int size, type;
	int shape;
	printf("길이(홀수)와 종류를 입력해주시요");
	scanf_s("%d %d", &size, &type);
	switch (type)
	{
	case 1:
		shape = type1(size);
		break;
	case 2:
		shape = type2(size);
		break;
	case 3:
		shape = type3(size);
		break;
	case 4:
		shape = type4(size);
		break;
	default:
		printf("잘못된 숫자입니다");
		break;
	}
}

int type1(int size)
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= (size + 1) / 2; j++)
		{
			if (i <= (size + 1) / 2)
			{
				if (j <= i)
					printf("*");
				else
					printf(" ");
			}
			else
			{
				if (i <= (size + 1) - j )
					printf("*");
				else
					printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}

int type2(int size)
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= (size + 1) / 2; j++)
		{
			if (i <= (size + 1) / 2)
			{
				if ((size+1)/2+1-i<=j)
					printf("*");
				else
					printf(" ");
			}
			else
			{
				if (i-(size-1)/2 <= j)
					printf("*");
				else
					printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}

int type3(int size)
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (i <= (size + 1) / 2)
				if (i <= j && (size + 1) - j >= i)
					printf("*");
				else
					printf(" ");
			else
				if (j >= size + 1 - i && (size + 1) - j >= size + 1 - i)
					printf("*");
				else
					printf(" ");
		}
		printf("\n");
	}
	return 0;
}

int type4(int size)
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (i <= (size + 1) / 2)
				if (i <= j && j<=(size+1)/2)
					printf("*");
				else
					printf(" ");
			else
				if (j >=(size+1)/2 && (size + 1) - j >= size + 1 - i)
					printf("*");
				else
					printf(" ");
		}
		printf("\n");
	}
	return 0;
}
