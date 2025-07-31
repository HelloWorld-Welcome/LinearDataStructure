// 6주차 2차시
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// 메뉴 열거형
typedef enum EMY_MENU
{
	EXIT, INSERT_FIRST, INSERT_LAST, PRINT, DELETE_FIRST, DELETE_LAST, PRINT_BACKWARD
} EMY_MENU;

// 더블 리스트 노드 구조체
typedef struct ListNode
{
	int data;
	struct ListNode* pPrev;
	struct ListNode* pNext;
} ListNode;

// 메뉴 출력
EMY_MENU PrintMenu(void);

// 이벤트 루프 함수
void EventLoopRun(void);

// 리스트 첫번째에 노드 추가
void InsertFirst(struct ListNode** ppHead, struct ListNode** ppTail, const int value);

// 리스트 마지막에 노드 추가
void InsertLastDynamicArrayMult(struct ListNode** ppHead, struct ListNode** ppTail, const int value);

// 리스트 첫번째 노드 제거
void DeleteFirst(struct ListNode** ppHead, struct ListNode** ppTail);

// 리스트 마지막 노드 제거
void DeleteLast(struct ListNode** ppHead, struct ListNode** ppTail);

// 리스트 출력(Param(2)에 문자열로 "FORWARD" 혹은 "BACKWARD" 입력
void PrintList(struct ListNode* pHead, struct ListNode* pTail, const char* forward_or_backward, const int* list_size);

// 다시 입력하라는 메세지 출력
void PrintInputAgain();

// NewNode 메모리 할당 실패시 오류 메세지 출력
void PrintNewNodeMallocErr();

// 타이틀과 디바이더 전체 길이를 입력받아 출력
void PrintDivider(const char* title, const int divider_length);

// 반복 루프가 다시 돌기 전 메세지 출력하고 아무 키나 받을때까지 기다림
void PressAnyKeyMsg(void);

// 추가 성공 메세지 출력
void PrintAddSuc(void);

// 삭제 성공 메세지 출력
void PrintDelSuc(void);

main(void)
{
	EventLoopRun();
}

// 메뉴 출력
EMY_MENU PrintMenu(void)
{
	EMY_MENU input = 0;

	system("cls");
	printf("----------[MENU]----------\n");
	printf("[1] Insert First\n");
	printf("[2] Insert Last\n");
	printf("[3] Print List\n");
	printf("[4] Delete First\n");
	printf("[5] Delete Last\n");
	printf("[6] Print Backward\n");
	printf("[0] Exit\n");
	scanf_s("%d%*c", &input);

	return input;
}

// 이벤트 루프 함수
void EventLoopRun(void)
{
	struct ListNode* pHead = NULL; // 헤드 포인터를 NULL로 초기화
	struct ListNode* pTail = NULL; // 테일 포인터를 NULL로 초기화
	int* list_size = 0; // 리스트 사이즈
	int input_value = 0, input_idx = 0;
	EMY_MENU menu = -1;

	while ((menu = PrintMenu()) != 0)
	{
		switch (menu)
		{
			// 1. InsertFirst 수행
		case INSERT_FIRST:
			printf("값 입력: ");
			scanf_s("%d%*c", &input_value);
			InsertFirst(&pHead, &pTail, input_value);
			PrintList(pHead, pTail, "FORWARD", &list_size);
			PressAnyKeyMsg();
			break;

			// 2. InsertLast 수행
		case INSERT_LAST:
			printf("값 입력: ");
			scanf_s("%d%*c", &input_value);
			InsertLastDynamicArrayMult(&pHead, &pTail, input_value);
			PrintList(pHead, pTail, "FORWARD", &list_size);
			PressAnyKeyMsg();
			break;

			// 3. PrintList 수행
		case PRINT:
			PrintList(pHead, pTail, "FORWARD", &list_size);
			PressAnyKeyMsg();
			break;

			// 4. DeleteFirst 수행
		case DELETE_FIRST:
			DeleteFirst(&pHead, &pTail);
			PrintList(pHead, pTail, "FORWARD", &list_size);
			PressAnyKeyMsg();
			break;

			// 5. DeleteLast 수행
		case DELETE_LAST:
			DeleteLast(&pHead, &pTail);
			PrintList(pHead, pTail, "FORWARD", &list_size);
			PressAnyKeyMsg();
			break;

			// 6. PrintBackward 수행
		case PRINT_BACKWARD:
			PrintList(pHead, pTail, "BACKWARD", &list_size);
			PressAnyKeyMsg();
			break;

			// 0. 프로그램 종료
		case 0:
			exit(1);
			return;

			// 다시 입력 메세지 출력
		default:
			PrintInputAgain();
			PressAnyKeyMsg();
			break;
		}
	}
}

