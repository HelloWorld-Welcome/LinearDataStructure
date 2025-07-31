// 12주차 2차시 과제 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

typedef int element;

// Queue 구조체 
typedef struct Queue
{
    int front; // 맨 앞 원소 인덱스 
    int rear; // 맨 끝 원소 인덱스 + 1 
    int full_size; // Capacity 
    element* data; // 데이터 
} Queue;

int QueueOccupation(Queue* pLQueue);
Queue* Create(const int full_size);
bool IsEmpty(Queue* pQueue);
bool IsFull(Queue* pQueue);
bool Enqueue(Queue* pQueue, element ele);
element Dequeue(Queue* pQueue);
element Peek(Queue* pQueue);
void PrintQueue(Queue* pQueue);

main(void)
{
    // 최대 4개 저장 가능한 큐 생성 
    Queue* pQueue = Create(5);

    printf("=== Enqueue 테스트 ===\n");
    // 삽입 테스트 
    for (int i = 1; i < 8; i++)
    {
        if (Enqueue(pQueue, i * 10))
        {
            printf("Enqueue(%2d)\n", i * 10);
        }
    }

    printf("=== Peek 테스트 ===\n");
    // Peek 테스트 
    if (!IsEmpty(pQueue))
        printf("Peek: %d\n", Peek(pQueue));

    printf("=== Print 테스트 ===\n");
    PrintQueue(pQueue);

    printf("=== Dequeue 테스트 ===\n");
    // 삭제 테스트 
    while (!IsEmpty(pQueue))
    {
        printf("Dequeue: %d\n", Dequeue(pQueue));
    }

    printf("=== IsEmpty 테스트 ===\n");
    printf("%d\n", IsEmpty(pQueue));

    printf("=== 포화상태 오류 테스트 ===\n");
    printf("5 Size Queue | 4 Enqueue | 3 Dequeue -> 2 Enqueue 시 오류 안뜨면 성공 \n");
    printf("Check Overflow\n");
    for (int i = 1; i < 5; i++)
    {
        if (Enqueue(pQueue, i * 10))
        {
            printf("Enqueue(%2d)\n", i * 10);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Dequeue: %d\n", Dequeue(pQueue));
    }

    for (int i = 1; i < 3; i++)
    {
        if (Enqueue(pQueue, i * 100))
        {
            printf("Enqueue(%2d)\n", 100);
        }
        else
        {
            printf("포화상태오류발생\n");
        }
    }

    PrintQueue(pQueue);
}

// Queue 점유공간 크기 반환 
int QueueOccupation(struct Queue* pQueue)
{
    int occupation = (((pQueue->rear) - (pQueue->front) + (pQueue->full_size)) % (pQueue->full_size));

    return occupation;
}

// Queue 생성 
Queue* Create(const int full_size)
{
    Queue* pLQueue = (Queue*)malloc(sizeof(Queue));
    if (!pLQueue)
    {
        printf("Queue 구조체 할당 실패");
        return NULL;
    }
    pLQueue->data = (element*)malloc(sizeof(element) * full_size);

    if (!pLQueue->data)
    {
        printf("Queue Data 배열 할당 실패");
        free(pLQueue);
        return NULL;
    }

    pLQueue->full_size = full_size;
    pLQueue->front = 0;
    pLQueue->rear = 0;

    return pLQueue;
}

// Queue가 비어있으면 False반환 
bool IsEmpty(Queue* pLQueue)
{
    if (QueueOccupation(pLQueue) == 0)
        return true;

    return false;
}

// Queue가 가득차면 True반환 
bool IsFull(Queue* pLQueue)
{
    if (QueueOccupation(pLQueue) == pLQueue->full_size - 1)
        return true;

    return false;
}

// 삽입 (enqueue) 
bool Enqueue(Queue* pLQueue, element e)
{
    if (IsFull(pLQueue))
    {
        printf("Enqueue 오류: 큐가 가득 찼습니다.\n");
        return false;
    }

    pLQueue->data[pLQueue->rear] = e;
    pLQueue->rear = (pLQueue->rear + 1) % pLQueue->full_size;

    return true;
}

// 삭제 및 반환 (dequeue) 
element Dequeue(Queue* pLQueue)
{
    if (IsEmpty(pLQueue))
    {
        printf("Dequeue 오류: 큐가 비어 있습니다.\n");
        return (element)0;
    }
    element e = pLQueue->data[pLQueue->front];
    pLQueue->front = (pLQueue->front + 1) % pLQueue->full_size;
    // 다 꺼냈다면 다시 초기화 

    return e;
}

// 맨 앞 Queue peek 
element Peek(Queue* pLQueue)
{
    if (IsEmpty(pLQueue))
    {
        printf("Peek 오류: 큐가 비어 있습니다.\n");
        return (element)0;
    }
    return pLQueue->data[pLQueue->front];
}

// Queue 출력 
void PrintQueue(Queue* pQueue)
{
    if (pQueue->rear >= pQueue->front)
    {
        for (int i = pQueue->front; i < pQueue->rear; i++)
        {
            printf("Queue: %d\n", pQueue->data[i]);
        }
    }

    if (pQueue->front > pQueue->rear)
    {
        for (int i = pQueue->front; i < pQueue->full_size; i++)
        {
            printf("Queue: %d\n", pQueue->data[i]);
        }

        for (int i = 0; i < pQueue->rear; i++)
        {
            printf("Queue: %d\n", pQueue->data[i]);
        }
    }

}