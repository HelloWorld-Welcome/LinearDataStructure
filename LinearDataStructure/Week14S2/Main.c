// 14주차 2차시 과제
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// 노드 구조체 정의
typedef struct Node
{
    int data;
    //struct Node* pPrev;
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
    Queue* q = CreateQueue();

    while (QueueSize(q) != 10)
    {
        int r = rand() % 100 + 1;
        int s = r % 3;

        printf("=== MAPPING ===\n");
        printf("r = %d | s = %d\n", r, s);

        printf("=== PROCESS ===\n");
        if (s % 2 == 0 && s != 0)
        {
            if (Enqueue(q, r))
            {
                printf("IsEnqueue: TRUE\n");
            }
            else
            {
                printf("IsEnqueue: FALSE\n");
            }
        }
        else
        {
            printf("Dequeue\n");
            Dequeue(q);
        }

        putchar('\n');
    }

    PrintLLQueue(q);
}

//큐 사이즈 반환
int QueueSize(Queue* q)
{
    if (q == NULL) return 0;

    int count = 0;
    Node* cur = q->front;
    while (cur != NULL)
    {
        count++;
        cur = cur->pNext;
    }
    return count;
}

// 중복 검사 함수: 큐에 value가 이미 들어있는지 확인
bool IsDuplicate(Queue* q, int value)
{
    if (q == NULL || q->front == NULL)
        return 0;

    Node* current = q->front;
    while (current != NULL)
    {
        if (current->data == value)
            return true;  // 중복 발견
        current = current->pNext;
    }
    return false;  // 중복 없음
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

// 큐가 비어있는지 확인하는 함수
bool IsEmpty(Queue* q)
{
    return q->front == NULL;
}

// 큐에 데이터 삽입 함수
bool Enqueue(Queue* q, int value)
{
    if (IsDuplicate(q, value))
    {
        printf("!!!중복된 수!!!\n");
        return false;
    }

    Node* pNewNode = (Node*)malloc(sizeof(Node));
    if (!pNewNode)
    {
        printf("메모리 할당 실패\n");
        return false;
    }
    pNewNode->data = value;
    pNewNode->pNext = NULL;

    if (IsEmpty(q))
    {
        // 비어있다면 front와 rear 모두 pNewNode로 설정
        q->front = q->rear = pNewNode;
        pNewNode->pNext = NULL;
    }
    else
    {
        // 비어있지 않다면 기존 rear 뒤에 연결 후 rear 업데이트
        q->rear->pNext = pNewNode;
        q->rear = pNewNode;
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

    //if (q->front == NULL)
    //{
    //    // 제거 후 큐가 비어있으면 rear도 NULL로 설정
    //    q->rear = NULL;
    //}
    //free(temp);

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
    } while (current != NULL);

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