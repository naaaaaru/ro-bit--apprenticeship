#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() 
{
    double num1, num2, result = 0;
    char operation;

    printf("Input Arithmetic Operation\nex) 3.4 + 8.5\n    2.9 - 5.4\n    3.9 * 8.0\n    3.9 ^ 8\n\ninput : ");
    scanf("%lf %c %lf", &num1, &operation, &num2);

    switch (operation) 
    {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '/':
        if (num2 != 0) 
        {
            result = num1 / num2;
        }
        else {
            printf("0으로 나눌 수는 없습니다.\n");
            return 1; // 프로그램을 종료합니다.
        }
        break;
    case '*':
        result = num1 * num2;
        break;
    case '^':
        result = 1;
        for (int i = 0; i < (int)num2; i++) 
        {
            result *= num1;
        }
        break;
    default:
        printf("잘못된 연산자입니다.\n");
        return 1; // 프로그램을 종료합니다.
    }

    printf("%lf %c %lf = %lf\n", num1, operation, num2, result);
    return 0;
}
