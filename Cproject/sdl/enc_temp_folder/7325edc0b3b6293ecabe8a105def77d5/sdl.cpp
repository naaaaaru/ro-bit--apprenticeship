#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 좌표를 나타내는 구조체
typedef struct
{
    int x, y;
} Point;

typedef struct
{
    Point data[100]; 
    int front;
    int rear;
} Queue;

void drawLine(SDL_Renderer* renderer);
void drawRectangle(SDL_Renderer* renderer, Point pt, SDL_Color color);
void drawPath(SDL_Renderer* renderer, Point* path, int path_length, SDL_Color color);
int distance(Point* path, int path_length);
void setCheckpoint(int maze[10][10], Point* checkpoint);
void _Queue(Queue* q);
int isQueueEmpty(Queue* q);
int isQueueFull(Queue* q);
void enqueue(Queue* q, Point p);
Point dequeue(Queue* q);
int isPathAvailable(int maze[10][10], Point start, Point end);

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL; // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);  // 윈도우 창 생성
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // 렌더러 생성
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Color playerColor = { 255, 0, 0, 255 }; // 움직이는 사각형 빨간색
    SDL_Color wallColor = { 255, 255, 255, 255 }; // 벽 하얀색
    SDL_Color doorColor = { 0, 255, 0, 255 }; // 입출구 초록색
    SDL_Color pathColor = { 255, 255, 255, 255 }; // 궤적 하얀색
    SDL_Color checkpointColor = { 0, 0, 255, 255 }; // 체크포인트 파란색

    Point player = { 0, 9 }; // 사각형 시작 위치
    Point entry = { 0, 9 }; // 입구 위치
    Point exit = { 9, 0 }; // 출구 위치

    int maze[10][10] = { 0 }; // 미로 배열 초기화 (0: 빈 공간, 1: 벽)
    int edit = 1; // 편집 모드 변수

    Point path[1000]; // 플레이어 궤적 기록 배열
    int pathLength = 0;

    int distances[100]; // 각 시도의 이동 거리 기록 배열
    int attemptCount = 0; // 시도 횟수

    Point checkpoint; // 체크포인트
    setCheckpoint(maze, &checkpoint); // 체크포인트 설정

    SDL_Event e; // SDL 이벤트 처리 구조체 (마우스 클릭, 키 입력 등을 처리함)
    int checkpointReached = 0; // 체크포인트 도달 여부

    while (1) // 프로그램 정지까지 반복
    {
        while (SDL_PollEvent(&e)) // 처리할 이벤트 e가 있다면 실행
        {
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_SPACE:
                    if (edit == 1)
                    {
                        edit = 0;
                        pathLength = 0;
                        player = entry; // 플레이어 시작위치에
                        path[pathLength] = player; // 시작 위치 기록
                        pathLength++;
                        checkpointReached = 0; // 체크포인트 도달 여부 초기화
                    }
                    break;
                case SDLK_RETURN:
                    if (attemptCount > 0)
                    {
                        int minDistance = distances[0];
                        for (int i = 1; i < attemptCount; ++i)
                        {
                            if (distances[i] < minDistance)
                            {
                                minDistance = distances[i];
                            }
                        }
                        printf("최단 경로 거리는 : %d\n", minDistance);

                        FILE* file = fopen("result.txt", "w");
                        if (file != NULL) 
                        {
                            fprintf(file, "최단 경로 거리: %d\n", minDistance);
                            fclose(file);
                        }
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 0;
                    }
                    break;
                case SDLK_w:
                    if (edit == 0 && player.y > 0 && maze[player.y - 1][player.x] == 0)
                        player.y--;
                    break;
                case SDLK_s:
                    if (edit == 0 && player.y < 9 && maze[player.y + 1][player.x] == 0)
                        player.y++;
                    break;
                case SDLK_a:
                    if (edit == 0 && player.x > 0 && maze[player.y][player.x - 1] == 0)
                        player.x--;
                    break;
                case SDLK_d:
                    if (edit == 0 && player.x < 9 && maze[player.y][player.x + 1] == 0)
                        player.x++;
                    break;
                }
                if (edit == 0)
                {
                    path[pathLength] = player; // 궤적 기록
                    pathLength++;

                    if (player.x == checkpoint.x && player.y == checkpoint.y)
                    {
                        checkpointReached = 1; // 체크포인트 도달 표시
                    }

                    if (player.x == exit.x && player.y == exit.y)
                    {
                        if (checkpointReached==1)
                        {
                            distances[attemptCount] = distance(path, pathLength);
                            attemptCount++;

                            pathLength = 0;
                            player = entry;
                            path[pathLength] = player;
                            pathLength++;
                            checkpointReached = 0; // 다음 시도를 위해 체크포인트 도달 여부 초기화
                        }
                        else
                        {
                            // 체크포인트를 지나지 않고 출구에 도착한 경우
                            pathLength = 0;
                            player = entry;
                            path[pathLength] = player;
                            pathLength++;
                            checkpointReached = 0; // 체크포인트 도달 여부 초기화
                        }
                    }
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (edit == 1)
                {
                    int x = e.button.x / 60;
                    int y = e.button.y / 60;

                    if (maze[y][x] == 1)
                        maze[y][x] = 0; // 벽 지우기
                    else
                        maze[y][x] = 1; // 벽 그리기

                    if (!isPathAvailable(maze, entry, exit))
                    {
                        printf("경로가 불가능합니다. 벽을 다시 수정하세요.\n");
                        maze[y][x] = 0; // 마지막 벽 수정 취소
                    }
                    else if (x == checkpoint.x && y == checkpoint.y)
                    {
                        setCheckpoint(maze, &checkpoint);
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawLine(renderer);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (maze[i][j] == 1)
                {
                    Point wallpoint = { j, i };
                    drawRectangle(renderer, wallpoint, wallColor);
                }
            }
        }

        drawRectangle(renderer, entry, doorColor);
        drawRectangle(renderer, exit, doorColor);
        drawRectangle(renderer, player, playerColor);
        drawRectangle(renderer, checkpoint, checkpointColor);

        if (edit == 0)
        {
            drawPath(renderer, path, pathLength, pathColor);
        }

        SDL_RenderPresent(renderer);
    }
}

