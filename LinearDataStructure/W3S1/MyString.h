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

// ���ڿ� ���� �Լ�
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

// String �� �Լ�
int CompareString(const struct String* const self, const char* other)
{
    return strcmp(self->chars, other);
}

// String ���� ��ȯ �Լ�
size_t GetLength(const struct String* const self)
{
    return self->length;
}

// String ��ü ����
struct String* NewString(const char* init_str)
{
    String* str = (String*)malloc(sizeof(String));
    if (str == NULL)
    {
        return NULL;
    }

    (*str).chars = init_str;
    (*str).length = strlen(init_str) + 1;

    // �Լ� ������ ����
    (*str).Copy = CopyString;
    (*str).Compare = CompareString;
    (*str).GetLength = GetLength;

    return str;
}

// String ����ü ����
void DeleteString(String* str)
{
    if (str->chars)
    {
        free(str);
    }
}