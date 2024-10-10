#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int func(char* str);

int main()
{
    char strInput[9];

    printf("음 입력 :\n");
    scanf("%s", strInput); 

    switch (func(strInput))
    {
    case 1:
        printf("ascending");
        break;
    case 2:
        printf("descending");
        break;
    default:
        printf("mixed");
        break;
    }

    return 0;
}

int func(char* str)
{
    if (str[0] == 'c'
        && str[1] == 'd'
        && str[2] == 'e'
        && str[3] == 'f'
        && str[4] == 'g'
        && str[5] == 'a'
        && str[6] == 'b'
        && str[7] == 'C')
        return 1;
    else if (str[0] == 'C'
        && str[1] == 'b'
        && str[2] == 'a'
        && str[3] == 'g'
        && str[4] == 'f'
        && str[5] == 'e'
        && str[6] == 'd'
        && str[7] == 'c')
        return 2;
    else
        return 0;
}
