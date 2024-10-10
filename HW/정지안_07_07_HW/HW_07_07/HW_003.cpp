#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

// 물품 가격 구조체
typedef struct 
{
    char name[50];
    int price;
} Item;

int main() 
{
    int num;
    printf("입력 : ");
    scanf_s("%d", &num);

    // 동적 할당
    Item* itemlist = (Item*)malloc(sizeof(Item)*num);

    // 물품과 금액 입력 받기
    for (int i = 0; i < num; i++) 
    {
        scanf_s("%s",itemlist[i].name, sizeof(itemlist[i].name));
        scanf_s("%d", &itemlist[i].price);
    }

    // 합계를 구할 물품 이름 입력 받기
    char check[20];
    scanf_s("%s", check, sizeof(check));

    // 합계 계산
    int sum = 0;//변수 초기화
    for (int i = 0; i < num; i++) 
    {
        if (strcmp(itemlist[i].name, check) == 0)//합계를 구할 물품의 이름이라면
        {
            sum += itemlist[i].price;//합계 계산
        }
    }

    // 결과 출력
    printf("출력 : %d\n", sum);//금액 입력이 없던 이름이라면 sum=0

    // 동적 할당 메모리 해제
    free(itemlist);
    return 0;
}