// 5주차 2차시
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// 메뉴 열거형
typedef enum EMY_MENU
{
	EXIT, INSERT_FIRST, INSERT_LAST, INSERT_BY_POSITION, PRINT, DELETE_FIRST, DELETE_LAST, DELETE_ALL, SEARCH_BY_VALUE, DELETE_BY_INDEX, INSERT_AFTER_THIRTY
} EMY_MENU;

// 싱글 리스트 노드 구조체
typedef struct ListNode
{
	//int idx;
	int data;
	struct ListNode* pNext;
} ListNode;

// 검색 리스트 노드 구조체
typedef struct SearchedList
{
	struct ListNode* pData;
	struct ListNode* pNext;
} SearchedList;

// 메뉴 출력
EMY_MENU PrintMenu(void);

// 이벤트 루프 함수
void EventLoopRun(void);

// 리스트 첫번째에 노드 추가
void InsertFirst(struct ListNode** ppHead, const int value);

// 리스트 마지막에 노드 추가
void InsertLastDynamicArrayMult(struct ListNode** ppHead, const int value);

// 리스트의 특정 포지션에 노드 추가
void InsertByPosition(struct ListNode** ppHead, const int pos, const int value);

// 리스트 첫번째 노드 제거
void DeleteFirst(struct ListNode** ppHead);

// 리스트 마지막 노드 제거
void DeleteLast(struct ListNode** ppHead);

// 리스트의 특정 포지션 노드 제거
void DeleteByPosition(struct ListNode** ppHead, const int pos);

// 30 데이터를 가진 노드 이후에 35 데이터 노드 추가
void PrintBackward(struct ListNode** ppHead);

// 리스트 검색
void SearchByValue(struct SearchedList** ppSHead, struct ListNode* pHead, const int value);

// 검색 리스트에 노드 추가
void InsertSearchedList(struct SearchedList** ppSHead, struct ListNode* pNode);

// 검색 리스트 출력
void PrintSearchedList(struct SearchedList* pSHead);

// 검색 리스트 전부 제거
void DeleteAllSearchedList(struct SearchedList** ppSHead);

// 리스트의 포지션을 다시 재조정 하는 함수
//void SortListIdx(struct ListNode** ppHead);

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
	printf("[3] Insert By Position\n");
	printf("[4] Print List\n");
	printf("[5] Delete First\n");
	printf("[6] Delete Last\n");
	printf("[7] Delete All\n");
	printf("[8] Search Result\n");
	printf("[9] Delete By Position\n");
	printf("[10] Insert After 30\n");
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

		case INSERT_BY_POSITION:
			printf("포지션 입력: ");
			scanf_s("%d%*c", &input_idx);
			printf("값 입력: ");
			scanf_s("%d%*c", &input_value);
			InsertByPosition(&pHead, input_idx, input_value);
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

			// 6. DeleteAll 수행
		case DELETE_ALL:
			DeleteAll(&pHead);
			PrintList(pHead);
			PressAnyKeyMsg();
			break;

			// 7. SearchByValue 수행
		case SEARCH_BY_VALUE:
			printf("찾을 값 입력: ");
			scanf_s("%d%*c", &input_value);
			SearchByValue(&pSHead, pHead, input_value);
			PrintSearchedList(pSHead);
			DeleteAllSearchedList(&pSHead);
			PressAnyKeyMsg();
			break;

			// 8. DeleteByIndex 수행
		case DELETE_BY_INDEX:
			printf("삭제할 포지션 입력: ");
			scanf_s("%d%*c", &input_idx);
			DeleteByPosition(&pHead, input_idx);
			PrintList(pHead);
			PressAnyKeyMsg();
			break;

		case INSERT_AFTER_THIRTY:
			PrintBackward(&pHead);
			PrintList(pHead);
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
	}
	else // 헤드 포인터가 노드를 가리키고 있으면
	{
		pNewNode->pNext = *ppHead; // 새 노드의 다음을 헤드로 연결
		*ppHead = pNewNode; // 헤드를 새 노드의 주소값으로 설정

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
	}
	else // 헤드 포인터가 노드를 가리키고 있으면
	{
		ListNode* pIterator = *ppHead; // 반복자를 헤드 포인터로 설정하고

		// 반복자가 연결 리스트의 끝까지 도달할 때까지 반복
		while (pIterator->pNext != NULL)
		{
			pIterator = pIterator->pNext;
		}

		// 반복자가 연결 리스트의 끝에 도달시 새 노드를 연결
		pIterator->pNext = pNewNode;

		// Print Add Success
		PrintAddSuc();

		// 인덱스 재정렬
		//SortListIdx(ppHead);
	}
}

