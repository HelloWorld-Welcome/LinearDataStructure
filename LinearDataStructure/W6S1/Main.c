// 6주차 1차시
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// 메뉴 열거형
typedef enum EMY_MENU
{
	EXIT, INSERT_FIRST, INSERT_LAST, PRINT, DELETE_FIRST, DELETE_LAST, CLOCK
} EMY_MENU;

// 싱글 리스트 노드 구조체
typedef struct ListNode
{
	//int idx;
	int data;
	struct ListNode* pNext;
} ListNode;

// 메뉴 출력
EMY_MENU PrintMenu(void);

// 이벤트 루프 함수
void EventLoopRun(void);

// 리스트 첫번째에 노드 추가
void InsertFirst(struct ListNode** ppHead, const int value);

// 리스트 마지막에 노드 추가
void InsertLastDynamicArrayMult(struct ListNode** ppHead, const int value);

// 리스트 첫번째 노드 제거
void DeleteFirst(struct ListNode** ppHead);

// 리스트 마지막 노드 제거
void DeleteLast(struct ListNode** ppHead);

// 리스트 출력
void PrintList(ListNode* pHead);

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

// 리스트 전부 제거
void DeleteAll(struct ListNode** ppHead);

void Clock(struct ListNode** ppHead, const int n1, const int n2);

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
	printf("[6] CLOCK\n");
	printf("[0] Exit\n");
	scanf_s("%d%*c", &input);

	return input;
}

// 이벤트 루프 함수
void EventLoopRun(void)
{
	struct ListNode* pHead = NULL; // 헤드 포인터를 NULL로 초기화
	struct SearchedList* pSHead = NULL;
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
			InsertFirst(&pHead, input_value);
			PrintList(pHead);
			PressAnyKeyMsg();
			break;

			// 2. InsertLast 수행
		case INSERT_LAST:
			printf("값 입력: ");
			scanf_s("%d%*c", &input_value);
			InsertLastDynamicArrayMult(&pHead, input_value);
			PrintList(pHead);
			PressAnyKeyMsg();
			break;

			// 3. PrintList 수행
		case PRINT:
			PrintList(pHead);
			PressAnyKeyMsg();
			break;

			// 4. DeleteFirst 수행
		case DELETE_FIRST:
			DeleteFirst(&pHead);
			PrintList(pHead);
			PressAnyKeyMsg();
			break;

			// 5. DeleteLast 수행
		case DELETE_LAST:
			DeleteLast(&pHead);
			PrintList(pHead);
			PressAnyKeyMsg();
			break;

			// 6. CLOCK 수행
		case CLOCK:
			printf("1~12의 시간을 입력: ");
			scanf_s("%d%*c", &input_value);
			if (input_value < 1 || input_value > 12)
			{
				printf("잘못된 입력입니다.\n");
				PressAnyKeyMsg();
				break;
			}
			printf("1~50의 시간을 입력: ");
			scanf_s("%d%*c", &input_idx);
			if (input_idx < 1 || input_idx > 50)
			{
				printf("잘못된 입력입니다.\n");
				PressAnyKeyMsg();
				break;
			}
			Clock(&pHead, input_value, input_idx);
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
void InsertFirst(struct ListNode** ppHead, const int value)
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
	pNewNode->pNext = NULL;

	if (*ppHead == NULL) // 헤드 포인터가 NULL을 가리키면
	{
		//pNewNode->idx = 0; // 새 노드를 인덱스 0 으로 하고
		*ppHead = pNewNode; // 헤드 포인터에 새 노드 주소값 입력
		pNewNode->pNext = *ppHead; // 새 노드의 다음을 헤드로 연결
	}
	else // 헤드 포인터가 노드를 가리키고 있으면
	{
		pNewNode->pNext = (*(*ppHead)).pNext; // 새 노드의 다음을 헤드의 다음 노드로 연결
		(*(*ppHead)).pNext = pNewNode; // 헤드의 다음 노드를 새 노드의 주소값으로 설정

		//SortListIdx(ppHead);
	}
}

// 리스트 마지막에 노드 추가
void InsertLastDynamicArrayMult(struct ListNode** ppHead, const int value)
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
	pNewNode->pNext = NULL;

	if (*ppHead == NULL) // 헤드 포인터가 NULL을 가리키면
	{
		//pNewNode->idx = 0; // 새 노드를 인덱스 0 으로 하고
		*ppHead = pNewNode; // 헤드 포인터에 새 노드 주소값 입력
		pNewNode->pNext = *ppHead; // 새 노드의 다음을 헤드로 연결
	}
	else // 헤드 포인터가 노드를 가리키고 있으면
	{
		pNewNode->pNext = (*(*ppHead)).pNext; // 새 노드의 다음을 헤드의 다음 노드로 연결
		(*(*ppHead)).pNext = pNewNode; // 헤드의 다음 노드를 새 노드의 주소값으로 설정
		*ppHead = pNewNode; // 헤드 포인터에 새 노드 주소값 입력
		// Print Add Success
		PrintAddSuc();

		// 인덱스 재정렬
		//SortListIdx(ppHead);
	}
}

