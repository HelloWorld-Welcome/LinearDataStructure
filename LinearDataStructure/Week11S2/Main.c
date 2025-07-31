// 11주차 2차시 
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <ctype.h> 

// Data 구조체 
typedef struct Data
{
    char character;
} Data;

// LinkedList Stack 노드 구조체 
typedef struct LinkedStack
{
    struct Data* data;
    struct LinkedStack* pNext;
} LinkedStack;

// Data 생성 
Data* CreateData(char c);

// 연결리스트형 Stack에 InsertFirst 
void Push(struct LinkedStack** ppHead, struct Data* data_to_input);

// 연결리스트형 Stack에 DeleteFirst 
void Pop(struct LinkedStack** ppHead);
// 연결리스트형 Stack의 Top 가져오기 
Data* Peek(struct LinkedStack* pHead);
// 연결리스트형 Stack이 비었는지 확인 
bool IsEmptyStack(struct LinkedStack* pHead);
// 괄호 사용 체크 
void CheckBracketUsing(const char* expression, bool* checker);
bool IsLetter(char c);
static int Precedence(char op);
char* InfixToPostfix(const char* infix_expression);
int PostfixCalc(const char* postfix_expression);
main()
{
    printf("%s\n", InfixToPostfix("1+2*5*(9/3/3)+3"));
    // 125*+933//*3+ 
    printf("%s\n", InfixToPostfix("1*2+5"));
    bool checker;
    CheckBracketUsing("[A*{B+(C-D)+E}*F]", &checker);
    CheckBracketUsing("(A*B+c}", &checker);
    CheckBracketUsing("{(A*B+c}", &checker);
    CheckBracketUsing("(a*b+})", &checker);
    CheckBracketUsing("{a+[b+c]}", &checker);
    //printf("%s\n", InfixToPostfix("(A+(B*C/D)/E)")); 
    InfixToPostfix("A+B*C-(D/E/F)*G");
    // 125+* 
    // 125*+ 
    // 1 2 5 + 
    printf("%s\n", InfixToPostfix("1+2*5"));
    // 
    //  
    printf("%d\n", PostfixCalc(InfixToPostfix("1*2+5")));

    printf("%d\n", PostfixCalc(InfixToPostfix("(20+3)*4+9")));
}

// 데이터 생성 후 리턴 
Data* CreateData(char c)
{
    Data* data = malloc(sizeof * data);
    if (data == NULL)
        return NULL;

    data->character = c;

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
void CheckBracketUsing(const char* expression, bool* checker)
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

            char last_open_bracket = Peek(bracket_stack)->character;
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

    (*checker) = 0;

    switch (error)
    {
    case 1:
        (*checker) = 1;
        printf("결과: %d\n표현식: %s\n", (*checker), expression);
        printf("CODE: %d\n표현식이 정상입니다.\n\n", error);
        break;

    case 23:
        (*checker) = 23;
        printf("결과: %d\n표현식: %s\n", (*checker), expression);
        printf("CODE: %d\n표현식에서 괄호가 열린 후 닫히지 않았거나 열리지 않고 닫혔습니다.\n\n", error); 
            break;

    case 3:
        (*checker) = 3;
        printf("결과: %d\n표현식: %s\n", (*checker), expression);
        printf("CODE: %d\n표현식에서 괄호가 열리지 않고 닫혔습니다.\n\n", error);
        break;

    case 4:
        (*checker) = 4;
        printf("결과: %d\n표현식: %s\n", (*checker), expression);
        printf("CODE: %d\n표현식에서 괄호 포함관계가 잘못되었습니다.\n\n", error);
        break;
    }

    free(bracket_stack);
}

bool IsLetter(char c)
{
    if ((c >= 48 && c <= 57) ||
        (c >= 65 && c <= 90) ||
        (c >= 97 && c <= 122))
    {
        return true;
    }

    return false;
}

