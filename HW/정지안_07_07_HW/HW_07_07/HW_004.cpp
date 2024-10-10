#include <stdio.h>

typedef struct _date 
{
    int year, month, day, hour, min, sec;
} date;

// 윤년인지 확인 
int leapyear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 월별 일수를 반환하는 함수
int daysum(int year, int month) 
{
    if (month == 2)
    {
        if (leapyear(year) == 1)//윤년이라면
        {
            return 28;//28일
        }
        else
            return 29;//아니면 29일
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) //30일 있는 달
    {
        return 30;
    }
    else
    {
        return 31;//나머지는 다 31일
    }
}

void main() 
{
    int yearcount, monthcount, daycount, hourcount, mincount, seccount, resultcount;
    int printhour, printmin, printsec;
    date list[2];//년,달,월,일,시,분,초가 포함되어있는 구조체 2개
    printf("입력 : \n");
    for (int i = 0; i < 2; i++) 
    {
        scanf_s("%d %d %d %d %d %d", &list[i].year, &list[i].month, &list[i].day, &list[i].hour, &list[i].min, &list[i].sec);
    }

    // 년도 차이 계산
    yearcount = (list[1].year - list[0].year) * 365 * 24 * 60 * 60;

    // 월 차이 계산
    monthcount = 0;
    if (list[1].year == list[0].year)//연도 차이가 안날때
    {
        if (list[1].month > list[0].month) 
        {
            for (int i = list[0].month; i < list[1].month; i++) //i가 달 차이 수만큼 반복
            {
                monthcount += daysum(list[0].year, i) * 24 * 60 * 60;//달마다 일수 총합
            }
        }
    }
    else //연도 차이가 날때
    {
        for (int i = list[0].month; i <= 12; i++) //다음 년까지 남은 달의 수
        {
            monthcount += daysum(list[0].year, i) * 24 * 60 * 60;
        }
        for (int i = 1; i < list[1].month; i++) //다음 년부터 지나갈 달의 수
        {
            monthcount += daysum(list[1].year, i) * 24 * 60 * 60;
        }
    }
    //만약 나중 시간이 전 시간 보다 적은 계산 값이 있다면 -로 계산됨
    // 일 차이 계산
    daycount = (list[1].day - list[0].day) * 24 * 60 * 60;

    // 시간, 분, 초 차이 계산
    hourcount = (list[1].hour - list[0].hour) * 60 * 60;
    mincount = (list[1].min - list[0].min) * 60;
    seccount = list[1].sec - list[0].sec;

    // 총 초 계산
    resultcount = yearcount + monthcount + daycount + hourcount + mincount + seccount;

    // 초를 시, 분, 초로 변환
    printhour = (resultcount - (resultcount % 3600)) / 3600;
    printsec = (resultcount - (printhour * 3600)) % 60;
    printmin = (resultcount - (printhour * 3600) - printsec) / 60;

    // 출력
    printf("%d시 %d분 %d초", printhour, printmin, printsec);
}