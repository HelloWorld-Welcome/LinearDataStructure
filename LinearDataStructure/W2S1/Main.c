// 2주차 1차시
#include <stdio.h>
#include <stdlib.h>

#define ROW 3 // 행
#define COL 3 // 열

// 매트릭스 주소, 행 또는 열의 번호, 행인지 열인지 구분자를 파라미터로 받아 합을 계산
int sum(int** matrix, int num, const char* RC);

int main()
{
	int** matrix = (int**)malloc(sizeof(int*) * ROW); // 이중 포인터로 행렬의 행 크기만큼 할당

	// 행렬의 각 행에 열 크기만큼 할당
	for (int i = 0; i < ROW; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int) * COL);
	}

	// 행렬에 수 입력
	int init = 1;
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			matrix[r][c] = init++;
		}
	}

	// 디버그용 출력
	printf("\\   1C  2C  3C\n");
	for (int r = 0; r < ROW; r++)
	{
		printf("%dR ", r + 1);
		for (int c = 0; c < COL; c++)
		{
			printf("[%d] ", matrix[r][c]);
		}
		putchar('\n');
	}

	printf("합을 구할 행 또는 열을 입력하세요. ex) 1행 -> 1R\n");

	char input[3]; // 입력을 받을 캐릭터 배열
	scanf_s("%2s", input, (unsigned int)sizeof(input)); // 입력 받기

	int num = input[0] - '0'; // 입력 받은 캐릭터 배열의 0 인덱스를 int로 저장
	printf("합: %d\n", sum(matrix, num, &input[1]));

	// 메모리 해제
	for (int i = 0; i < ROW; i++)
	{
		free(matrix[i]);
	}
	free(matrix);

	return 0;
}

int sum(int** matrix, int num, const char* RC)
{
	int total = 0;

	if (*RC == 'R') // (num - 1)번 행(R)일 경우 
	{
		for (int c = 0; c < COL; c++)
		{
			total += matrix[num - 1][c];
		}
	}
	else if (*RC == 'C') // (num - 1)번 열(C)일 경우 
	{
		for (int r = 0; r < ROW; r++)
		{
			total += matrix[r][num - 1];
		}
	}

	return total;
}