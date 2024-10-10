#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define SIZE 5

typedef struct _student
{
	int number;
	double grade;
	char name[10];
} student;

void main()
{
	student list[SIZE];
	int i, j;
	student temp;

	for (i = 0; i < SIZE; i++)
	{
		printf("학년을 입력하시오: ");
		scanf_s("%d", &list[i].number);
		printf("학점을 입력하시오: ");
		scanf_s("%lf", &list[i].grade);
		printf("이름을 입력하시오: ");
		scanf_s("%s", list[i].name, sizeof(list[i].name));
		//그동안 해결 못하던 문제인데 scanf로 문자를 읽을때 문자열의 크기도 지정해줘야 된다고 가르쳐 주셔서 감사합니다
	}

	// 정렬
	for (i = 0; i < SIZE - 1; i++)
	{
		for (j = 0; j < SIZE - 1 - i; j++)
		{
			if (list[j].number > list[j + 1].number || //1순위 학년
				(list[j].number == list[j + 1].number && list[j].grade > list[j + 1].grade) ||//2순위 학년이 같을때 성적
				(list[j].number == list[j + 1].number && list[j].grade == list[j + 1].grade && strcmp(list[j].name, list[j + 1].name) > 0))
				//3순위 학년 성적이 같을때 문자,문자는 사전식 배열로
			{
				// 순서 배열 list[]의 순서를 배열하면 구조체 안 숫자 두개와 문자가 동시에 바뀜
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

	// 출력
	for (i = 0; i < SIZE; i++)
	{
		printf("학년 : %d 학점 : %f 이름 : %s\n", list[i].number, list[i].grade, list[i].name);
	}
}
