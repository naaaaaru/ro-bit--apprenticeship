#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    int min, max;//입력값
    int arr[10001] = { 0, };//정수 갯수+끝 null
    int resultCount = 0;//실제 닶

    printf("min :");
    scanf_s("%d", &min);
    printf("max :");
    scanf_s("%d", &max);

    for (int j = min; j <= max; j++)
    {
        arr[j] = j;//배열 "min"번 부터 "max"번까지를 각각 숫자로 채움
    }
    for (int k = min; k <= max; k++)
    {
        int index = 1;//제곱인지 검사 변수
        for (int num = 2; num * num <= arr[k]; num++)
            //num이 1씩 커지면서 배열이 num의 제곱인지 검사,
            //배열의 숫자보다 더 큰수로 나누면 무조건 나머지는 0이 아니기 때문에 num^2이 배열보다 작거나 같을때까지
        {
            if (arr[k] % (num * num) == 0)//제곱수로 나누었을때 나머지가 0이 되는 경우
            {
                if (arr[k] / (num * num) == 1)//제곱수를 소인수로 가지면서 제곱이 아닌경우를 제외
                    //ex)12=2x2x3
                {
                    index = 0;//제곱일때를 갯수세기에서 제외
                    break;
                }
            }
        }
        if (index == 1)//제곱이 아니라면
        {
            if (k != 1)//1은 제곱x
            {
                resultCount++;//갯수+1
            }
        }
    }

    printf("제곱 ㄴㄴ수 : %d개\n", resultCount);
    return 0;
}
