#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    int min, max;
    int arr[10001] = { 0, };
    int resultCount = 0;

    printf("min :");
    scanf_s("%d", &min);
    printf("max :");
    scanf_s("%d", &max);

    for (int j = min; j <= max; j++)
    {
        arr[j] = j;
    }
    for (int k = min; k <= max; k++)
    {
        int index = 1;
        for (int num = 2; num * num <= arr[k]; num++)
        {
            if (arr[k] % (num * num) == 0)
            {
                if (arr[k] / (num * num) == 1)
                {
                    index = 0;
                    break;
                }
            }
        }
        if (index==1)
        {
            if (k != 1)
            {
                resultCount++;
            }
        }
    }

    printf("제곱 ㄴㄴ수 : %d개\n", resultCount);
    return 0;
}
