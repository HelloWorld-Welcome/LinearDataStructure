// 9주차 1차시
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 데이터 타입
typedef int element;

// 배열형 Stack 구조체
typedef struct StackArray
{
	int capacity; // Stack 크기
	int top; // 사용된 Stack 크기
	element* element_arr; // 데이터 배열
} StackArray;

// 배열형 Stack 구조체를 동적 생성하여 주소값을 리턴
StackArray* CreateStack(const int size);

// 배열형 Stack 구조체가 Full인지 확인
bool IsFull(StackArray* const array);

// 배열형 Stack 구조체가 Empty인지 확인
bool IsEmpty(StackArray* const array);

// 배열형 Stack 구조체 포인터가 Nullptr인지 확인
bool IsNullArray(const StackArray* const array);

// 배열형 Stack 구조체에 데이터 Push (InsertLast)
void Push(StackArray* const array, const int item);

// 배열형 Stack 구조체에 데이터 Pop (DeleteLast)
void Pop(StackArray* const array);

// 배열형 Stack 구조체 데이터 출력
void PrintStack(const StackArray* const array);

// Stack이 Nullptr이면 출력
void PrintStackIsNull();

// Stack이 Full이면 출력
void PrintStackIsFull();

// Stack이 Empty이면 출력
void PrintStackIsEmpty();

main(void)
{
	// [1]: 입력
	StackArray* main_array = CreateStack(6);

	// [2]: 처리
	Push(main_array, 10);
	Push(main_array, 20);
	Push(main_array, 30);
	Push(main_array, 40);
	Push(main_array, 50);
	Push(main_array, 60);
	Push(main_array, 70);

	// [3]: 출력
	PrintStack(main_array);

	// [2]: 처리
	Pop(main_array);
	Pop(main_array);
	Pop(main_array);
	Pop(main_array);
	Pop(main_array);
	Pop(main_array);
	Pop(main_array);

	return 0;
}

// 배열형 Stack 구조체를 동적 생성하여 주소값을 리턴
StackArray* CreateStack(const int size)
{
	StackArray* array_created = (StackArray*)malloc(sizeof(StackArray));

	// 동적 할당 실패시 NULLPTR 리턴
	if (array_created == NULL)
	{
		PrintStackIsNull();
		return NULL;
	}

	array_created->capacity = size;
	array_created->top = 0;
	array_created->element_arr = (element*)malloc(sizeof(element) * size);

	return array_created;
}

// 배열형 Stack 구조체가 Full인지 확인
bool IsFull(const StackArray* const array)
{
	if (array->capacity == array->top)
		return true;

	return false;
}

// 배열형 Stack 구조체가 Empty인지 확인
bool IsEmpty(const StackArray* const array)
{
	if (array->top == 0)
		return true;

	return false;
}

// 배열형 Stack 구조체 포인터가 Nullptr인지 확인
bool IsNullArray(const StackArray* const array)
{
	if (array == NULL)
		return true;

	return false;
}

// 배열형 Stack 구조체에 데이터 Push (InsertLast)
void Push(StackArray* const array, const int item)
{
	// 배열형 Stack 구조체 포인터가 Nullptr인지 체크
	if (IsNullArray(array))
	{
		PrintStackIsNull();
		return;
	}

	// 배열형 Stack 구조체가 Full인지 체크
	if (IsFull(array))
	{
		PrintStackIsFull();
		return;
	}

	*((array->element_arr) + (array->top)++) = item;
}

// 배열형 Stack 구조체에 데이터 Pop (DeleteLast)
void Pop(StackArray* const array)
{
	// 배열형 Stack 구조체 포인터가 Nullptr인지 체크
	if (IsNullArray(array))
	{
		PrintStackIsNull();
		return;
	}

	// 배열형 Stack 구조체가 Empty인지 체크
	if (IsEmpty(array))
	{
		PrintStackIsEmpty();
		return;
	}

	(array->top)--;
}

// 배열형 Stack 구조체 데이터 출력
void PrintStack(const StackArray* const array)
{
	// 배열형 Stack 구조체 포인터가 Nullptr인지 체크
	if (IsNullArray(array))
	{
		PrintStackIsNull();
		return;
	}

	if (IsEmpty(array))
	{
		PrintStackIsEmpty();
		return;
	}

	int count = 0;
	for (int i = 0; i < array->top; i++)
	{
		printf("[%d] ", *(array->element_arr + i));
		count++;

		if (count % 10 == 0)
			putchar('\n');
	}

	putchar('\n');
}

// Stack이 Nullptr이면 출력
void PrintStackIsNull()
{
	printf("StackArray가 NULLPTR 입니다.\n");
	return;
}

// Stack이 Full이면 출력
void PrintStackIsFull()
{
	printf("StackArray가 포화상태 입니다.\n");
	return;
}

// Stack이 Empty이면 출력
void PrintStackIsEmpty()
{
	printf("StackArray가 진공상태 입니다.\n");
	return;
}