static int Precedence(char op)
{
    switch (op)
    {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return 0;  // '(' 등은 0으로 
}

char* InfixToPostfix(const char* infix_expression)
{
    bool bracket_error[4] = { false };
    CheckBracketUsing(infix_expression, bracket_error);
    if (!bracket_error[0]) return NULL;

    LinkedStack* operator_stack = NULL;
    int length = strlen(infix_expression);
    char* postfix_expression = calloc(length * 3 + 1, sizeof(char));
    int idx = 0;

    for (int i = 0; i < length; )
    {
        char c = infix_expression[i];

        if (isspace((char)c))
        {
            i++;
        }
        else if (isdigit((char)c))
        {
            // 다자리 숫자 읽기 
            while (i < length && isdigit((unsigned char)infix_expression[i]))
            {
                postfix_expression[idx++] = infix_expression[i++];
            }
            postfix_expression[idx++] = ' ';
        }
        else if (c == '(')
        {
            Push(&operator_stack, CreateData(c));
            i++;
        }
        else if (c == ')')
        {
            // '(' 나올 때까지 
            while (!IsEmptyStack(operator_stack) &&
                Peek(operator_stack)->character != '(')
            {
                postfix_expression[idx++] = Peek(operator_stack)->character;
                postfix_expression[idx++] = ' ';
                Pop(&operator_stack);
            }
            // '(' 제거 
            if (!IsEmptyStack(operator_stack))
                Pop(&operator_stack);

            i++;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            int precedence = Precedence(c);
            // 스택 위에 '(' 이거나 우선순위가 낮으면 중단 
            while (!IsEmptyStack(operator_stack))
            {
                char top_operator = Peek(operator_stack)->character;
                if (top_operator == '(') break;

                int precedence = Precedence(top_operator);
                if (precedence >= precedence)
                {
                    postfix_expression[idx++] = top_operator;
                    postfix_expression[idx++] = ' ';
                    Pop(&operator_stack);
                }
                else
                {
                    break;
                }
            }
            Push(&operator_stack, CreateData(c));
            i++;
        }
        else
        {
            // 변수명 등이면 무시하거나 별도 처리 
            i++;
        }
    }

    // 남은 연산자 모두 출력 
    while (!IsEmptyStack(operator_stack))
    {
        char top_operator = Peek(operator_stack)->character;
        if (top_operator != '(')
        {
            postfix_expression[idx++] = top_operator;
            postfix_expression[idx++] = ' ';
        }
        Pop(&operator_stack);
    }

    postfix_expression[idx] = '\0';
    return postfix_expression;
}



int PostfixCalc(const char* postfix_expression)
{
    int array_stack[256];
    int top = -1;

    // strtok 로 토큰 분리 
    char* buf = strdup(postfix_expression);
    char* context = NULL;
    char* token = strtok_s(buf, " ", &context);
    while (token)
    {
        // 1) 숫자 토큰 
        if (isdigit((char)token[0]))
        {
            array_stack[++top] = atoi(token);
        }
        // 2) 연산자 토큰 (단일 문자) 
        else if (strlen(token) == 1)
        {
            if (top < 1)
            {
                printf("잘못된 후위표현식\n");
                free(buf);
                return 0;
            }
            int b = array_stack[top--];
            int a = array_stack[top--];
            int result = 0;
            switch (token[0])
            {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0)
                {
                    printf("0으로 나눌 수 없습니다.\n");
                    free(buf);
                    return 0;
                }
                result = a / b;
                break;
            default:
                printf("지원되지 않는 연산자: %s\n", token);
                free(buf);
                return 0;
            }
            array_stack[++top] = result;
        }
        // 3) 그 외 토큰: 무시 
        token = strtok_s(NULL, " ", &context);
    }

    int expression_calc_result = (top == 0) ? array_stack[top] : 0;
    if (top != 0)
        printf("계산 후 스택에 잔여값이 있습니다\n");

    free(buf);
    return expression_calc_result;
};