// 리스트 첫번째에 노드 추가
void InsertFirst(struct ListNode** ppHead, struct ListNode** ppTail, const int value)
{
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));

	// 메모리 할당 체크
	if (pNewNode == NULL)
	{
		PrintNewNodeMallocErr();
		return;
	}

	// 동적 할당한 노드에 데이터 초기화
	pNewNode->data = value;
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	if (*ppHead == NULL) // 헤드 포인터가 NULL을 가리키면
	{
		//pNewNode->idx = 0; // 새 노드를 인덱스 0 으로 하고
		*ppHead = pNewNode; // 헤드 포인터에 새 노드 주소값 입력
		*ppTail = pNewNode; // 테일 포인터에 새 노드 주소값 입력
	}
	else // 헤드 포인터가 노드를 가리키고 있으면
	{
		(*ppHead)->pPrev = pNewNode;
		pNewNode->pNext = *ppHead; // 새 노드의 다음을 헤드로 연결
		*ppHead = pNewNode; // 헤드를 새 노드의 주소값으로 설정
	}
}

// 리스트 마지막에 노드 추가
void InsertLastDynamicArrayMult(struct ListNode** ppHead, struct ListNode** ppTail, const int value)
{
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));

	// 메모리 할당 체크
	if (pNewNode == NULL)
	{
		PrintNewNodeMallocErr();
		return;
	}

	// 동적 할당한 노드에 데이터 초기화
	pNewNode->data = value;
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	if (*ppHead == NULL) // 헤드 포인터가 NULL을 가리키면
	{
		//pNewNode->idx = 0; // 새 노드를 인덱스 0 으로 하고
		*ppHead = pNewNode; // 헤드 포인터에 새 노드 주소값 입력
		*ppTail = pNewNode; // 테일 포인터에 새 노드 주소값 입력
	}
	else // 헤드 포인터가 노드를 가리키고 있으면
	{
		// 테일 노드 다음 노드를 테일 노드로 설정
		(*ppTail)->pNext = pNewNode;
		pNewNode->pPrev = (*ppTail);
		(*ppTail) = pNewNode;

		// Print Add Success
		PrintAddSuc();
	}
}

// 첫번째 노드 제거
void DeleteFirst(struct ListNode** ppHead, struct ListNode** ppTail)
{
	// 리스트에 노드 및 데이터가 없으면 종료
	if (*ppHead == NULL)
	{
		PrintDivider("LIST IS EMPTY", 73);
		return;
	}

	// 리스트에 헤드노드 단 하나만 남았을 때 실행 후 리턴
	if ((*(*ppHead)).pNext == NULL)
	{
		ListNode* pDelete = (ListNode*)*ppHead;
		free(pDelete);
		(*ppTail) = NULL;
		(*ppHead) = NULL;
		PrintDelSuc();
		return;
	}

	// 헤드노드의 주소를 pDelete에 입력, pHead는 기존 헤드노드의 다음 노드 주소값으로 설정 후 free(pDelete)
	ListNode* pDelete = (ListNode*)*ppHead;
	(*ppHead)->pNext->pPrev = NULL;
	*ppHead = (*(*ppHead)).pNext;
	free(pDelete);
	PrintDelSuc();
}

