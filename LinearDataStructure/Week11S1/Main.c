// 11주차 1차시 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
// Data 구조체 
typedef struct Data
{
    char bracket;
} Data;

// LinkedList Stack 노드 구조체 
typedef struct LinkedStack
{
    struct Data* data;
    struct LinkedStack* pNext;
} LinkedStack;

// Data 생성 
Data* CreateData(char c);

// 연결리스트형 Stack에 DeleteFirst 
void Pop(struct LinkedStack** ppHead);

// 연결리스트형 Stack에 InsertFirst 
void Push(struct LinkedStack** ppHead, struct Data* data_to_input);

// 연결리스트형 Stack의 Top 가져오기 
Data* Peek(struct LinkedStack* pHead);

// 연결리스트형 Stack이 비었는지 확인 
bool IsEmptyStack(struct LinkedStack* pHead);

// 괄호 사용 체크 
void CheckBracketUsing(const char* expression);

main()
{
    CheckBracketUsing("[A*{B+(C-D)+E}*F]");
    CheckBracketUsing("(A*B+c}");
    CheckBracketUsing("{(A*B+c}");
    CheckBracketUsing("(a*b+})");
    CheckBracketUsing("{a+[b+c]}");
}

// 데이터 생성 후 리턴 
Data* CreateData(char c)
{
    Data* data = malloc(sizeof * data);
    if (data == NULL)
        return NULL;

    data->bracket = c;

    return data;
}

// 연결리스트형 Stack에 InsertFirst 
void Push(struct LinkedStack** ppHead, struct Data* data_to_input)
{
    LinkedStack* pNewNode = malloc(sizeof * pNewNode);

    // 메모리 할당 체크 
    if (pNewNode == NULL)
    {
        return;
    }

    // 동적 할당한 노드에 데이터 초기화 
    pNewNode->data = data_to_input;
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

// 연결리스트형 Stack에 DeleteFirst 
void Pop(LinkedStack** ppHead)
{
    // 리스트에 노드 및 데이터가 없으면 종료 
    if (*ppHead == NULL)
    {
        return;
    }

    // 리스트에 헤드노드 단 하나만 남았을 때 실행 후 리턴 
    if ((*(*ppHead)).pNext == NULL)
    {
        Data* pDataDelete = (Data*)((*ppHead)->data);
        LinkedStack* pDelete = (LinkedStack*)*ppHead;
        free(pDataDelete);
        free(pDelete);
        (*ppHead) = NULL;
        return;
    }
    // 제거 후 메모리 해제 
    Data* pDataDelete = (Data*)((*ppHead)->data);
    LinkedStack* pDelete = (LinkedStack*)*ppHead;
    *ppHead = (*(*ppHead)).pNext;
    free(pDataDelete);
    free(pDelete);
}
// 연결리스트형 Stack의 Top 가져오기 
Data* Peek(LinkedStack* pHead)
{
    if (pHead == NULL)
        return NULL;
    return pHead->data;
}
// 연결리스트형 Stack이 비었는지 확인 
bool IsEmptyStack(LinkedStack* pHead)
{
    if (pHead == NULL)
        return true;

    return false;
}

// 괄호 사용 체크 
void CheckBracketUsing(const char* expression)
{
    LinkedStack* bracket_stack = NULL;

    /*
     3-2. 열렸는데 닫히지 않은 경우{(A * B + c} || {((A * B) + c}] => 결과가 Stack is NOT EMPTY
     3-3. 열리지 않았는데 닫힌 경우 (a*b}) || }(a*b)}) || [}(a + b)}]=> Stack is NULL인데 제거해야됨 ||
       => 공통점: 스택에 저장된 괄호와 검사하려는 괄호의 쌍이 맞지 않다.
       => 차이점: ??
     3-4. 소,중,대 괄호사이의 포함관계가 잘못된 경우
       => 괄호의 포함 우선순위를 레이어로 구분해서 체크
    */

    int length = strlen(expression); // 표현식 길이 
    int error = 1; // 오류 코드 
    int layer = -1; // 레이어 

    // Index is BRACKET LAYER ([]: 0 | {}: 1 | (): 2) 
    const char open_brackets[3] = { '[', '{', '(' };
    const char close_brackets[3] = { ']', '}', ')' };

    // 괄호 검사 
    for (int i = 0; i < length; i++)
    {
        char c = expression[i];

        if (c == open_brackets[0] || c == open_brackets[1] || c == open_brackets[2])
        {
            // 여는 괄호는 스택에 push 
            Push(&bracket_stack, CreateData(c));

            // 소,중,대 괄호사이의 포함관계가 잘못된 경우 체크 
            for (int j = 0; j < 3; j++)
            {
                if (c == open_brackets[j])
                {
                    if (layer > j)
                    {
                        error = 4;
                        break;
                    }

                    layer = j;
                }
            }
        }
        else if (c == close_brackets[0] || c == close_brackets[1] || c == close_brackets[2])
        {
            // Stack이 비었는데 닫는 괄호가 나온 경우(3-3) 체크 
            if (IsEmptyStack(bracket_stack))
            {
                error = 3;
                break;
            }

            char last_open_bracket = Peek(bracket_stack)->bracket;
            Pop(&bracket_stack);

            for (int k = 2; k >= 0; k--)
            {
                if (last_open_bracket == open_brackets[k])
                {
                    if (close_brackets[k] != c)
                    {
                        error = 23;
                        break;
                    }
                }
            }
        }
    }

    switch (error)
    {
    case 1:
        printf("표현식: %s\n", expression);
        printf("ERROR CODE: 1\n표현식이 정상입니다.\n\n");
        break;

    case 23:
        printf("표현식: %s\n", expression);
        printf("ERROR CODE: 23\n표현식에서 괄호가 열린 후 닫히지 않았거나 열리지 않고 닫혔습니다.\n\n"); 
            break;

    case 3:
        printf("표현식: %s\n", expression);
        printf("ERROR CODE: 3\n표현식에서 괄호가 열리지 않고 닫혔습니다.\n\n");
        break;

    case 4:
        printf("표현식: %s\n", expression);
        printf("ERROR CODE: 4\n표현식에서 괄호 포함관계가 잘못되었습니다.\n\n");
        break;
    }

    free(bracket_stack);
}