// 13주차 2차시 과제 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <time.h> 

// 노드 구조체 정의 
typedef struct Node
{
    int data;
    struct Node* pPrev;
    struct Node* pNext;
} Node;

// 큐 구조체 정의 
typedef struct Queue
{
    Node* front;  // 맨 앞 노드를 가리키는 포인터 
    Node* rear;   // 맨 뒤 노드를 가리키는 포인터 
} Queue;

Queue* CreateQueue();
Queue* CreateCustomQueue();
Queue* MergeQueue(Queue* q2, Queue* q1);
bool IsEmpty(Queue* q);
bool Enqueue(Queue* q, int value);
int Dequeue(Queue* q);
int Peek(Queue* q);
Node* DeleteByIndex(Queue* q, const int k);
void PrintLLQueue(Queue* q);

main(void)
{
    srand((unsigned)time(NULL));

    Queue* q1 = CreateCustomQueue();

    PrintLLQueue(q1);

    Queue* q2 = CreateCustomQueue();

    PrintLLQueue(q2);

    q1 = MergeQueue(q1, q2);

    PrintLLQueue(q1);

    Queue* q3 = CreateCustomQueue();

    PrintLLQueue(q3);

    q1 = MergeQueue(q1, q3);

    PrintLLQueue(q1);

    return 0;
}

// 큐 생성 함수 
Queue* CreateQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q)
    {
        printf("메모리 할당 실패\n");
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

// 과제 제출용 큐 생성 함수 
Queue* CreateCustomQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q)
    {
        printf("메모리 할당 실패\n");
        return NULL;
    }
    q->front = q->rear = NULL;

    for (int i = 0; i < 5; i++)
    {
        int rd = rand() % 50 + 1;
        if (Enqueue(q, rd))
        {
            printf("Enqueue(%d)\n", rd);
        }
    }

    int k = rand() % 5 + 1;
    printf("k = %d\n", k);

    Node* pDeleteNode = NULL;
    Node* pItrNode = q->front;
    Node* pPrevNode = q->front;

    int i = 0;

    while (i != k - 1)
    {
        i++;
        pPrevNode = pItrNode;
        pItrNode = pItrNode->pNext;
    }

    pDeleteNode = pItrNode;

    if (k == 1)
    {
        q->front = pDeleteNode->pNext;
        pDeleteNode->pNext->pPrev = q->rear;
        q->rear->pNext = q->front;
        free(pDeleteNode);
    }
    else if (k == 5)
    {
        pPrevNode->pNext = q->front;
        q->front->pPrev = pPrevNode;
        q->rear = pPrevNode;
        free(pDeleteNode);
    }
    else
    {
        q->front = pDeleteNode->pNext;
        q->rear = pDeleteNode->pPrev;
        pDeleteNode->pNext->pPrev = q->rear;
        pDeleteNode->pPrev->pNext = q->front;
    }

    return q;
}

// 과제 제출용 큐 병합 함수 
Queue* MergeQueue(Queue* q2, Queue* q1)
{
    Queue* q_merge = (Queue*)malloc(sizeof(Queue));

    if (q_merge == NULL)
        return;

    q_merge->front = q1->front;
    q_merge->rear = q2->rear;
    q_merge->rear->pNext = q1->front;
    q_merge->front->pPrev = q2->rear;

    q1->rear->pNext = q2->front;
    q2->front->pPrev = q1->rear;

    free(q1);
    free(q2);

    return q_merge;
}

// 큐가 비어있는지 확인하는 함수 
bool IsEmpty(Queue* q)
{
    return q->front == NULL;
}

// 큐에 데이터 삽입 함수 
bool Enqueue(Queue* q, int value)
{
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    if (!pNewNode)
    {
        printf("메모리 할당 실패\n");
        return false;
    }
    pNewNode->data = value;
    pNewNode->pPrev = NULL;
    pNewNode->pNext = NULL;

    if (IsEmpty(q))
    {
        // 비어있다면 front와 rear 모두 pNewNode로 설정 
        q->front = q->rear = pNewNode;
        pNewNode->pNext = pNewNode;
        pNewNode->pPrev = pNewNode;
    }
    else
    {
        // 비어있지 않다면 기존 rear 뒤에 연결 후 rear 업데이트 
        q->rear->pNext = pNewNode;
        pNewNode->pPrev = q->rear;
        q->rear = pNewNode;
        pNewNode->pNext = q->front;
        q->front->pPrev = q->rear;

    }

    return true;
}

// 큐에서 데이터 제거 및 반환 함수 
int Dequeue(Queue* q)
{
    if (IsEmpty(q))
    {
        printf("큐가 비어있음\n");
        return -1;
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->pNext;
    q->front->pPrev = q->rear;
    q->rear->pNext = q->front;

    if (q->front == NULL)
    {
        // 제거 후 큐가 비어있으면 rear도 NULL로 설정 
        q->rear = NULL;
    }
    free(temp);

    return value;
}

// 큐의 맨 앞 데이터를 확인만 하는 함수 
int Peek(Queue* q)
{
    if (IsEmpty(q))
    {
        printf("큐가 비어있음\n");
        return -1;
    }
    return q->front->data;
}

// 사용X 
Node* DeleteByIndex(Queue* q, const int k)
{
    int i = 0;
    Node* pPrev = q->front;
    Node* pItr = q->front;
    Node* pDelete = NULL;
    while (i != k - 1)
    {
        pPrev = pItr;
        pItr = pItr->pNext;
        i++;
    }
    pDelete = pItr;
    if (pPrev != q->front)
    {

        pPrev->pNext = pItr->pNext;
    }
    else
    {
        pItr->pNext = pItr->pNext->pNext;
    }

    return pDelete;
}

// 큐 출력 함수 
void PrintLLQueue(Queue* q)
{
    if (IsEmpty(q))
    {
        printf("큐가 비어있습니다.\n");
        return;
    }

    Node* current = q->front;
    printf("Queue: ");
    do
    {
        printf("[%d] ", current->data);
        current = current->pNext;
    } while (current != q->front);

    printf("\n");
}

// 큐 메모리 해제 함수 
void DestroyLLQueue(Queue* q)
{
    while (!IsEmpty(q))
    {
        Dequeue(q);
    }
    free(q);
}