void drawLine(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i <= 10; ++i)
    {
        SDL_RenderDrawLine(renderer, i * 60, 0, i * 60, 600);
        SDL_RenderDrawLine(renderer, 0, i * 60, 600, i * 60);
    }
}

void drawRectangle(SDL_Renderer* renderer, Point pt, SDL_Color color)
{
    SDL_Rect rect = { pt.x * 60, pt.y * 60, 60, 60 };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void drawPath(SDL_Renderer* renderer, Point* path, int path_length, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int i = 0; i < path_length - 1; i++)
    {
        SDL_RenderDrawLine(renderer, path[i].x * 60 + 30, path[i].y * 60 + 30,
            path[i + 1].x * 60 + 30, path[i + 1].y * 60 + 30);
    }
}

int distance(Point* path, int path_length) 
{
    int totalDistance = 0;
    for (int i = 0; i < path_length - 1; ++i)
    {
        int distanceX = abs(path[i].x - path[i + 1].x);
        int distanceY = abs(path[i].y - path[i + 1].y);
        totalDistance += distanceX + distanceY;
    }
    return totalDistance;
}

void setCheckpoint(int maze[10][10], Point* checkpoint)
{
    srand((unsigned int)time(NULL));//시간을 인자로 랜덤값 생성

    int x, y;
    int check = 0;

    while (check == 0)
    {
        x = rand() % 10;
        y = rand() % 10;

        if (!(x == 0 && y == 9) && !(x == 9 && y == 0))
        {
            checkpoint->x = x;
            checkpoint->y = y;
            check = 1;
        }
    }
}

// 큐 관련 함수
void _Queue(Queue* q)
{
    q->front = 0;
    q->rear = 0;
}

int isQueueEmpty(Queue* q)
{
    return q->front == q->rear;
}

int isQueueFull(Queue* q)
{
    return q->rear + 1 == q->front;
}

void enqueue(Queue* q, Point p)
{
    if (q->rear + 1 != q->front)
    {
        q->data[q->rear] = p;
        q->rear = q->rear + 1;
    }
}

Point dequeue(Queue* q)
{
    if (q->front == q->rear)
    {
        printf("Queue is empty\n");
        Point empty = { -1, -1 };
        return empty;
    }
    Point p = q->data[q->front];
    q->front = (q->front + 1) % 100;
    return p;
}

// BFS를 사용한 경로 찾기
int isPathAvailable(int maze[10][10], Point start, Point end)
{
    int visited[10][10] = { 0 };//방문 배열 visited를 초기화,0=방문하지 않음
    Queue q;
    _Queue(&q);

    // 시작점을 큐에 추가
    enqueue(&q, start);
    visited[start.y][start.x] = 1;

    while (!isQueueEmpty(&q))
    {
        Point current = dequeue(&q);

        // 도착점에 도달한 경우
        if (current.x == end.x && current.y == end.y)
        {
            return 1; // 경로가 존재함
        }

        current.x--;
        if (current.x >= 0 && current.x < 10 && current.y >= 0 && current.y < 10 && !visited[current.y][current.x] && maze[current.y][current.x] == 0)
        {
                // 새 점을 방문한 것으로 표시하고 큐에 추가
                visited[current.y][current.x] = 1;
                Point newPoint = { current.x, current.y };
                enqueue(&q, newPoint);
        }
        current.y--;
        if (current.x >= 0 && current.x < 10 && current.y >= 0 && current.y < 10 && !visited[current.y][current.x] && maze[current.y][current.x] == 0)
        {
            // 새 점을 방문한 것으로 표시하고 큐에 추가
            visited[current.y][current.x] = 1;
            Point newPoint = { current.x, current.y };
            enqueue(&q, newPoint);
        }
        current.x++;
        if (current.x >= 0 && current.x < 10 && current.y >= 0 && current.y < 10 && !visited[current.y][current.x] && maze[current.y][current.x] == 0)
        {
            // 새 점을 방문한 것으로 표시하고 큐에 추가
            visited[current.y][current.x] = 1;
            Point newPoint = { current.x, current.y };
            enqueue(&q, newPoint);
        }
        current.y++;
        if (current.x >= 0 && current.x < 10 && current.y >= 0 && current.y < 10 && !visited[current.y][current.x] && maze[current.y][current.x] == 0)
        {
            // 새 점을 방문한 것으로 표시하고 큐에 추가
            visited[current.y][current.x] = 1;
            Point newPoint = { current.x, current.y };
            enqueue(&q, newPoint);
        }
    }
    return 0; // 경로가 없음
}
