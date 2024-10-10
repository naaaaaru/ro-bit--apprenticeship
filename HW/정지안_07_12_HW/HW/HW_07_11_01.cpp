#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
    int num;
    char name[30];
    char country[30];
    char prov[30];
    char city[30];
    char district[30];
    int grade;
} student;

int main() 
{
    student students[100];
    int count = 0;
    int opp, opp2;

    FILE* file = fopen("students.txt", "r");
    if (file != NULL) 
    {
        while (fscanf(file, "%d %s %s %s %s %s %d", &students[count].num, students[count].name, students[count].country, students[count].prov, students[count].city, students[count].district, &students[count].grade) != -1)
        {
            count++;
        }
        fclose(file);
    }

    while (1)
    {
        printf("숫자를 입력하세요\n학생을 추가하려면 : 1\n학생을 삭제하려면 : 2\n학생을 찾으려면 : 3\n학생을 정렬하려면 : 4\n학생 목록을 저장하려면 : 5\n종료하려면 : 6\n");
        scanf("%d", &opp);

        if (opp == 1) 
        {
            if (count >= 100) 
            {
                printf("학생을 더 이상 추가할 수 없습니다.\n");
            }
            else
            {
                printf("학생 번호: ");
                scanf("%d", &students[count].num);
                printf("학생 이름: ");
                scanf("%s", students[count].name);
                printf("나라: ");
                scanf("%s", students[count].country);
                printf("도: ");
                scanf("%s", students[count].prov);
                printf("시: ");
                scanf("%s", students[count].city);
                printf("구: ");
                scanf("%s", students[count].district);
                printf("성적: ");
                scanf("%d", &students[count].grade);
                count++;
            }
        }
        else if (opp == 2) 
        {
            int num;
            printf("삭제할 학생의 번호를 입력하세요: ");
            scanf("%d", &num);
            for (int i = 0; i < count; i++) 
            {
                if (students[i].num == num) 
                {
                    for (int j = i; j < count - 1; j++)
                    {
                        students[j] = students[j + 1];
                    }
                    count--;
                    break;
                }
            }
        }
        else if (opp == 3) 
        {
            int num;
            printf("찾을 학생의 번호를 입력하세요: ");
            scanf("%d", &num);
            for (int i = 0; i < count; i++) 
            {
                if (students[i].num == num) 
                {
                    printf("번호: %d, 이름: %s, 나라: %s, 도: %s, 시: %s, 구: %s, 성적: %d\n",
                        students[i].num, students[i].name, students[i].country, students[i].prov, students[i].city, students[i].district, students[i].grade);
                    break;
                }
            }
        }
        else if (opp == 4) 
        {
            printf("어떤 순서로 학생을 정렬할건지 숫자를 입력하세요\n번호순 : 1\n이름순 : 2\n성적순 : 3\n");
            scanf("%d", &opp2);
            if (opp2 == 1) 
            {
                for (int i = 0; i < count - 1; i++) 
                {
                    for (int j = 0; j < count - i - 1; j++) 
                    {
                        if (students[j].num > students[j + 1].num) 
                        {
                            student temp = students[j];
                            students[j] = students[j + 1];
                            students[j + 1] = temp;
                        }
                    }
                }
            }
            else if (opp2 == 2) 
            {
                for (int i = 0; i < count - 1; i++) 
                {
                    for (int j = 0; j < count - i - 1; j++) 
                    {
                        if (strcmp(students[j].name, students[j + 1].name) > 0)
                        {
                            student temp = students[j];
                            students[j] = students[j + 1];
                            students[j + 1] = temp;
                        }
                    }
                }
            }
            else if (opp2 == 3) 
            {
                for (int i = 0; i < count - 1; i++) 
                {
                    for (int j = 0; j < count - i - 1; j++) 
                    {
                        if (students[j].grade < students[j + 1].grade) 
                        {
                            student temp = students[j];
                            students[j] = students[j + 1];
                            students[j + 1] = temp;
                        }
                    }
                }
            }
            else 
            {
                printf("잘못된 선택입니다.\n");
            }
            for (int i = 0; i < count; i++) 
            {
                printf("번호: %d, 이름: %s, 나라: %s, 도: %s, 시: %s, 구: %s, 성적: %d\n",students[i].num, students[i].name, students[i].country, students[i].prov, students[i].city, students[i].district, students[i].grade);
            }
        }
        else if (opp == 5) 
        {
            FILE* file = fopen("students.txt", "w");
            if (file == NULL) 
            {
                printf("파일을 열 수 없습니다.\n");
            }
            else {
                for (int i = 0; i < count; i++) 
                {
                    fprintf(file, "%d %s %s %s %s %s %d\n", students[i].num, students[i].name, students[i].country, students[i].prov, students[i].city, students[i].district, students[i].grade);
                }
                fclose(file);
            }
        }
        else if (opp == 6) 
        {
            FILE* file = fopen("students.txt", "r");
            if (file == NULL) 
            {
                printf("파일을 열 수 없습니다.\n");
            }
            else 
            {
                count = 0;
                while (fscanf(file, "%d %s %s %s %s %s %d", &students[count].num, students[count].name, students[count].country, students[count].prov, students[count].city, students[count].district, &students[count].grade) != -1) 
                {
                    count++;
                }
                fclose(file);
            }
        }
        else if (opp == 7) 
        {
            FILE* file = fopen("students.txt", "w");
            if (file != NULL) 
            {
                for (int i = 0; i < count; i++) 
                {
                    fprintf(file, "%d %s %s %s %s %s %d\n", students[i].num, students[i].name, students[i].country, students[i].prov, students[i].city, students[i].district, students[i].grade);
                }
                fclose(file);
            }
            break;
        }
        else 
        {
            printf("잘못된 숫자입니다.\n");
        }
    }
    return 0;
}