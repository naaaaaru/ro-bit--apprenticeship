#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int check(int N, int B, int A[]) 
{
    int count = 0;
    int length;
    int t;
    int i;
    for (length = 1; length <= N; length += 2)//길이가 홀수여야 중앙값이 내부에 포함됨
    {
        for (t = 0; t <= N - length; t++)// 길이에 따른 부분수열 종류
        {
            int subA[100];
            for (i = 0; i < length; i++)
            {
                subA[i] = A[t + i];//부분함수 생성
            }

            for (i = 0; i < length - 1; i++) 
            {
                for (int j = 0; j < length - i - 1; j++)
                {
                    if (subA[j] > subA[j + 1]) //부분 수열 정렬
                    {
                        int temp = subA[j];
                        subA[j] = subA[j + 1];
                        subA[j + 1] = temp;
                    }
                }
            }
            int mid = length / 2;
            if (subA[mid] == B)
            {
                count++;
            }
        }
    }

    return count;
}

int main() 
{
    int N, B;
    int A[100] = { 0, };

    printf("N : ");
    scanf("%d", &N);
    printf("B : ");
    scanf("%d", &B);
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &A[i]);
    }
    int result = check(N, B, A);
    printf("중앙값이%d인 부분수열의 개수 : %d\n",B,result);

    return 0;
}
