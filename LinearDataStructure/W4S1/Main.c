/*
   List 1 - Sequential List
   List 2 - Linked List - Singly List
                        - Doubly List
                        - Circular List
   Stack - Array, Dynamic Array, Linked List -> Circular Linked List
   Queue - Array, Dynamic Array, Linked List -> Circular Linked List

   Tree  - Stack, Queue
   Graph - Stack, Queue

   ADT   - List에서 제공해주는 함수
*/
// 4주차 1차시
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Sequential List를 구조체로 구현
typedef struct ArrayList
{
    int full_size; // 전체 크기
    int used_size; // 사용된 크기
    int* arr; // 배열 포인터

    bool (*is_full)(struct ArrayList*);
    bool (*is_empty)(struct ArrayList*);
    bool (*is_valid_index)(struct ArrayList*, int);
    void (*print_list)(struct ArrayList*);
    void (*insert_first)(struct ArrayList*, int);
    void (*insert_by_index)(struct ArrayList*, int, int);
    void (*insert_last)(struct ArrayList*, int);
    void (*delete_first)(struct ArrayList*);
    void (*delete_by_index)(struct ArrayList*, int);
    void (*delete_last)(struct ArrayList*);
} ArrayList;

// ArrayList를 포인터로 받아 used_size가 full_size인지 여부 리턴
bool is_full(struct ArrayList* arr_list);

// ArrayList를 포인터로 받아 used_size가 0인지 여부 리턴
bool is_empty(struct ArrayList* arr_list);

// ArrayList에 접근하려는 인덱스가 유효한지 검사
bool is_valid_index(struct ArrayList* arr_list, int idx);

// 배열이 다 차면 출력
void print_arr_is_full();

// 배열이 비었으면 출력
void print_arr_is_empty();

// 접근 인덱스가 유효하지 않으면 출력
void print_invalid_index();

// 추가 성공 메세지 출력
void print_add_suc();

// 삭제 성공 메세지 출력
void print_del_suc();

// 다시 입력하라는 메세지 출력
void print_input_again();

// ArrayList를 포인터로 받아 arr을 출력
void print_list(struct ArrayList* arr_list);

// ArrayList를 포인터로 받아 arr의 첫번째에 insert
void insert_first(struct ArrayList* arr_list, int n);

// ArrayList를 포인터로 받아 arr의 특정 index에 insert
void insert_by_index(struct ArrayList* arr_list, int idx, int n);

// ArrayList를 포인터로 받아 arr의 사용된 배열 끝에 insert
void insert_last(struct ArrayList* arr_list, int n);

// ArrayList를 포인터로 받아 arr의 첫번째 요소 delete
void delete_first(struct ArrayList* arr_list);

// ArrayList를 포인터로 받아 arr의 특정 index의 data를 delete
void delete_by_index(struct ArrayList* arr_list, int idx);

// ArrayList를 포인터로 받아 arr의 사용된 배열 마지막 data를 delete
void delete_last(struct ArrayList* arr_list);

// ArrayList 동적 생성하여 리턴
ArrayList* Create(int full_size);

// ArrayList를 포인터로 받아 메모리 제거
void free_array_list(struct ArrayList* arr_list);

