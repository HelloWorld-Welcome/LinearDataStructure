#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
    char* chars;
    size_t length;

    void (*Copy)(struct String*, const char*);
    int  (*Compare)(struct String*, const char*);
    size_t(*GetLength)(struct String*);
} String;

// 문자열 복사 함수
void CopyString(struct String* self, const char* new_str)
{
    self->length = strlen(new_str) + 1;
    self->chars = (char*)malloc(self->length);
    if (self->chars == NULL)
    {
        return;
    }
    strcpy_s(self->chars, self->GetLength(self), new_str);
}

// String 비교 함수
int CompareString(const struct String* const self, const char* other)
{
    return strcmp(self->chars, other);
}

// String 길이 반환 함수
size_t GetLength(const struct String* const self)
{
    return self->length;
}

// String 객체 생성
struct String* NewString(const char* init_str)
{
    String* str = (String*)malloc(sizeof(String));
    if (str == NULL)
    {
        return NULL;
    }

    (*str).chars = init_str;
    (*str).length = strlen(init_str) + 1;

    // 함수 포인터 설정
    (*str).Copy = CopyString;
    (*str).Compare = CompareString;
    (*str).GetLength = GetLength;

    return str;
}

// String 구조체 해제
void DeleteString(String* str)
{
    if (str->chars)
    {
        free(str);
    }
}