#include<stdio.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

void stringswap(char* str);
char freqchar(char* str);

int main()
{
    char str[100];

    printf("입력 : ");
    scanf("%[^\n]", str);

    stringswap(str);
    printf("출력: %s\n", str);

    char frequentChar = freqchar(str);
    printf("최다 등장 문자: %c\n", frequentChar);

    return 0;
}

void stringswap(char* str)
{
    int len = strlen(str);
    char temp;
    for (int i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char freqchar(char* str)
{
    int len = strlen(str);
    char maxcountchar = 0;
    int maxcount = 0;
    for (int i = 0; i < len; i++)
    {
        int count = 0;
        for (int j = 0; j < len; j++)
        {
            if (str[i] == str[j])
                count++;
        }
        if (count > maxcount)
        {
            maxcount = count;
            maxcountchar = str[i];
        }
    }
    return maxcountchar;
}
