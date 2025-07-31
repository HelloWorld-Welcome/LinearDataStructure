// 1주차 2차시 과제
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define SIZE 100 // 랜덤값 배열 크기
#define SELECT_SIZE 10 // 선택값 배열 크기
#define MIN_VALUE 0 // 난수의 최소값
#define MAX_VALUE 99 // 난수의 최대값

// 일정한 범위의 난수를 생성하여 일정한 크기의 배열에 저장하는 함수
void GenerateRandomNumbers(int* random_numbers);

// 생성하여 저장된 난수 중 임의의 수를 선택하여 배열에 저장
void SelectNumbers(int* random_numbers, int* selected_numbers);

// 선택값 배열에서 최댓값 찾기
void FindLargestNumber(int* largest, int* selected_numbers);

// 최댓값 출력
void PrintLargest(int* largest);

int main(void)
{
	int random_numbers[SIZE]; // SIZE 만큼의 랜덤값 배열 선언
	int selected_numbers[SELECT_SIZE]; // SELECT_SIZE 만큼의 선택값 배열 선언
	int largest; // 최댓값 변수 선언

	GenerateRandomNumbers(random_numbers); // 난수 생성 및 배열에 저장
	SelectNumbers(random_numbers, selected_numbers); // 난수 배열의 임의의 수를 SELECT_SIZE 크기의 배열에 저장
	FindLargestNumber(&largest, selected_numbers); // 선택값 배열에서 최댓값 찾기
	PrintLargest(&largest); // 최댓값 출력하기

	return 0;
}

// 일정한 범위의 난수를 생성하여 일정한 크기의 배열에 저장하는 함수
void GenerateRandomNumbers(int* random_numbers)
{
	srand((unsigned int)time(NULL)); //난수 초기화

	// 0부터 (배열 크기 - 1)까지 난수 생성하여 저장
	int i = 0;
	while (i != SIZE)
	{
		int generated_random_number = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE; // 생성된 난수
		int overlap_count = 0; // 중복 카운트

		// 배열을 순회하여 중복 체크
		for (int j = 0; j < i - 1; j++)
		{
			if (*(random_numbers + j) == generated_random_number)
			{
				overlap_count++; // 중복시 중복 카운트 1 증가
			}
		}

		// 중복 카운트가 0이면 해당 인덱스에 난수 저장하고 다음 인덱스로 이동
		if (overlap_count == 0)
		{
			*(random_numbers + i) = generated_random_number;
			i++;
		}
	}

	// 디버그용 출력
	printf("----------------- [랜덤값 배열] -----------------");
	putchar('\n');
	for (int i = 0; i < SIZE; i++)
	{
		printf("[%2d] ", random_numbers[i]);
		if ((i + 1) % 10 == 0) putchar('\n');
	}
	putchar('\n');
}

// 생성하여 저장된 난수 중 임의의 수를 선택하여 배열에 저장
void SelectNumbers(int* random_numbers, int* selected_numbers)
{
	int i = 0;
	int* selected_idx_arr = (int*)malloc(sizeof(int) * SELECT_SIZE);

	if (selected_idx_arr == NULL)
	{
		fprintf(stderr, "selected_idx_arr 메모리 할당 실패.");
		return;
	}

	while (i != SELECT_SIZE)
	{
		int idx = rand() % SIZE;
		int overlap_count = 0;

		// 배열을 순회하여 idx 중복 체크
		if (i != 0)
		{
			for (int j = 0; j < i - 1; j++)
			{
				if (*(selected_idx_arr + j) == idx)
				{
					overlap_count++; // 중복시 중복 카운트 1 증가
				}
			}
		}

		// 중복 카운트가 0이면 해당 인덱스에 임의의 수 저장하고 다음 인덱스로 이동
		if (overlap_count == 0)
		{
			*(selected_idx_arr + i) = idx;
			*(selected_numbers + i) = *(random_numbers + idx);
			i++;
		}
	}

	free(selected_idx_arr);

	// 디버그용 출력
	printf("----------------- [선택값 배열] -----------------");
	putchar('\n');
	for (int i = 0; i < SELECT_SIZE; i++)
	{
		printf("[%2d] ", selected_numbers[i]);
	}
	printf("\n\n");
}

// 선택값 배열에서 최댓값 찾기
void FindLargestNumber(int* largest, int* selected_numbers)
{
	*largest = *(selected_numbers + 0);

	for (int i = 0; i < SELECT_SIZE; i++)
	{
		if (*largest < selected_numbers[i])
		{
			*largest = selected_numbers[i];
		}
	}
}

// 최댓값 출력
void PrintLargest(int* largest)
{
	printf("-------------------------------------------------\n");
	printf("최댓값: %d\n", *largest);
}