#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void sort(int arr[], int n);
int main()
{
	int arr[8] = { 0, };
	int input;
	int i;
	printf("입력 : \n");
	for (i = 0; i < 8; i++)
	{
		printf("%d : ", i);
		scanf_s("%d", &input);
		arr[i] = input;
	}
	sort(arr, i);
	printf("출력\n");
	for (int k = 0; k < 8; k++)
	{
		printf("%d : %d\n", k, arr[k]);
	}

}
void sort(int arr[], int n)
{
	int num;
	for (int i = n - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				num = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = num;
			}
		}
		for (int l = 0; l < 8; l++)
			printf("%d ", arr[l]);
		printf("\n");
	}
}
