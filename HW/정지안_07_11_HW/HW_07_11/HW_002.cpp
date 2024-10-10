#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int data;
    struct _Node* next;
} Node;

typedef struct _Stack
{
    Node* top;
    int size;
} Stack;

void _Stack(Stack* stack);
void push(Stack* stack, int data);
int pop(Stack* stack);
int size(Stack* stack);
int top(Stack* stack);
int isEmpty(Stack* stack);
void printStack(Stack* stack);

int main()
{
    Stack stack;
    _Stack(&stack);

    push(&stack, 100);
    push(&stack, 200);
    push(&stack, 300);

    printStack(&stack);

    printf("pop : %d\n", pop(&stack));
    printStack(&stack);

    printf("size: %d\n", size(&stack));
    printf("top: %d\n", top(&stack));
    printf("Isempty: %d\n", isEmpty(&stack));

    printStack(&stack);

    return 0;
}

void _Stack(Stack* stack)
{
    stack->top = NULL;
    stack->size = 0;
}

void push(Stack* stack, int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

int pop(Stack* stack)
{
    if (stack->top == NULL)
    {
        printf("스택이 비어있습니다\n");
        return 0;
    }
    Node* temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return data;
}

int size(Stack* stack)
{
    return stack->size;
}

int top(Stack* stack)
{
    if (stack->top == NULL)
    {
        printf("스택이 비어있습니다\n");
        return -1;
    }
    return stack->top->data;
}

int isEmpty(Stack* stack)
{
    if (stack->size = 0)
        return 1;
    else
        return 0;
}

void printStack(Stack* stack)
{
    if (stack->top == NULL)
    {
        printf("스택이 비어있습니다\n");
        return;
    }
    Node* current = stack->top;
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("\n");
}