// 4���� 2����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
	int pData;
	struct ListNode* pNext;
} ListNode;

struct ListNode* pHead = NULL;

void InsertFirst(const int value)
{
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));

	if (pNewNode == NULL)
	{
		printf("[ErrorLog]: pNewNode �޸� �Ҵ� ����!\n");
		return;
	}

	pNewNode->pData = value;
	pNewNode->pNext = NULL;

	if (pHead == NULL)
	{
		pHead = pNewNode;
	}
	else
	{
		pNewNode->pNext = pHead;
	}
}

void InsertLast(const int value)
{
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));

	if (pNewNode == NULL)
	{
		printf("[ErrorLog]: pNewNode �޸� �Ҵ� ����!\n");
		return;
	}

	pNewNode->pData = value;
	pNewNode->pNext = NULL;

	if (pHead == NULL)
	{
		pHead = pNewNode;
	}
	else
	{
		ListNode* pSelector = pHead;

		while (pSelector->pNext != NULL)
		{
			pSelector = pSelector->pNext;
		}

		pSelector->pNext = pNewNode;
	}
}

void PrintList()
{
	ListNode* pSelector = pHead;

	printf("---------------------------------------------\n");

	while (pSelector->pNext != NULL)
	{
		printf("[DebugLog]: [%p] | Value: %d | [%p]\n", pSelector, pSelector->pData, pSelector->pNext);

		pSelector = pSelector->pNext;
	}
}

void PrintInputAgain()
{
	printf("�ٽ� �Է����ּ���.\n");
}

main(void)
{
	int input, input_value = 0;

	printf("1. InsertFirst\n");
	printf("2. InsertLast\n");
	printf("3. PrintList\n");
	printf("4. Exit");
	printf("�Է�: ");

	scanf_s("%d%*c", &input);

	switch (input)
	{
	case 1:
		printf("�� �Է�: ");
		scnaf_s("%d%*c", &input_value);
		InsertFirst(input_value);
		PrintList();
		break;

	case 2:
		printf("�� �Է�: ");
		scnaf_s("%d%*c", &input_value);
		InsertLast(input_value);
		PrintList();
		break;

	case 3:
		PrintList();
		break;

	case 4:
		return;

	default:
		PrintInputAgain();
		break;
	}
}