int main(void)
{
    int size_input;

    printf("배열 사이즈 입력: ");
    scanf_s("%d", &size_input);

    ArrayList* array_list = Create(size_input);
    if (array_list == NULL) {
        return 1;
    }

    while (1)
    {
        int input, input_number, input_index, input_plus;
        // 메뉴 입력, 아이템 입력, 인덱스 입력, 추가 입력

        // 메뉴 출력
        printf("\n----------[Menu]----------\n");
        printf("1. 배열에 아이템 추가\n");
        printf("2. 배열에 아이템 제거\n");
        printf("3. 배열 출력\n");
        printf("4. Exit\n");
        printf("입력: ");
        scanf_s("%d%*c", &input);

        switch (input)
        {
        case 1:

            // 배열이 다 찼는지 검사
            if (array_list->is_full(array_list))
            {
                print_arr_is_full();
                break;
            }

            // 세부 메뉴 출력
            printf("    1. insert_first\n");
            printf("    2. insert_by_index\n");
            printf("    3. insert_last\n");
            printf("    4. 뒤로가기\n");
            printf("    입력: ");
            scanf_s("%d%*c", &input);

            switch (input)
            {
            case 1:
                printf("    추가할 인티저 입력: ");
                scanf_s("%d%*c", &input_number);
                insert_first(array_list, input_number);
                break;

            case 2:
                printf("    인덱스 입력: ");
                scanf_s("%d%*c", &input_index);

                // 입력된 인덱스가 유효하지 않으면 에러 출력
                if (!(array_list->is_valid_index(array_list, input_index)))
                {
                    print_invalid_index();
                    break;
                }

                printf("    추가할 인티저 입력: ");
                scanf_s("%d%*c", &input_number);
                insert_by_index(array_list, input_index, input_number);
                break;

            case 3:
                printf("    추가할 인티저 입력: ");
                scanf_s("%d%*c", &input_number);
                insert_last(array_list, input_number);
                break;

            case 4:
                break;

            default:
                print_input_again();
            }

            break;

        case 2:

            // 배열이 비었는지 검사
            if (array_list->is_empty(array_list))
            {
                print_arr_is_empty();
                break;
            }
            else
            {
                printf("    1. delete_first\n");
                printf("    2. delete_by_index\n");
                printf("    3. delete_last\n");
                printf("    4. 뒤로가기\n");
                printf("    입력: ");
                scanf_s("%d%*c", &input);

                switch (input)
                {
                case 1:
                    delete_first(array_list);
                    break;

                case 2:
                    printf("    제거할 인덱스 입력: ");
                    scanf_s("%d%*c", &input_index);

                    // 입력된 인덱스가 유효하지 않으면 에러 출력
                    if (!(array_list->is_valid_index(array_list, input_index)))
                    {
                        print_invalid_index();
                        break;
                    }

                    delete_by_index(array_list, input_index);
                    break;

                case 3:
                    delete_last(array_list);
                    break;

                case 4:
                    break;

                default:
                    print_input_again();
                }
            }

            break;

        case 3:
            print_list(array_list);
            break;

        case 4:
            free_array_list(array_list);
            return 0;

        default:
            printf("다시입력해주세요.\n");
        }
    }

    return 0;
}

// ArrayList를 포인터로 받아 arr을 출력
void print_list(struct ArrayList* arr_list)
{
    if (arr_list == NULL)
    {
        fprintf(stderr, "ERROR: 인자가 NULL이어서 출력할 수 없습니다.\n");
        return;
    }

    printf("----------[ ArrayList Info ]----------\n");
    printf("최대 크기: %d\n", arr_list->full_size);
    printf("사용 크기: %d\n", arr_list->used_size);

    printf("배열: ");
    for (int i = 0; i < arr_list->used_size; i++)
    {
        printf("[%d] ", arr_list->arr[i]);
    }
    printf("\n");
}

// ArrayList를 포인터로 받아 arr의 첫번째에 insert
void insert_first(struct ArrayList* arr_list, int n)
{
    // 사용크기가 0일때는 인덱스 -1에 접근할 수 있으므로 예외처리
    if (arr_list->used_size > 0)
    {
        for (int i = arr_list->used_size; i > 0; i--)
        {
            arr_list->arr[i] = arr_list->arr[i - 1];
        }
    }

    arr_list->arr[0] = n;
    arr_list->used_size++;

    print_add_suc();
    print_list(arr_list);
}

// ArrayList를 포인터로 받아 arr의 특정 index에 insert
void insert_by_index(struct ArrayList* arr_list, int idx, int n)
{

    for (int i = arr_list->used_size; i > idx; i--)
    {
        arr_list->arr[i] = arr_list->arr[i - 1];
    }

    arr_list->arr[idx] = n;
    arr_list->used_size++;

    print_add_suc();
    print_list(arr_list);
}

// ArrayList를 포인터로 받아 arr의 사용된 배열 끝에 insert
void insert_last(struct ArrayList* arr_list, int n)
{
    arr_list->arr[arr_list->used_size] = n;
    arr_list->used_size++;

    print_add_suc();
    print_list(arr_list);
}

