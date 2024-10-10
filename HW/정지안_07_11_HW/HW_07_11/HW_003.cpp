#include <stdio.h>
#include <stdlib.h>

typedef struct _Node 
{
    int data;
    struct _Node* next;
} Node;

typedef struct _Queue 
{
    Node* front;
    Node* rear;
    int size;
} Queue;

void _Queue(Queue* queue);
void Enqueue(Queue* queue, int data);
int Dequeue(Queue* queue);
int size(Queue* queue);
int front(Queue* queue);
int rear(Queue* queue);
int isempty(Queue* queue);
void printQueue(Queue* queue);

int main() 
{
    Queue queue;
    _Queue(&queue);

    Enqueue(&queue, 100);
    Enqueue(&queue, 200);
    Enqueue(&queue, 300);

    printQueue(&queue);

    printf("Dequeue : %d\n", Dequeue(&queue));
    printQueue(&queue);

    printf("size: %d\n", size(&queue));
    printf("front: %d\n", front(&queue));
    printf("rear: %d\n", rear(&queue));
    printf("Isempty: %d\n", isempty(&queue));

    printQueue(&queue);
    return 0;
}

void _Queue(Queue* queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void Enqueue(Queue* queue, int data)
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

int Dequeue(Queue* queue)
{
    if (queue->front == NULL)
    {
        printf("큐가 비어있습니다\n");
        return 0;
    }

    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) 
    {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;
    return data;
}

int front(Queue* queue) 
{
    if (queue->front == NULL) 
    {
        printf("큐가 비어있습니다\n");
        return 0;
    }
    return queue->front->data;
}

int rear(Queue* queue) 
{
    if (queue->rear == NULL) 
    {
        printf("큐가 비어있습니다\n");
        return 0;
    }
    return queue->rear->data;
}

int size(Queue* queue) 
{
    return queue->size;
}

int isempty(Queue* queue) 
{
    return (queue->size == 0);
}

void printQueue(Queue* queue) 
{
    if (queue->front == NULL) 
    {
        printf("큐가 비어있습니다\n");
        return;
    }
    Node* current = queue->front;
    while (current != NULL) 
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("\n");
}