// 해당 포지션에 노드 추가
void InsertByPosition(struct ListNode** ppHead, const int pos, const int value)
{
	// pos가 음수일 때 예외처리
	if (pos < 0)
	{
		printf("[ErrorLog]: 해당 포지션에 데이터 노드를 추가할 수 없습니다.(idx가 음수)\n");
		return;
	}

	// pos가 0일 때 InsertFirst실행
	if (pos == 0)
	{
		InsertFirst(ppHead, value);
		return;
	}

	// 반복자에 헤드노드 주소 입력
	ListNode* pIterator = (ListNode*)*ppHead;
	int position = 0;

	// 반복자가 마지막 리스트의 다음에 접근하면 새 노드를 추가하고 전체 리스트 정렬 후 종료
	while (pIterator != NULL)
	{
		// 마지막 노드 다음 노드에 추가하려는 경우 InsertLast를 실행
		if (pIterator->pNext == NULL && position + 1 == pos)
		{
			InsertLastDynamicArrayMult(ppHead, value);
			return;
		}

		// 포지션을 찾으면 반복자가 가리키는 노드의 다음 노드에 새 노드를 추가하고 종료
		if (position == pos)
		{
			ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));
			if (pNewNode == NULL)
			{
				PrintNewNodeMallocErr();
				return;
			}

			pNewNode->data = value;
			pNewNode->pNext = pIterator->pNext;
			pIterator->pNext = pNewNode;

			//SortListIdx(ppHead);

			return;
		}

		pIterator = pIterator->pNext;
		position++;
	}

	printf("[ErrorLog]: 해당 포지션에 데이터 노드를 추가할 수 없습니다.(포지션 범위 초과)\n");
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
	if ((*(*ppHead)).pNext == NULL)
	{
		ListNode* pDelete = (ListNode*)*ppHead;
		free(pDelete);
		(*ppHead) = NULL;
		PrintDelSuc();
		return;
	}

	// 헤드노드의 주소를 pDelete에 입력, pHead는 기존 헤드노드의 다음 노드 주소값으로 설정 후 free(pDelete)
	ListNode* pDelete = (ListNode*)*ppHead;
	*ppHead = (*(*ppHead)).pNext;
	free(pDelete);
	PrintDelSuc();
	//SortListIdx(ppHead);
}

void DeleteLast(struct ListNode** ppHead)
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

	// 반복자로 리스트의 마지막 전 노드까지 도달
	ListNode* pIterator = (ListNode*)*ppHead;
	while (pIterator->pNext->pNext != NULL)
	{
		pIterator = pIterator->pNext;
	}

	// pDelete에 리스트의 마지막 노드 입력 후 free(pDelete)
	ListNode* pDelete = pIterator->pNext;
	pIterator->pNext = NULL; // 마지막 전 노드의 다음 주소값은 없는 주소를 가리키면 안 되므로 NULL로 설정
	free(pDelete);
	PrintDelSuc();
	//SortListIdx(ppHead);
}

void DeleteByPosition(ListNode** ppHead, const int pos)
{
	// 리스트가 비었고 0이 아닌 인덱스에 접근하려 할 때 오류메세지 출력하고 리턴
	// Q: 이 예외는 함수에서 처리하는 것이 나은 것인가 아님 입력단계에서 처리하는 것이 나은 것인가
	if (*ppHead == NULL)
	{
		printf("[ErrorLog]: 해당 포지션의 데이터 노드를 삭제할 수 없습니다.(Empty List)\n");
		return;
	}
	if (pos != 0 && pos < 0)
	{
		printf("[ErrorLog]: 해당 포지션의 데이터 노드를 삭제할 수 없습니다.(Pos가 음수)\n");
		return;
	}
	if (pos == 0)
	{
		DeleteFirst(ppHead);
		return;
	}

	ListNode* pIterator = (ListNode*)*ppHead;
	ListNode* pPrev = pIterator;
	int position = 0;

	// 반복자가 포지션을 찾으면 해당 노드의 전 노드와 다음 노드를 연결하고 free(pIterator)
	while (pIterator->pNext != NULL)
	{
		if (position == pos)
		{
			pPrev->pNext = pIterator->pNext;
			free(pIterator);
			//SortListIdx(ppHead);
			return;
		}
		pPrev = pIterator;
		pIterator = pIterator->pNext;
		position++;
	}

	// 마지막 노드 포지션를 입력했을 때
	if (pIterator->pNext == NULL && position == pos)
	{
		DeleteLast(ppHead);
		return;
	}

	printf("[ErrorLog]: 해당 포지션의 데이터 노드를 삭제할 수 없습니다.(포지션 범위 초과)\n");
}

