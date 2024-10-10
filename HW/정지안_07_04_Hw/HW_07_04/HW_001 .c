#include <stdio.h>
#include <stdlib.h>

void print(int** arr, int N1, int N2);

int main() 
{
    int N1, N2;
    printf("입력: ");
    scanf_s("%d %d", &N1, &N2);

 
    int** arr = (int**)malloc(N1 * sizeof(int*));
    for (int i = 0; i < N1; ++i) 
    {
        arr[i] = (int*)malloc(N2 * sizeof(int));
        for (int j = 0; j < N2; ++j) 
        {
            arr[i][j] = 0;
        }
    }

 
    print(arr, N1, N2);

    for (int i = 0; i < N1; ++i)
    {
        for (int j = 0; j < N2; ++j)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N1; ++i) 
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

void print(int** arr, int N1, int N2)
{
    int num = N1 * N2;
    int x = (N2+1)/2, y = (N1+1)/2;
    int direction = 1;
    y++;
    while (num <=(N1*N2))
    {
        arr[y][x] = num++;
        if (direction == 0)//우하향
        {
            if (y + 1 < N1 && arr[y + 1][x] == 0)
            {
                y++;
                x++;
            }
            else 
            {
                direction = 1;
                x++;
            }
        }
        else if (direction == 1) //우상향
        {
            if (x + 1 < N2 && arr[y][x + 1] == 0)
            {
                x++;
                y--;
            }
            else
            {
                direction = 2;
                y--;//상향
            }
        }
        else if (direction == 2)//좌상향
        {
            if (y - 1 >= 0 && arr[y - 1][x] == 0)
            {
                x--;
                y--;
            }
            else {
                direction = 3;
                x--;//좌향
            }
        }
        else if (direction == 3)//좌하향
        {
            if (x - 1 >= 0 && arr[y][x - 1] == 0)
            {
                y++;
                x++;
            }
            else
            {
                direction = 0;
                y++;//하향
            }
        }

    }
}
