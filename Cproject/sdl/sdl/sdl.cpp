#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void enqueue(Queue* q, Point p);
Point dequeue(Queue* q);
int bfs(int maze[10][10], Point start, Point end, int visited[10][10]);
int checkMaze(int maze[10][10], Point start, Point checkpoint, Point end);
void easyMaze(int maze[10][10]);
void normalMaze(int maze[10][10]);
void hardMaze(int maze[10][10]);


int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 700, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Color playerColor = { 255, 0, 0, 255 }; // 플레이어 사각형 빨간색
    SDL_Color wallColor = { 255, 255, 255, 255 }; // 벽 하얀색
    SDL_Color doorColor = { 0, 255, 0, 255 }; // 입출구 초록색
    SDL_Color pathColor = { 255, 255, 255, 255 }; // 궤적 하얀색
    SDL_Color checkpointColor = { 0, 0, 255, 255 }; // 체크포인트 파란색

    Point player = { 0, 9 }; // 플레이어 시작 위치
    Point entry = { 0, 9 }; // 입구 위치
    Point exit = { 9, 0 }; // 출구 위치

    int maze[10][10] = { 0 }; // 미로 배열 초기화 (0: 빈 공간, 1: 벽)
    int edit = 1; // 편집 모드 변수

    Point* path = (Point*)malloc(sizeof(Point) * 500);
    int* distances = (int*)malloc(sizeof(int) * 500);

    int pathLength = 0;
    int attemptCount = 0; // 시도 횟수

    Point checkpoint; // 체크포인트
    setCheckpoint(maze, &checkpoint); // 체크포인트 설정

    SDL_Event e; // SDL 이벤트 처리 구조체
    int checkpointReached = 0; // 체크포인트 도달 여부

    while (1)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_SPACE:
                {
                    if (edit == 1)
                    {
                        edit = 0;
                        pathLength = 0;
                        player = entry; // 플레이어를 시작 위치로 리셋
                        path[pathLength] = player; // 궤적 기록
                        pathLength++;
                        checkpointReached = 0; // 체크포인트 도달 여부 초기화
                    }
                    break;
                }
                case SDLK_RETURN:
                {
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
                        printf("최단 경로 거리: %d\n", minDistance);

                        FILE* file = fopen("result.txt", "w");
                        if (file != NULL)
                        {
                            fprintf(file, "최단 경로 거리 : %d\n", minDistance);
                            fclose(file);
                        }
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        free(path);
                        free(distances);

                        return 0;
                    }
                    break;
                }
                case SDLK_w:
                {
                    if (edit == 0 && player.y > 0 && maze[player.y - 1][player.x] == 0)
                    {
                        player.y--;
                    }
                    break;
                }
                case SDLK_s:
                {
                    if (edit == 0 && player.y < 9 && maze[player.y + 1][player.x] == 0)
                    {
                        player.y++;
                    }
                    break;
                }
                case SDLK_a:
                {
                    if (edit == 0 && player.x > 0 && maze[player.y][player.x - 1] == 0)
                    {
                        player.x--;
                    }
                    break;
                }
                case SDLK_d:
                {
                    if (edit == 0 && player.x < 9 && maze[player.y][player.x + 1] == 0)
                    {
                        player.x++;
                    }
                    break;
                }
                case SDLK_1: // 숫자 1을 눌렀을 때
                {
                    int _check = 0;
                    while (_check == 0)
                    {
                        easyMaze(maze);
                        if (checkMaze(maze, entry, checkpoint, exit))
                        {
                            _check = 1;
                        }
                    }
                }
                break;
                case SDLK_2: // 숫자 2을 눌렀을 때
                {
                    int _check = 0;
                    while (_check == 0)
                    {
                        normalMaze(maze);
                        if (checkMaze(maze, entry, checkpoint, exit))
                        {
                            _check = 1;
                        }
                    }
                }
                break;
                case SDLK_3: // 숫자 3을 눌렀을 때
                {
                    int _check = 0;
                    while (_check == 0)
                    {
                        hardMaze(maze);
                        if (checkMaze(maze, entry, checkpoint, exit))
                        {
                            _check = 1;
                        }
                    }
                }
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
                        if (checkpointReached == 1)
                        {
                            distances[attemptCount] = distance(path, pathLength);
                            printf("%d번째 시도 움직임 횟수: %d\n", attemptCount + 1, distances[attemptCount]);
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
                            printf("체크포인트를 지나쳤습니다");
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
                    {
                        maze[y][x] = 0; // 벽 지우기
                    }
                    else
                    {
                        maze[y][x] = 1; // 벽 그리기
                    }

                    if (checkMaze(maze, entry, checkpoint, exit) == 0)
                    {
                        printf("경로가 불가능합니다.\n");
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
        SDL_RenderDrawLine(renderer, i * 60, 0, i * 60, 10 * 60);
        SDL_RenderDrawLine(renderer, 0, i * 60, 10 * 60, i * 60);
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
    srand((unsigned int)time(NULL));

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

void _Queue(Queue* q)
{
    q->front = 0;
    q->rear = 0;
}

void enqueue(Queue* q, Point p)
{
    q->data[q->rear] = p; // rear의 데이터 배열에 좌표 입력 
    q->rear = q->rear + 1; // rear 인덱스를 증가시켜 자리 만들기
}

Point dequeue(Queue* q)
{
    Point p = q->data[q->front]; // front의 데이터값 불러오기
    q->front = q->front + 1; // front 인덱스를 증가시켜 다음 값 가르키기
    return p; // 데이터값 반환
}

// BFS를 사용한 경로 찾기
int bfs(int maze[10][10], Point start, Point end, int visited[10][10])
{
    Queue q;
    _Queue(&q); // 큐 초기화
    enqueue(&q, start); // 시작점을 큐에 추가
    visited[start.y][start.x] = 1; // 시작점을 방문 표시

    while (q.front != q.rear)
    {
        Point current = dequeue(&q); // 현재 위치 가져오기

        if (current.x == end.x && current.y == end.y)
        {
            return 1; // 도착점에 도달했으면 성공
        }

        // 상
        if (current.y > 0 && maze[current.y - 1][current.x] == 0 && !visited[current.y - 1][current.x])
        {
            visited[current.y - 1][current.x] = 1; // 방문 표시
            Point next = { current.x, current.y - 1 };
            enqueue(&q, next); // 큐에 추가
        }

        // 하
        if (current.y < 9 && maze[current.y + 1][current.x] == 0 && !visited[current.y + 1][current.x])
        {
            visited[current.y + 1][current.x] = 1; // 방문 표시
            Point next = { current.x, current.y + 1 };
            enqueue(&q, next); // 큐에 추가
        }

        // 좌
        if (current.x > 0 && maze[current.y][current.x - 1] == 0 && !visited[current.y][current.x - 1])
        {
            visited[current.y][current.x - 1] = 1; // 방문 표시
            Point next = { current.x - 1, current.y };
            enqueue(&q, next); // 큐에 추가
        }

        // 우
        if (current.x < 9 && maze[current.y][current.x + 1] == 0 && !visited[current.y][current.x + 1])
        {
            visited[current.y][current.x + 1] = 1; // 방문 표시
            Point next = { current.x + 1, current.y };
            enqueue(&q, next); // 큐에 추가
        }
    }
    return 0; // 도착점에 도달하지 못했으면 실패
}

int checkMaze(int maze[10][10], Point start, Point checkpoint, Point end)
{
    int visited[10][10];

    // 시작점에서 체크포인트까지 경로 찾기
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            visited[i][j] = 0; // 방문 배열 초기화
        }
    }
    if (bfs(maze, start, checkpoint, visited)==0)
    {
        return 0; // 시작점에서 체크포인트까지 경로가 없으면 실패
    }

    // 체크포인트에서 출구까지 경로 찾기
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            visited[i][j] = 0; // 방문 배열 초기화
        }
    }
    if (bfs(maze, checkpoint, end, visited)==0)
    {
        return 0; // 체크포인트에서 출구까지 경로가 없으면 실패
    }

    return 1; // 두 경로 모두 성공하면 성공
}


void easyMaze(int maze[10][10])
{
    // 모든 셀을 빈 공간으로 초기화
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            maze[i][j] = 0;
        }
    }

    // 랜덤 벽을 추가하여 미로 생성
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (rand() % 5 == 0 && !(i == 0 && j == 9) && !(i == 9 && j == 0))//5분의 1확률로 미로 생성
            {
                maze[i][j] = 1;
            }
        }
    }
}

void normalMaze(int maze[10][10])
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            maze[i][j] = 0;
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (rand() % 3 == 0 && !(i == 0 && j == 9) && !(i == 9 && j == 0))//3분의 1확률로 미로 생성
            {
                maze[i][j] = 1;
            }
        }
    }
}

void hardMaze(int maze[10][10])
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            maze[i][j] = 0;
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (rand() % 2 == 0 && !(i == 0 && j == 9) && !(i == 9 && j == 0))//2분의 1확률로 미로 생성
            {
                maze[i][j] = 1;
            }
        }
    }
}