void DeleteLast(struct ListNode** ppHead, struct ListNode** ppTail)
{
	// 리스트에 노드 및 데이터가 없으면 종료
	if (*ppHead == NULL)
	{
		PrintDivider("LIST IS EMPTY", 73);
		return;
	}

	// 리스트에 헤드노드 단 하나만 남았을 때 실행 후 리턴
	if ((*(*ppHead)).pNext == NULL)
	{
		ListNode* pDelete = (ListNode*)*ppHead;
		free(pDelete);
		(*ppHead) = NULL;
		PrintDelSuc();
		return;
	}

	// pDelete에 리스트의 마지막 노드 입력 후 free(pDelete)
	ListNode* pDelete = (*ppTail);
	(*ppTail) = (*ppTail)->pPrev;
	(*ppTail)->pNext = NULL;
	free(pDelete);
	PrintDelSuc();
}

// 리스트 출력(Param(2)에 문자열로 "FORWARD" 혹은 "BACKWARD" 입력
void PrintList(struct ListNode* pHead, struct ListNode* pTail, const char* forward_or_backward, int* list_size)
{
	if (pHead == NULL)
		PrintDivider("LIST IS EMPTY", 73);

	if (forward_or_backward == "FORWARD")
	{
		ListNode* pIterator = pHead;
		int position = 0;

		PrintDivider("[LIST]", 73);

		while (pIterator != NULL)
		{
			printf("[DebugLog]: [Pos: %d] | [pPrev: %p] | [this: %p] | [Data: %d] | [pNext: %p]\n", position, pIterator->pPrev, pIterator, pIterator->data, pIterator->pNext);
			pIterator = pIterator->pNext;
			position++;
		}

		(*list_size) = position;
	}

	if (forward_or_backward == "BACKWARD")
	{
		ListNode* pIterator = pTail;
		int position = (*list_size);

		PrintDivider("[LIST]", 73);

		while (pIterator != NULL)
		{
			printf("[DebugLog]: [Pos: %d] | [pPrev: %p] | [this: %p] | [Data: %d] | [pNext: %p]\n", position, pIterator->pPrev, pIterator, pIterator->data, pIterator->pNext);
			pIterator = pIterator->pPrev;
			position--;
		}
	}

	putchar('\n');
}

// 다시 입력하라는 메세지 출력
void PrintInputAgain(void)
{
	printf("다시 입력해주세요.\n");
}

// NewNode 메모리 할당 실패시 오류 메세지 출력
void PrintNewNodeMallocErr(void)
{
	printf("[ErrorLog]: pNewNode 메모리 할당 실패!\n");
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

// 반복 루프가 다시 돌기 전 메세지 출력하고 아무 키나 받을때까지 기다림
void PressAnyKeyMsg(void)
{
	puts("계속하시려면 아무 키나 누르세요...");
	int dummy = _getch();
}

// 추가 성공 메세지 출력
void PrintAddSuc()
{
	printf("[DebugLog]: 추가 성공!\n");
}

// 삭제 성공 메세지 출력
void PrintDelSuc()
{
	printf("[DebugLog]: 삭제 성공!\n");
}

// 리스트 전부 제거
void DeleteAll(struct ListNode** ppHead)
{
	if (*ppHead == NULL)
	{
		printf("[DebugLog]: 제거할 리스트 없음.\n");
		return;
	}

	ListNode* pIterator = *ppHead;
	ListNode* pDelete = *ppHead;
	while (pIterator != NULL)
	{
		pDelete = pIterator;
		pIterator = pIterator->pNext;
		free(pDelete);
	}

	*ppHead = NULL;

	printf("[DebugLog]: 리스트가 전부 제거됨!\n");
}