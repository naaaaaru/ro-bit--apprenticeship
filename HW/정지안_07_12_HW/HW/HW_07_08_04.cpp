#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    char data;
    struct _Node* next;
} Node;

typedef struct _Stack
{
    Node* top;
    int size;
} Stack;

typedef struct _Queue
{
    Node* front;
    Node* rear;
    int size;
} Queue;

void _Stack(Stack* stack);
void push(Stack* stack, char data);
char pop(Stack* stack);
int isEmptyStack(Stack* stack);

void _Queue(Queue* queue);
void Enqueue(Queue* queue, char data);
char Dequeue(Queue* queue);
int isEmptyQueue(Queue* queue);

int check(char* str);

int main()
{
    char str[100];

    printf("문자열을 입력하세요: ");
    scanf_s("%[^\n]", str, sizeof(str));

    if (check(str)==1)
    {
        printf("회문입니다.\n");
    }
    else
    {
        printf("회문이 아닙니다.\n");
    }

    return 0;
}

void _Stack(Stack* stack)
{
    stack->top = NULL;
    stack->size = 0;
}

void push(Stack* stack, char data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

char pop(Stack* stack)
{
    if (stack->top == NULL)
    {
        return '\0';
    }
    Node* temp = stack->top;
    char data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return data;
}

int isEmptyStack(Stack* stack)
{
    return stack->size == 0;
}

void _Queue(Queue* queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void Enqueue(Queue* queue, char data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

char Dequeue(Queue* queue)
{
    if (queue->front == NULL)
    {
        return '\0';
    }

    Node* temp = queue->front;
    char data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;
    return data;
}

int isEmptyQueue(Queue* queue)
{
    return queue->size == 0;
}

int check(char* str)
{
    Stack stack;
    Queue queue;
    _Stack(&stack);
    _Queue(&queue);

    for (int i = 0; str[i] != '\0'; i++)
    {
        push(&stack, str[i]);
        Enqueue(&queue, str[i]);
    }
    while (!isEmptyStack(&stack) && !isEmptyQueue(&queue))
    {
        if (pop(&stack) != Dequeue(&queue))
        {
            return 0;
        }
    }
    return 1;
}