// ArrayList를 포인터로 받아 arr의 첫번째 요소 delete
void delete_first(struct ArrayList* arr_list)
{
    for (int i = 0; i < arr_list->used_size - 1; i++)
    {
        arr_list->arr[i] = arr_list->arr[i + 1];
    }

    arr_list->used_size--;

    print_del_suc();
    print_list(arr_list);
}

// ArrayList를 포인터로 받아 arr의 특정 index의 data를 delete
void delete_by_index(struct ArrayList* arr_list, int idx)
{
    for (int i = idx; i < arr_list->used_size - 1; i++)
    {
        arr_list->arr[i] = arr_list->arr[i + 1];
    }
    arr_list->used_size--;

    print_del_suc();
    print_list(arr_list);
}

// ArrayList를 포인터로 받아 arr의 사용된 배열 마지막 data를 delete
void delete_last(struct ArrayList* arr_list)
{
    arr_list->used_size--;
    print_del_suc();
    print_list(arr_list);
}

// ArrayList를 포인터로 받아 used_size가 full_size인지 여부 리턴
bool is_full(struct ArrayList* arr_list)
{
    if (arr_list->full_size == arr_list->used_size)
        return true;

    return false;
}

// ArrayList를 포인터로 받아 used_size가 0인지 여부 리턴
bool is_empty(struct ArrayList* arr_list)
{
    if (arr_list->used_size == 0)
        return true;

    return false;
}

// ArrayList에 접근하려는 인덱스가 유효한지 검사
bool is_valid_index(struct ArrayList* arr_list, int idx)
{
    if (idx >= arr_list->used_size || idx < 0)
        return false;

    return true;
}

// ArrayList 동적 생성하여 리턴
ArrayList* Create(int full_size)
{
    if (full_size <= 0)
    {
        fprintf(stderr, "[DebugLog]: ArrayList의 크기는 0보다 커야합니다.\n");
        return NULL;
    }

    ArrayList* arr_list_created = (ArrayList*)malloc(sizeof(ArrayList));

    if (arr_list_created == NULL)
    {
        fprintf(stderr, "[DebugLog]: ArrayList 메모리 할당 실패!\n");
        return NULL;
    }

    arr_list_created->full_size = full_size;
    arr_list_created->used_size = 0;
    arr_list_created->arr = (int*)malloc(sizeof(int) * full_size);

    if (arr_list_created->arr == NULL)
    {
        fprintf(stderr, "[DebugLog]: arr_list_created->arr 메모리 할당 실패!\n");
        free(arr_list_created);
        return NULL;
    }


    arr_list_created->print_list = print_list;
    arr_list_created->insert_first = insert_first;
    arr_list_created->insert_by_index = insert_by_index;
    arr_list_created->insert_last = insert_last;
    arr_list_created->delete_first = delete_first;
    arr_list_created->delete_by_index = delete_by_index;
    arr_list_created->delete_last = delete_last;
    arr_list_created->is_full = is_full;
    arr_list_created->is_empty = is_empty;
    arr_list_created->is_valid_index = is_valid_index;

    return arr_list_created;
}

// ArrayList를 포인터로 받아 메모리 제거
void free_array_list(struct ArrayList* arr_list)
{
    if (arr_list != NULL)
    {
        printf("ArrayList메모리가 해제됨.");
        free(arr_list->arr);
        free(arr_list);
    }
}

// 배열이 다 차면 출력
void print_arr_is_full()
{
    fprintf(stderr, "ERROR: 배열이 다 찼습니다.\n");
}

// 배열이 비었으면 출력
void print_arr_is_empty()
{
    fprintf(stderr, "ERROR: 배열이 비었습니다.\n");
}

// 접근 인덱스가 유효하지 않으면 출력
void print_invalid_index()
{
    fprintf(stderr, "ERROR: 유효하지 않은 인덱스 입니다.\n");
}

// 추가 성공 메세지 출력
void print_add_suc()
{
    printf("[DebugLog]: 추가 성공!\n");
}

// 삭제 성공 메세지 출력
void print_del_suc()
{
    printf("[DebugLog]: 삭제 성공!\n");
}

// 다시 입력하라는 메세지 출력
void print_input_again()
{
    printf("다시 입력해주세요.\n");
}