#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() 
{
    int num;
    printf("정수를 입력하세요: ");
    scanf("%d", &num);

    for (int i = 1; i <= num; i++) 
    {
        for (int j = 1; j <= i; j++) 
        {
            printf("*");
        }
        for (int j = 1; j <= 2 * (num - i); j++)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    for (int i = num - 1; i >= 1; i--) 
    {
        for (int j = 1; j <= i; j++) 
        {
            printf("*");
        }
        for (int j = 1; j <= 2 * (num - i); j++) 
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++) 
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
