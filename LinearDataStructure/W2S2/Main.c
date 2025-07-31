// 2추자 2차시
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define STR_SIZE 32 // 문자열 크기

typedef struct String
{
    size_t size;
    char* str;
    struct String* (*GenString)(const char* chars);
} String;

struct String* GenString(const char* chars)
{
    size_t size = strlen(chars) + 1;
    struct String* str_gen = (String*)malloc(sizeof(struct String));

    if (str_gen == NULL)
    {
        return;
    }

    str_gen->str = (char*)calloc(size, sizeof(char));

    if (str_gen->str != NULL)
    {
        strcpy_s(str_gen->str, sizeof(str_gen->str), chars);

        return str_gen;
    }

    return;
}


void Reverse(char* str)
{
    int str_size = strlen(str) + 1;
    char* str_tmp = (char*)malloc(str_size * sizeof(char));

    if (str_tmp == NULL)
    {
        return;
    }
    for (int i = 0; i < strlen(str); i++)
    {
        *(str_tmp + i) = *(str + strlen(str) - 1 - i);
    }

    *(str_tmp + strlen(str)) = '\0';

    strcpy_s(str, str_size, str_tmp);

    free(str_tmp);
}

// 입력
void Input(char* str);

// 처리: 문자열을 받아 숫자를 빼고 뒤집는 함수
char* ReverseWithoutNumber(char* str);

// 결과
void Output(const char* str, const char* str_reversed);

// 메모리 동적할당 실패 메세지
void PrintMemoryAllocationError();

int main()
{
    // [0] 초기화
    char* str = (char*)malloc(STR_SIZE * sizeof(char)); // 원본 문자열
    char* str_reversed; // 뒤집은 문자열

    // NULL 포인터 체크
    if (str == NULL)
    {
        PrintMemoryAllocationError();
        return 1;
    }

    // [1] 입력
    Input(str);

    // [2] 처리
    str_reversed = ReverseWithoutNumber(str);

    // [3] 결과 
    Output(str, str_reversed);

    // 메모리 해제
    free(str);
    free(str_reversed);

    return 0;
}

void Input(char* str)
{
    printf("%d 만큼의 문자를 입력할 수 있습니다.\n", STR_SIZE - 1);
    printf("입력: ");
    scanf_s("%s", str, STR_SIZE); // STR_SIZE 변경시 수정 필요
}

char* ReverseWithoutNumber(char* str)
{
    /*
        [용어 정의]
        문자열 크기 = 문자 배열의 크기('\0'(Null) 크기 포함)
        문자열 길이 = 문자 배열 중 실제 문자의 길이('\0'(Null) 크기 제외)
    */

    int str_size = strlen(str) + 1; // 원본 문자열 크기
    char* str_tmp = (char*)calloc(str_size, sizeof(char)); // 복사할 문자열을 임시 저장할 문자열 동적할당
    /*
        calloc 쓴 이유 = > 원본 문자열과 숫자를 제외하고 뒤집은 문자열은 문자열 길이가 차이나므로 빈 공간이 발생하기 때문에
                           그 빈공간을 문자열 종료 문자로 채워주기 위해서.
    */

    // NULL 포인터 체크
    if (str_tmp == NULL)
    {
        PrintMemoryAllocationError();
        return NULL;
    }

    int tmp_idx = 0; // 숫자를 뺀 문자열의 인덱스 번호를 메기는 변수
    for (int i = 0; i < strlen(str); i++)
    {
        char to_copy_check = *(str + strlen(str) - 1 - i); // 문자의 복사 여부를 체크할 변수

        if (to_copy_check < '0' || to_copy_check > '9') // 문자가 숫자가 아니면 ↓↓
        {
            *(str_tmp + tmp_idx) = to_copy_check; // 임시 문자열의 해당 인덱스에 문자를 복사
            tmp_idx++; // 다음 인덱스로 넘어가기
        }
    }

    /*
        임시 문자열을 원본 문자열에 복사하면 문자열 크기는 같지만 문자열 길이가 차이나므로 빈 공간이 발생하여 메모리 공간이 낭비된다.
        따라서 뒤집은 문자열을 알맞은 크기에 저장할 문자열 공간을 새로 동적할당해준다.
    */

    char* str_reversed = (char*)calloc(tmp_idx + 1, sizeof(char));

    // NULL포인터 체크
    if (str_reversed == NULL)
    {
        PrintMemoryAllocationError();
        return NULL;
    }

    // 문자열 복사. (strcpy_s을 사용하면 버퍼 오버런이 발생하므로 사용할 수 없다.)
    for (int i = 0; i < tmp_idx; i++)
    {
        *(str_reversed + i) = *(str_tmp + i);
    }
    // 마지막 1공간은 calloc으로 초기화 해주었으므로 따로 종료문자를 넣어주지 않아도 된다.

    return str_reversed;
}

void Output(const char* str, const char* str_reversed)
{
    printf("원본 문자열: %s\n", str);
    printf("뒤집은 문자열(숫자는 제거됨): %s\n", str_reversed);

    return;
}

void PrintMemoryAllocationError()
{
    fprintf(stderr, "Memory Allocation Failed.\n");
    return;
}