// Data가 30인 노드 뒤에 Data가 35인 노드 삽입
void PrintBackward(struct ListNode** ppHead)
{
	if (*ppHead == NULL)
	{
		printf("[DebugLog]: 리스트가 비어있습니다.\n");
		return;
	}

	ListNode* pIterator = (ListNode*)*ppHead;
	int position = 0;

	// 30을 찾기 위해 반복
	while (pIterator->pNext != NULL)
	{
		// 반복자가 30을 찾으면
		if (pIterator->data == 30)
		{
			// 반복자의 다음 노드에 35를 추가
			InsertByPosition(ppHead, position, 35);
			return;
		}
		pIterator = pIterator->pNext;
		position++;
	}

	// 반복자가 마지막 노드에 도달했을 때 데이터가 30이면 다음 노드 35 추가
	if (pIterator->data == 30)
	{
		InsertLastDynamicArrayMult(ppHead, 35);
		return;
	}

	// 반복자가 30을 찾지 못했으면 출력
	printf("[DebugLog]: 30을 찾지 못했습니다.\n");
}

// Data값을 기준으로 검색
void SearchByValue(struct SearchedList** ppSHead, struct ListNode* pHead, const int value)
{
	ListNode* pIterator = (ListNode*)pHead;
	int cnt = 0;

	if (pIterator == NULL)
	{
		return;
	}

	while (pIterator != NULL)
	{
		if (pIterator->data == value)
		{
			InsertSearchedList(ppSHead, pIterator);
		}
		pIterator = pIterator->pNext;
		cnt++;
	}

	if (cnt == 0)
		printf("리스트에 %d이 포함되어 있지 않습니다.\n", value);
}

// 검색 리스트에 노드 추가
void InsertSearchedList(struct SearchedList** ppSHead, struct ListNode* pNode)
{
	SearchedList* pSearchedNode = (SearchedList*)malloc(sizeof(SearchedList));

	// 메모리 할당 체크
	if (pSearchedNode == NULL)
	{
		PrintNewNodeMallocErr();
		return;
	}

	// 동적 할당한 노드에 데이터 초기화
	pSearchedNode->pData = pNode;
	pSearchedNode->pNext = NULL;

	if (*ppSHead == NULL) // 헤드 포인터가 NULL을 가리키면
	{
		*ppSHead = pSearchedNode; // 헤드 포인터에 새 노드 주소값 입력
	}
	else // 헤드 포인터가 노드를 가리키고 있으면
	{
		SearchedList* pIterator = *ppSHead; // 반복자를 헤드 포인터로 설정하고

		// 반복자가 연결 리스트의 끝까지 도달할 때까지 반복
		while (pIterator->pNext != NULL)
		{
			pIterator = pIterator->pNext;
		}

		// 반복자가 연결 리스트의 끝에 도달시 새 노드를 연결
		pIterator->pNext = pSearchedNode;
	}
}

// 검색 리스트 출력
void PrintSearchedList(struct SearchedList* pSHead)
{
	SearchedList* pIterator = (SearchedList*)pSHead;
	int position = 0;

	PrintDivider("[SEARCH RESULT]", 73);

	while (pIterator != NULL)
	{
		printf("[DebugLog]: [Pos: %d] | [this: %p] | [Value: %d] | [pNext: %p]\n", position, pIterator, pIterator->pData->data, pIterator->pData->pNext);
		pIterator = pIterator->pNext;
		position++;
	}
}

// 검색 리스트 전부 제거
void DeleteAllSearchedList(struct SearchedList** ppSHead)
{
	if (*ppSHead == NULL)
	{
		printf("[DebugLog]: 제거할 리스트 없음.\n");
		return;
	}

	SearchedList* pIterator = *ppSHead;
	SearchedList* pDelete = *ppSHead;
	while (pIterator != NULL)
	{
		pDelete = pIterator;
		pIterator = pIterator->pNext;
		free(pDelete);
	}

	*ppSHead = NULL;

	printf("[DebugLog]: 검색 리스트가 전부 제거됨!\n");
}

// 리스트 출력
void PrintList(ListNode* pHead)
{
	ListNode* pIterator = pHead;
	int position = 0;

	PrintDivider("[LIST]", 73);

	while (pIterator != NULL)
	{
		printf("[DebugLog]: [Pos: %d] | [this: %p] | [Value: %d] | [pNext: %p]\n", position, pIterator, pIterator->data, pIterator->pNext);
		pIterator = pIterator->pNext;
		position++;
	}

	if (pHead == NULL)
		PrintDivider("LIST IS EMPTY", 73);

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
