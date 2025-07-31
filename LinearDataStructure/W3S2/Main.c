// 3주차 2차시 과제
#include "stdio.h"
#include "time.h"
#include "setjmp.h"
#include "Windows.h"

#define ALLOW_LIMIT 97 // (단위: %) 스택 사용량을 전체 중 몇%까지 혀용할 것인지.
// 97이하로 설정할 것을 권장
#define JUMP -1 // 저장된 환경 변수로 점프하게 하는 변수

#define CLOCKS_PER_SEC 1000

jmp_buf mark; // 환경 저장 변수

int apprx_value = 0; // 스택 오버플로우 근사값 (전역)

// 팩토리얼 재귀함수 
int factorial_recursion(int input, void* current_stack_addr, size_t stack_limit);

// 팩토리얼 순회함수
int factorial_iteration(int input);

// Windows 환경에서 스택 사용량 확인
size_t get_stack_usage(void* current_stack_addr);

// 메인
main()
{
	// [0]: 초기화
	int flag;
	void* base_stack_addr = &flag; // 기준 스택 주소 설정

	// Windows에서 스택 제한 가져오기
	ULONG_PTR lowLimit, highLimit;
	GetCurrentThreadStackLimits(&lowLimit, &highLimit);
	size_t stack_size = (size_t)(highLimit - lowLimit); // 스택 크기 계산

	clock_t start, finish; // 시작시간과 종료시간을 측정하는 변수
	double duration_rec, duration_itr; // 각각 재귀함수와 순회함수의 실행시간을 측정하는 변수

	int input = 1; // 팩토리얼 함수 입력 초기값

	// [1]: 입력, 처리, 출력
	if ((setjmp(mark) != 0)) // setjmp호출로 환경변수에 현재 스택 환경 저장 
		// longjmp가 호출되어 환경 변수의 값이 바뀌면 아래 스코프가 실행됨
	{
		puts("---------------------------------------------------");
		printf("Recursion: 스택 오버플로우 발생 근사값: %d\n", apprx_value + 1);

		start = clock();
		factorial_iteration(apprx_value + 1);
		finish = clock();
		duration_itr = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("Iteration은 k값(%d)에서도 실행되었습니다. 실행시간: %f초\n", apprx_value, duration_itr);
	}
	else // longjmp가 호출되지 않아 환경 변수의 값이 바뀌지 않았으면 아래 스코프가 실행됨
	{
		while (1) {
			int stack_addr;

			// 재귀 실행
			start = clock();
			factorial_recursion(input, &stack_addr, stack_size);
			finish = clock();
			duration_rec = (double)(finish - start) / CLOCKS_PER_SEC; // 실행시간 계산

			// 순환 실행
			start = clock();
			factorial_iteration(input);
			finish = clock();
			duration_itr = (double)(finish - start) / CLOCKS_PER_SEC; // 실행시간 계산

			// 결과 출력
			printf("Recursion| 입력값: %d | 실행시간: %f초\n", input, duration_rec);
			printf("Iteration| 입력값: %d | 실행시간: %f초\n", input, duration_itr);
			apprx_value = input++; // 입력값 증가
		}
	}
}

// 팩토리얼 재귀함수 
int factorial_recursion(int input, void* current_stack_addr, size_t stack_size)
{
	size_t stack_usage = get_stack_usage(current_stack_addr);

	// 스택 사용량이 (ALLOW_LIMIT)% 를 초과하면 경고 후 longjmp 실행
	if (stack_usage > ALLOW_LIMIT / 100.0 * (size_t)stack_size)
	{
		puts("---------------------------------------------------");
		printf("[경고] 스택 사용량이 예약된 공간의 %d%% 초과! 값: %d\n", ALLOW_LIMIT, apprx_value + 1);
		longjmp(mark, JUMP);
	}

	if (input <= 1)
		return 1;
	else
		return input * factorial_recursion(input - 1, current_stack_addr, stack_size);
}

// 팩토리얼 순회함수
int factorial_iteration(int num)
{
	int fac = 1;
	for (int i = num; i > 0; i--)
	{
		fac *= i;
	}

	return fac;
}

// Windows용 스택 사용량 확인 함수
size_t get_stack_usage(void* base_stack_addr)
{
	void* current_stack_addr;
	__asm {
		mov current_stack_addr, esp  // 현재 스택 포인터 가져오기
	}

	// 베이스 주소값(메인함수주소)에서 현재 스택 주소값 빼기 = 스택 사용량
	return (size_t)((char*)base_stack_addr - (char*)current_stack_addr);
}