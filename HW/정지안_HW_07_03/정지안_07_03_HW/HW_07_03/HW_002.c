#include<stdio.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

int main() {
    int set[21] = { 0, };//집합 배열
    int num;//숫자 입력 변수
    char op[10] = { 0, };//연산 변수
    int index = 0;//배열의 주소 변수
    printf("연산을 선택하세요. (1 <= x <= 20)\n");
    printf("add X\nremove X\ncheck X\ntoggle X\nall 0\nempty 0\n");

    while (1)//무한 반복
    {
        printf("\ninput : ");
        scanf_s("%s", op, 30);
        scanf_s("%d", &num);

        if (strcmp(op, "add") == 0)//add의 경우
        {
            int check1 = 0;
            for (int i = 0; i < index; i++) //중복 검사
            {
                if (set[i] == num)//배열중 중복되는 숫자가 있다면 연산을 무시
                {
                    check1 = 1;
                    break;
                }
            }
            if (check1 == 0)
            {
                set[index] = num;//자리가 비어있는 가장 앞번 주소부터 채움
                index++;//배열을 채웠기 때문에 주소+1
            }
        }

        else if (strcmp(op, "remove") == 0)
        {
            for (int i = 0; i < index; i++)//숫자 검사
            {
                if (set[i] == num)//삭제하려는 숫자의 주소==i
                {
                    for (int k = i; k <= index - 1; k++)//배열의 끝주소 전 까지 반복
                    {
                        set[k] = set[k + 1];//배열의 숫자를 한칸씩 앞으로 당기기
                    }
                    index--;//숫자 하나가 사라졌기때문에 주소 -1
                    break;
                }
                else//삭제 하려는 숫자가 없을때 연산 무시
                    break;
            }
        }

        else if (strcmp(op, "check") == 0)
        {
            int numCheck = 0;//숫자가 검사되지 않았다면 0출력
            for (int i = 0; i < index; i++)//배열 검사
            {
                if (set[i] == num)
                {
                    numCheck = 1;//숫자가 검사되었다면 1출력
                    break;
                }
                else
                    break;
            }
            printf("%d\n", numCheck);
        }

        else if (strcmp(op, "toggle") == 0)
        {
            int check2 = 0;
            for (int i = 0; i < index; i++)
            {
                if (set[i] == num)
                {
                    for (int k = i; k < index - 1; k++)//숫자가 있다면 'remove알고리즘' 
                    {
                        set[k] = set[k + 1];
                    }
                    index--;
                    check2 = 1;
                    break;
                }
            }
            if (check2 == 0)
            {
                set[index] = num;//숫자가 없다면 'add알고리즘'
                index++;
            }
        }

        else if (strcmp(op, "all") == 0)
        {
            for (int i = 0; i < 20; i++)
            {
                set[i] = i + 1;//20까지 배열의 각 자리에 숫자 채우기
            }
            index = 20;//배열 주소는 20까지 밀기
        }

        else if (strcmp(op, "empty") == 0)
        {
            for (int i = 0; i < 20; i++) //배열내 숫자 전부 초기화
            {
                set[i] = 0;
            }
            index = 0;//다 삭제 되었으므로 배열 주소는 0
        }

        else
        {
            continue;//연산자가 잘못입력된 경우 그냥 무시
        }

        printf("집합 : {");//출력의 앞 "집합 : {"구현
        for (int i = 0; i < index; i++)
        {
            printf("%d", set[i]);
            if (i < index - 1)
            {
                printf(", ");
            }
        }
        printf(" }\n");//출력의 뒤 "}"구현
    }
}
