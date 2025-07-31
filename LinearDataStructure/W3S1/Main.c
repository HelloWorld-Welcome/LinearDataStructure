// 3주차 1차시 과제
#include "MyString.h"
#include "math.h"

// Student 구조체
typedef struct Student
{
	String* name;
	int age;
	double score;
} Student;

// 정보를 입력하는 함수
void Input(struct Student* const students, int* number_of_students);

// 평균을 계산하는 함수
double CalcAvg(const struct Student* students, const int number_of_students);

// 학생 정보를 출력하는 함수
void ShowStudentInfo(const struct Student* const students, const int number_of_students);

main(void)
{
	// [0]: 초기화
	struct Student* arr_st = (Student*)malloc(sizeof(Student)); // 

	if (arr_st == NULL)
		return;

	int number_of_students = 0;
	double avg = 0;

	// [1]: 입력
	Input(arr_st, &number_of_students);

	// [2]: 처리
	avg = CalcAvg(arr_st, number_of_students);

	// [3]: 출력
	ShowStudentInfo(arr_st, number_of_students);
	printf("전체 성적 평균: %.1lf", avg);

	return 0;
}

void Input(struct Student* const students, int* number_of_students)
{
	printf("학생 수: ");
	scanf_s("%d", number_of_students);

	for (int i = 0; i < *number_of_students; i++)
	{
		char* name_input = (char*)malloc(sizeof(char) * 32); // 이름 입력받을 문자열 동적할당
		int age_input; // 나이 입력받을 변수
		double score_input; // 성적 입력받을 변수

		// 동적할당한 문자열 널체크
		if (name_input == NULL)
			return;

		// 사용자 입력
		printf("학생의 이름: ");
		scanf_s("%s", name_input, 32);
		printf("학생의 나이: ");
		scanf_s("%d", &age_input);
		printf("학생의 성적: ");
		scanf_s("%lf", &score_input);

		// 문자열 크기를 실문자열 길이로 최적화
		int size = strlen(name_input) + 1;
		char* name_resized = (char*)calloc(size, sizeof(char));

		if (name_resized == NULL)
			return;

		for (int i = 0; i < size; i++)
		{
			*(name_resized + i) = *(name_input + i);
		}

		// 기존 문자열 메모리 해제
		free(name_input);

		// 구조체에 데이터 입력
		(students + i)->name = NewString(name_resized);
		(students + i)->age = age_input;
		(students + i)->score = score_input;
	}
}

// 평균을 계산하는 함수
double CalcAvg(const struct Student* students, const int number_of_students)
{
	double sum = 0;
	double avg = 0;
	for (int i = 0; i < number_of_students; i++)
		sum += (students + i)->score;


	avg = sum / number_of_students;

	return avg;
}

// 학생 정보를 출력하는 함수
void ShowStudentInfo(const struct Student* const students, const int number_of_students)
{
	for (int i = 0; i < number_of_students; i++)
	{
		printf("------[학생 %d]------\n", i + 1);

		printf("이름: %s\n", (students + i)->name->chars);
		printf("나이: %d\n", (students + i)->age);
		printf("성적: %.1lf\n", (students + i)->score);
	}
}