// 10주차 2차시 과제 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 

// Data 구조체 
typedef struct Data
{
    int value;
} Data;

// LinkedList Stack 노드 구조체 
typedef struct LinkedStack
{
    Data* data;
    struct LinkedStack* pNext;
} LinkedStack;

// Data 생성하여 반환 
Data* CreateData(const int value);

// 연결리스트형 Stack에 InsertFirst 
void PushLS(struct LinkedStack** ppHead, const int item);

// 연결리스트형 Stack이 비었는지 확인 후 리턴 
bool IsLSEmpty(struct LinkedStack* pHead);

// Display() 
void PrintLS(struct LinkedStack* pHead);

// 타이틀과 디바이더 전체 길이를 입력받아 출력 
void PrintDivider(const char* title, const int divider_length);

// NewNode 메모리 할당 실패시 오류 메세지 출력 
void PrintNewNodeMallocErr(void);

// 두 Stack을 DeepCopy 
void DeepCopy(LinkedStack** ppDstHead, LinkedStack** ppDstTail, const LinkedStack* src);

// Stack이 DeepCopy되었는지 체크하는 함수 
bool CheckDeepCopy(const LinkedStack* src, const LinkedStack* dst);

main()
{
    struct LinkedStack* pHeadSource = NULL;
    struct LinkedStack* pHeadDestination = NULL;
    struct LinkedStack* pTailDestination = NULL;
    for (int i = 1; i < 6; i++)
    {
        PushLS(&pHeadSource, i * 10);
    }
    printf("=== 원본 Stack ===\n");
    PrintLS(pHeadSource);
    DeepCopy(&pHeadDestination, &pTailDestination, pHeadSource);
    printf("=== 복본 Stack ===\n");
    PrintLS(pHeadDestination);
    printf("DeepCopy 체크 결과: %d (0: False | 1: True)\n", CheckDeepCopy(pHeadSource, pHeadDestination));
}
// Data 생성하여 반환 
Data* CreateData(const int value)
{
    Data* data = (Data*)malloc(sizeof(Data));
    if (data == NULL)
        return;
    data->value = value;
    return data;
}
// 원형 연결리스트형 Stack에 InsertFirst 
void PushLS(struct LinkedStack** ppHead, const int item)
{
    LinkedStack* pNewNode = (LinkedStack*)malloc(sizeof(LinkedStack));
    Data* ele = CreateData(item);
    // 메모리 할당 체크 
    if (pNewNode == NULL)
    {
        PrintNewNodeMallocErr();
        return;
    }
    if (ele == NULL)
        return;
    // 동적 할당한 노드에 데이터 초기화 
    ele->value = item;
    pNewNode->data = ele;
    pNewNode->pNext = NULL;
    if (*ppHead == NULL) // 헤드 포인터가 NULL을 가리키면 
    {
        *ppHead = pNewNode; // 헤드 포인터에 새 노드 주소값 입력 
    }
    else // 헤드 포인터가 노드를 가리키고 있으면 
    {
        pNewNode->pNext = *ppHead;
        *ppHead = pNewNode;
    }
}
// 연결리스트형 Stack이 비었는지 확인 후 리턴 
bool IsLSEmpty(struct LinkedStack* pHead)
{
    if (pHead == NULL)
        return true;
    return false;
}
// 연결리스트형 Stack 출력 
void PrintLS(struct LinkedStack* pHead)
{
    // 리스트가 비었으면 실행 후 리턴 
    if (pHead == NULL)
    {
        PrintDivider("LIST IS EMPTY", 73);
        putchar('\n');
        return;
    }
    // 반복자에 첫번째 노드 주소로 설정 
    LinkedStack* pIterator = pHead;
    int position = 0;
    PrintDivider("[LinkedStack]", 73);
    while (pIterator != NULL)
    {
        printf("[DebugLog]: [Pos: %d] | [this: %p] | [Data: %d | pData: %p] | [pNext: %p]\n", 
            position, pIterator, pIterator-> data->value, pIterator->data, pIterator->pNext);
        pIterator = pIterator->pNext;
        position++;
    }
}
// 타이틀과 디바이더 전체 길이를 입력받아 출력 
void PrintDivider(const char* title, const int divider_length)
{
    int title_length = strlen(title);
    int dash_length = divider_length - title_length;
    int length_to_print = dash_length / 2 + dash_length / 2 + title_length;
    for (int i = 0; i < dash_length / 2; i++)
    {
        putchar('-');
    }
    printf("%s", title);
    for (int i = 0; i < dash_length / 2; i++)
    {
        putchar('-');
    }
    if (length_to_print != divider_length)
        putchar('-');
    putchar('\n');
}
// NewNode 메모리 할당 실패시 오류 메세지 출력 
void PrintNewNodeMallocErr(void)
{
    printf("[ErrorLog]: pNewNode 메모리 할당 실패!\n");
}

// 두 Stack을 DeepCopy 
void DeepCopy(LinkedStack** ppDstHead, LinkedStack** ppDstTail, const LinkedStack* src)
{
    if (src == NULL)
    {
        *ppDstHead = NULL;
        *ppDstTail = NULL;
        return;
    }

    *ppDstHead = NULL;
    *ppDstTail = NULL;

    for (const LinkedStack* current = src; current; current = current->pNext)
    {
        // 새 노드 생성 
        LinkedStack* pNewNode = malloc(sizeof * pNewNode);
        if (!pNewNode) {
            // 할당 실패 시 이미 만든 노드들 해제 
            for (LinkedStack* t = *ppDstHead; t; ) {
                LinkedStack* next = t->pNext;
                free(t->data);
                free(t);
                t = next;
            }
            *ppDstHead = NULL;
            return;
        }

        // Data 깊은 복사 
        pNewNode->data = malloc(sizeof * current->data);
        if (!pNewNode->data)
        {
            free(pNewNode);
            return NULL;
        }
        memcpy(pNewNode->data, current->data, sizeof * current->data);

        pNewNode->pNext = NULL;
        if (*ppDstHead == NULL)
        {
            *ppDstHead = pNewNode;
        }
        else
        {
            (*ppDstTail)->pNext = pNewNode;
        }
        *ppDstTail = pNewNode;
    }
}

// Stack이 DeepCopy되었는지 체크하는 함수 
bool CheckDeepCopy(const LinkedStack* src, const LinkedStack* dst)
{
    const LinkedStack* pSrcItr = src, * pDstItr = dst;
    while (pSrcItr && pDstItr)
    {
        // 노드가 다른 주소인지 체크 
        if (pSrcItr == pDstItr)
        {
            return false;
        }
        // data 포인터가 다른 주소인지 체크 
        if (pSrcItr->data == pDstItr->data)
        {
            return false;
        }
        // data 내용은 동일한지 체크 
        if (memcmp(pSrcItr->data, pDstItr->data, sizeof * pSrcItr->data) != 0)
        {
            return false;
        }
        pSrcItr = pSrcItr->pNext;
        pDstItr = pDstItr->pNext;
    }
    // 최종적으로 둘 다 NULL인지 (길이가 동일한지) 체크 
    return (pSrcItr == NULL && pDstItr == NULL);
}