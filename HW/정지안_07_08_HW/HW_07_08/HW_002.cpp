#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main() 
{
    int i, j;
    int num[12];
    int* pnum = num; 
    int printnum[12];
    int* pprintnum = printnum; 

    printf("input : ");
    scanf_s("%d", &pnum[0]); 

    for (i = 0; i < 12; i++) 
    {
        pprintnum[i] = pnum[0];
    }

    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 4; b++) {
            printf("%d", pprintnum[a * 4 + b]); 
        }
        printf("\n");
    }

    while (1)
    { 
        printf("next input : ");
        scanf_s("%d", &pnum[j]); 

        for (j = 1; j < 12; j++)
        {
            printf("next input : ");
            scanf_s("%d", &num[j]);
            for (int p = 0; p <= j; p++)
                for (int k = 0; k < 12 / (j + 1); k++)
                {
                    printnum[p + (p + 1) * k] = num[p];
                }
        for (int a = 0; a < 3; a++)
        {
            for (int b = 0; b < 4; b++) 
            {
                printf("%d", pprintnum[a * 4 + b]); 
            }
            printf("\n");
        }
    }
    return 0;
}
