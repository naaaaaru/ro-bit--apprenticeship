#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	int N, B;
	int result;
	int input;
	printf("N : ");
	scanf_s("%d", &N);
	printf("B : ");
	scanf_s("%d", &B);
	int arr[999] = { 0, };
	for (int i = 0; i < N; i++)
	{
		scanf_s("%d", &input);
		arr[i] = input;
	}
	int higher=0, lower=0;
	for (int a = 0; a < N; a++)
		if (arr[a] > B)
			higher++;
		else if (arr[a] < B)
			lower++;
	result = (higher > lower) ? lower : higher;
	result++;
	printf("중앙값이 %d인 부분수열의 개수 : %d", B, result);
}