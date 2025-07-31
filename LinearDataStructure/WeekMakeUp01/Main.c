/*
    TODO
    1. 한 task는 5~15 사이의 랜덤 값을 clock으로 가짐
    2. Single CPU Queue를 가지는데 이 Single CPU Queue는 3 크기 만큼의 Queue이고 1 clock/s 로 task를 처리함
    3. 프로세스가 7초마다 1개씩 1번 조건에 해당하는 task를 생성하여 Single CPU Queue로 Enqueue하고 출력(Queue와 Task정보 및 시간) Singe CPU Queue는 2번 조건에 따라 Task가 가진 clock값에 해당하는 초 시간 이후 Dequeue하고 출력(Queue와 Task정보 및 시간).
    4. 3크기를 가지는 Single CPU Qeueue가 다 차있는데 Task가 생성되면 이 Task는 Loss되어 버리고 이를 출력
    5. Task는 6개까지만 만들고 프로그램 종료

    ADT
    1. Task 구조체(int id, clock, remaining_clock)
    2. Queue 구조체(배열)
    3. bool Enqueue(Queue* q, Task task)
    4. Task* Dequeue(Queue* q)
    5. void PrintQueue(const Queue* q)
    6. void PrintTask(const Task* task)
    7. bool IsFull(Queue* q)
    8. bool IsEmpty(Queue* q)
    9. Queue* CreateQueue(const int size)
    10. Task* CreateTask(const int id, const int clock)
    11. void PrintLoss(Task* task) => 10초가 지나 Task를 생성해서 Enqueue해야 할 때 Queue가 IsFull이면 실행하고 free(task)
*/

// 보강
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

typedef struct Task
{
    int id; // Task ID
    int clock; // 초기 Clock (초)
    int remaining_clock; // 남은Clock (초)
} Task;

typedef struct Queue
{
    Task** tasks; // Task* 배열
    int front, rear; // 원형 큐 인덱스
    int count; // 현재 원소 개수
    int capacity; // 최대 용량
} Queue;

Queue* CreateQueue(const int size);
Task* CreateTask(const int id, const int clock);
bool IsFull(const Queue* q);
bool IsEmpty(const Queue* q);
bool Enqueue(Queue* q, const Task* task_created);
Task* Dequeue(Queue* q);
Task* Peek(const Queue* q);
void PrintQueue(const Queue* q);
void PrintTask(const Task* task_created);
void PrintLoss(const Task* task_created);

main(void)
{
    srand((unsigned)time(NULL));

    // 상수 초기변수
    const int MAX_TASKS = 6; // 총 생성할 Task 수
    const int GAP = 7; // Task 생성 간격(초)
    const int QUEUE_CAPACITY = 3; // 큐 크기

    // 초기변수
    int number_of_tasks = 0; // 지금까지 생성된 Task 수
    int task_id = 1; // Task에 부여할 ID
    int current_time = 0; // 프로세스 시간(초)
    Task* current_task = NULL; // CPU에서 처리 중인 Task

    // SINGLE CPU QUEUE
    Queue* single_cpu = CreateQueue(QUEUE_CAPACITY);

    while (true)
    {
        // 1) 7초마다 1개씩 Task 생성, 최대 6개
        if (number_of_tasks < MAX_TASKS
            && current_time > 0
            && current_time % GAP == 0)
        {
            int clock = rand() % 11 + 5;  // 5~15초 랜덤값 생성
            Task* task_created = CreateTask(task_id++, clock);
            printf("[%2d초 경과] Task 생성! ", current_time);
            PrintTask(task_created);

            if (Enqueue(single_cpu, task_created))
            {
                printf("Enqueue 성공! ");
                PrintQueue(single_cpu);
            }
            else
            {
                printf(" Enqueue 실패! Queue가 FULL\n");
                PrintLoss(task_created);
                free(task_created);
            }

            current_task = Peek(single_cpu);

            number_of_tasks++;
        }

        // 2) CPU 처리
        if (current_task != NULL)
        {
            current_task->remaining_clock--;
            PrintTask(current_task);

            if (current_task->remaining_clock <= 0)
            {
                printf("[%2d초 경과] Task 수행 완료! ", current_time);
                PrintTask(current_task);
                Dequeue(single_cpu);
                free(current_task);
                current_task = Peek(single_cpu);
                PrintQueue(single_cpu);
            }
        }

        // 3) 종료: 6개 생성 완료 & 큐 비어있고 & 처리 중인 Task 없음
        if (number_of_tasks >= MAX_TASKS
            && current_task == NULL
            && IsEmpty(single_cpu))
        {
            printf("총 처리 시간: %d 초\n", current_time);
            break;
        }

        //Sleep(1000);
        current_time++;
    }

    // 메모리 해제
    free(single_cpu->tasks);
    free(single_cpu);
}

// Queue 생성 후 반환
Queue* CreateQueue(const int size)
{
    Queue* q = malloc(sizeof(Queue));
    if (q == NULL)
        return;

    q->tasks = malloc(sizeof(Task*) * size);

    if (q->tasks == NULL)
        return;

    q->capacity = size;
    q->front = 0;
    q->rear = 0;
    q->count = 0;

    return q;
}

// Task 생성 후 반환
Task* CreateTask(const int id, const int clock)
{
    Task* task_created = malloc(sizeof(Task));

    if (task_created == NULL)
        return;

    task_created->id = id;
    task_created->clock = clock;
    task_created->remaining_clock = clock;

    return task_created;
}

// Queue가 Full인지 true||false
bool IsFull(const Queue* q)
{
    return q->count == q->capacity;
}

// Queue가 비었는지 true||false
bool IsEmpty(const Queue* q)
{
    return q->count == 0;
}

// Enqueue : 성공(true)||실패(false)
bool Enqueue(Queue* q, const Task* task_created)
{
    if (IsFull(q))
        return false;

    q->tasks[q->rear] = task_created;
    q->rear = (q->rear + 1) % q->capacity;
    q->count++;

    return true;
}

// Dequeue : Task반환
Task* Dequeue(Queue* q)
{
    if (IsEmpty(q))
        return NULL;

    Task* task_created = q->tasks[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->count--;

    return task_created;
}

// Peek 함수
Task* Peek(const Queue* q)
{
    if (IsEmpty(q))
        return NULL;

    return q->tasks[q->front];
}

// Task 정보 출력
void PrintTask(const Task* task)
{
    printf("Task: [ID: %2d | 처리시간 = %2d | 남은시간 = %2d]\n",
        task->id, task->clock, task->remaining_clock);
}

// Queue 정보 출력
void PrintQueue(const Queue* q)
{
    printf("=== Queue 상태 (%d/%d): ", q->count, q->capacity);

    if (IsEmpty(q))
    {
        printf("Queue가 비었음!\n");
        return;
    }

    // front에서 count만큼 순회
    for (int i = 0; i < q->count; i++)
    {
        int idx = (q->front + i) % q->capacity;
        Task* task = q->tasks[idx];
        printf("[Task ID:%2d | 처리시간 = %2d | 남은시간 = %2d] ", task->id, task->clock, task->remaining_clock);
    }
    printf("===\n");
}

// Loss된 Task 정보 출력
void PrintLoss(const Task* task)
{
    printf("Task 손실! [Task ID: %2d | clock = %2d]\n", task->id, task->clock);
}