// 첫번째 노드 제거
void DeleteFirst(struct ListNode** ppHead)
{
	// 리스트에 노드 및 데이터가 없으면 종료
	if (*ppHead == NULL)
	{
		PrintDivider("LIST IS EMPTY", 73);
		return;
	}

	// 리스트에 헤드노드 단 하나만 남았을 때 실행 후 리턴
	if ((*(*ppHead)).pNext == *ppHead)
	{
		ListNode* pDelete = (ListNode*)*ppHead;
		*ppHead = NULL; // 헤드 포인터를 NULL로 설정
		free(pDelete);
		PrintDelSuc();
		return;
	}

	ListNode* pDelete = (*(*ppHead)).pNext; // 첫번째 노드의 주소를 pDelete에 입력
	(*ppHead)->pNext = pDelete->pNext; // 헤드의 다음을 pDelete의 다음으로 설정
	free(pDelete); // pDelete 메모리 해제
	PrintDelSuc();
	//SortListIdx(ppHead);
}

// 리스트 마지막 노드 제거
void DeleteLast(struct ListNode** ppHead)
{
	// 리스트에 노드 및 데이터가 없으면 종료
	if (*ppHead == NULL)
	{
		PrintDivider("LIST IS EMPTY", 73);
		return;
	}

	// 리스트에 헤드노드 단 하나만 남았을 때 실행 후 리턴
	if ((*(*ppHead)).pNext == *ppHead)
	{
		ListNode* pDelete = (ListNode*)*ppHead;
		*ppHead = NULL; // 헤드 포인터를 NULL로 설정
		free(pDelete);
		PrintDelSuc();
		return;
	}

	// 반복자로 리스트의 마지막 전 노드까지 도달
	ListNode* pIterator = (ListNode*)(*ppHead)->pNext;
	while (pIterator->pNext != *ppHead)
	{
		pIterator = pIterator->pNext;
	}

	ListNode* pDelete = *ppHead; // 헤드노드의 주소를 삭제 pDelete에 입력
	*ppHead = pIterator; // 헤드 포인터를 마지막 전 노드로 설정
	(*ppHead)->pNext = pDelete->pNext; // 헤드의 다음을 pDelete의 다음으로 설정
	free(pDelete); // 기존의 헤드 주소 해제
	PrintDelSuc();
	//SortListIdx(ppHead);
}

// 시계 기능
void Clock(struct ListNode** ppHead, const int n1, const int n2)
{
	DeleteAll(ppHead); // 리스트 전부 제거
	// 리스트에 1~12까지의 숫자 노드 추가
	for (int i = 1; i < 13; i++)
	{
		InsertLastDynamicArrayMult(ppHead, i);
	}

	ListNode* pIterator = *ppHead;
	while (pIterator->data != n1) // n1시각 찾아서 출력
	{
		pIterator = pIterator->pNext;
	}
	printf("[DebugLog]: [N1: %2d] | [this: %p] | [HOUR: %2d] | [pNext: %p]\n", n1, pIterator, pIterator->data, pIterator->pNext);

	for (int i = 0; i < n2; i++) // n2시각까지 반복한 후 n2시각 찾아서 출력
	{
		pIterator = pIterator->pNext;
	}
	printf("[DebugLog]: [N2: %2d] | [this: %p] | [HOUR: %2d] | [pNext: %p]\n", n2, pIterator, pIterator->data, pIterator->pNext);
}

// 리스트 출력
void PrintList(ListNode* pHead)
{
	// 리스트가 비었으면 실행 후 리턴
	if (pHead == NULL)
	{
		PrintDivider("LIST IS EMPTY", 73);
		putchar('\n');
		return;
	}

	// 반복자에 첫번째 노드 주소로 설정
	ListNode* pIterator = pHead->pNext;
	int position = 0;

	PrintDivider("[LIST]", 73);

	while (pIterator != pHead)
	{
		printf("[DebugLog]: [Pos: %d] | [this: %p] | [Value: %d] | [pNext: %p]\n", position, pIterator, pIterator->data, pIterator->pNext);
		pIterator = pIterator->pNext;
		position++;
	}
	// 반복문은 반복자가 헤드 주소 도달 후 종료되므로 반복문 밖에서 헤드값 출력
	printf("[DebugLog]: [Pos: %d] | [this: %p] | [Value: %d] | [pNext: %p]\n", position, pIterator, pIterator->data, pIterator->pNext);

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
	// 리스트가 비었으면 출력하고 리턴
	if (*ppHead == NULL)
	{
		printf("[DebugLog]: 제거할 리스트 없음.\n");
		return;
	}

	// pIterator와 pDelete를 첫번째 노드로 변경
	ListNode* pIterator = (*ppHead)->pNext;
	ListNode* pDelete = (*ppHead)->pNext;

	// 반복자로 마지막 노드(헤드 노드) 전 노드까지 도달
	while (pIterator->pNext != *ppHead)
	{
		pDelete = pIterator;
		pIterator = pIterator->pNext;
		free(pDelete);
	}

	// 마지막 노드(헤드노드) 전 노드 메모리 해제
	free(pIterator);
	pDelete = *ppHead; // pDelete에 헤드 포인터 입력
	*ppHead = NULL; // 헤드 노드를 NULL로 설정
	free(pDelete); // 기존 헤드 노드 주소 메모리 해제

	printf("[DebugLog]: 리스트가 전부 제거됨!\n");
}
