#include <stdio.h>
#include <stdlib.h>

void print(int** arr, int sizeX, int sizeY);
void arr_ij(int** arr, int sizeX, int sizeY);

int main()
{
    int** arr;
    int row, col;

    printf("열의 수를 입력하세요: ");
    scanf_s("%d", &col);
    printf("행의 수를 입력하세요: ");
    scanf_s("%d", &row);

    arr = (int**)malloc(sizeof(int*) * row);//행 동적 할당
    for (int i = 0; i < row; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * col);//열 동적할당
        
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            arr[i][j] = 0; // 배열 초기화
        }
    }

    arr_ij(arr, row, col);//2차원 배열에 숫자 입력
    print(arr, row, col);//도형 출력

    for (int i = 0; i < row; i++) 
    {
        free(arr[i]);//열 동적 할당 해제
    }
    free(arr);//행 동적 할당 해제

    return 0;
}

void print(int** arr, int sizeX, int sizeY) 
{
    for (int i = 0; i < sizeX; i++) 
    {
        for (int j = 0; j < sizeY; j++)
        {
            printf("%3d ", arr[i][j]);//숫자가 출력될때 밀리지 않게 하기 위해 %3d, 만약 4가 출력 된다면 4가 아닌 004가 출력됨(00은 스페이스로 출력됨)
        }
        printf("\n");
    }
}

void arr_ij(int** arr, int sizeX, int sizeY) 
{
    int direction = 1;
    int x = 0, y = 0;
    for (int i = 1; i <= sizeX * sizeY; i++) //1부터 행x열(사각형의 크기)의 개수만큼 반복
    {
        arr[x][y] = i;//2차원 배열에 숫자 입력
        switch (direction) 
        {
        case 1: // 우향
            if (y + 1 < sizeY && arr[x][y + 1] == 0)//우측 벽에 닿지 않을때=진행방향이 열의 크기보다 작거나 숫자가 차있지 않을때
            {
                y++;
            }
            else {
                direction = 2;//하향으로 방향전환
                x++;
            }
            break;
        case 2: // 하향
            if (x + 1 < sizeX && arr[x + 1][y] == 0) 
            {
                x++;
            }
            else 
            {
                direction = 3;//좌향으로 방향 전환
                y--;
            }
            break;
        case 3: // 좌향
            if (y - 1 >= 0 && arr[x][y - 1] == 0)
            {
                y--;
            }
            else {
                direction = 4;//상향으로 방향전환
                x--;
            }
            break;
        case 4: // 상향
            if (x - 1 >= 0 && arr[x - 1][y] == 0) 
            {
                x--;
            }
            else 
            {
                direction = 1;//우향으로 방향 전환
                y++;
            }
            break;
        }
    }
}
