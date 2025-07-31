// 13주차 1차시 과제
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 

typedef int element;

// Queue 구조체 
typedef struct Queue
{
    int front; // 맨 앞 원소 인덱스 
    int rear; // 맨 끝 원소 인덱스 + 1 
    //int occupatioin; 
    int full_size; // Capacity 
    element* data; // 데이터 
} Queue;

int QueueOccupation(Queue* pQueue);
Queue* Create(const int full_size);
bool IsEmpty(Queue* pQueue);
bool IsFull(Queue* pQueue);
bool Enqueue(Queue* pQueue, element ele);
element Dequeue(Queue* pQueue);
element Peek(Queue* pQueue);
void PrintQueue(Queue* pQueue);
void ReassignQueue(Queue* pQueue);
void InitQueue(Queue* pQueue);

main(void)
{
    // 최대 5개 저장 가능한 큐 생성 
    Queue* pQueue = Create(6);

    printf("=== CASE 1. 정방향 : 10 -> 20 -> 30 -> 40 -> 50  (Enq. 5번) ===\n");

    for (int i = 1; i < 6; i++)
    {
        if (Enqueue(pQueue, i * 10))
        {
            printf("Enqueue(%d)\n", i * 10);
        }
    }

    PrintQueue(pQueue);

    Queue* pQueueSnd = Create(6);
    printf("=== CASE 2. 역방향 : 60 -> 70 -> 30 -> 40-> 50 (Enq. 3번 -> Deq. 2번 -> Enq. 4번) ===\n");

    for (int i = 1; i < 4; i++)
    {
        if (Enqueue(pQueueSnd, i * 10))
        {
            printf("Enqueue(%d)\n", i * 10);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        printf("Dequeue: %d\n", Dequeue(pQueueSnd));
    }

    for (int i = 4; i < 8; i++)
    {
        if (Enqueue(pQueueSnd, i * 10))
        {
            printf("Enqueue(%d)\n", i * 10);
        }
    }

    PrintQueue(pQueueSnd);

    printf("CASE 3. 역방향 : 60 -> 70 -> 30 -> 40-> 50 (Enq. 3번 -> Deq. 2번 -> Enq. 4번)\n");
    ReassignQueue(pQueueSnd);
    PrintQueue(pQueueSnd);
}

// Queue 생성 
Queue* Create(const int full_size)
{
    Queue* pQueue = (Queue*)malloc(sizeof(Queue));
    if (!pQueue)
    {
        printf("Queue 구조체 할당 실패");
        return NULL;
    }
    pQueue->data = (element*)malloc(sizeof(element) * full_size);

    if (!pQueue->data)
    {
        printf("Queue Data 배열 할당 실패");
        free(pQueue);
        return NULL;
    }

    pQueue->full_size = full_size;
    pQueue->front = 0;
    pQueue->rear = 0;
    //pQueue->occupatioin = 0; 

    return pQueue;
}

// Queue가 비어있으면 False반환 
bool IsEmpty(Queue* pQueue)
{
    if (QueueOccupation(pQueue) == 0)
        return true;

    return false;
}

// Queue가 가득차면 True반환 
bool IsFull(Queue* pQueue)
{
    if (QueueOccupation(pQueue) == pQueue->full_size - 1)
        return true;

    return false;
}

// 삽입 (enqueue) 
bool Enqueue(Queue* pQueue, element e)
{
    if (IsEmpty(pQueue))
    {
        pQueue->front = 0;
        pQueue->rear = 0;
    }
    if (IsFull(pQueue))
    {
        printf("Enqueue 오류: 큐가 가득 찼습니다.\n");
        return false;
    }

    pQueue->data[pQueue->rear] = e;
    pQueue->rear = (pQueue->rear + 1) % pQueue->full_size;
    //pQueue->occupatioin++; 

    return true;
}

// 삭제 및 반환 (dequeue) 
element Dequeue(Queue* pQueue)
{
    if (IsEmpty(pQueue))
    {
        printf("Dequeue 오류: 큐가 비어 있습니다.\n");
        return (element)0;
    }
    element e = pQueue->data[pQueue->front];
    pQueue->front = (pQueue->front + 1) % pQueue->full_size;
    //pQueue->occupatioin--; 

    return e;
}

// 맨 앞 Queue peek 
element Peek(Queue* pQueue)
{
    if (IsEmpty(pQueue))
    {
        printf("Peek 오류: 큐가 비어 있습니다.\n");
        return (element)0;
    }
    return pQueue->data[pQueue->front];
}

// Queue 출력 
void PrintQueue(Queue* pQueue)
{
    int cnt = 0;
    if (pQueue->rear > pQueue->front)
    {
        printf("[정방향 Queue]\n");
        for (int i = pQueue->front; i < pQueue->rear; i++)
        {
            printf("Queue[%d]: %d\n", cnt++, pQueue->data[i]);
        }
    }

    if (pQueue->front > pQueue->rear)
    {
        printf("[역방향 Queue]\n");
        for (int i = pQueue->front; i < pQueue->full_size; i++)
        {
            printf("Queue[%d]: %d\n", i, pQueue->data[i]);
        }

        for (int i = 0; i < pQueue->rear; i++)
        {
            printf("Queue[%d]: %d\n", i, pQueue->data[i]);
        }
    }

}

void ReassignQueue(Queue* pQueue)
{
    if (pQueue->front > pQueue->rear)
    {
        element* tmp = pQueue->data;

        pQueue->data = (element*)malloc(sizeof(element) * pQueue->full_size);

        if (pQueue->data == NULL)
            return;

        int cnt = 0;
        for (int i = pQueue->front; i < pQueue->full_size; i++)
        {
            pQueue->data[cnt++] = tmp[i];
        }

        for (int i = 0; i < pQueue->rear; i++)
        {
            pQueue->data[cnt++] = tmp[i];
        }

        //pQueue->rear = pQueue->occupatioin; 

        pQueue->front = 0;
    }
}

void InitQueue(Queue* pQueue)
{
    element* pDelete = pQueue->data;
    pQueue->data = (element*)malloc(sizeof(element) * pQueue->full_size);
    free(pDelete);

    if (pQueue->data == NULL)
        return;

    pQueue->front = -1;
    pQueue->rear = -1;
    //pQueue->occupatioin = 0; 
}