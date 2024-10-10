#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct //좌표 구조체
{
    int x;
    int y;
} Point;

double distance(Point a, Point b) //거리 계산 함수
//x,y 두개의 변수가 저장된 구조체 2개를 받으면 숫자 4개로 두 점사이의 거리를 계산
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));//math.h의 sqrt=제곱근
}

void main() 
{
    int num;
    Point* points;

    printf("입력 : ");
    scanf_s("%d", &num);//점의 개수 입력

    points = (Point*)malloc(sizeof(Point) * num);//동적할당

    for (int i = 0; i < num; i++) 
    {
        scanf_s("%d %d", &points[i].x, &points[i].y);//좌표 입력
    }

    Point maxpoint = points[0];
    double maxdistancesum = 0;//변수 초기화

    for (int i = 0; i < num; i++) //i가 먼저 고정되서 커지는 j와 비교
    {
        double distancesum = 0;
        for (int j = 0; j < num; j++) 
        {
            if (i != j) //서로 다른 두 점일때
            {
                distancesum += distance(points[i], points[j]);//i와 다른 점들의 거리를 합산
            }
        }
        if (distancesum > maxdistancesum)//i가 커지면서 가장 멀리 떨어져있는 좌표 찾기
        {
            maxdistancesum = distancesum;
            maxpoint = points[i];//가장 멀리 떨어져 있는 좌표 주소 저장
        }
    }

    printf("가장 거리가 먼 좌표는 (%d, %d)이며, 다른 좌표의 거리 총합은 약 %lf입니다.\n", maxpoint.x, maxpoint.y, maxdistancesum);//출력
    free(points);//동적 할당 해제
}