/*
    Condition
    1. CPU는 1시간동안 작업을 처리한다.

    2. 15초마다 아래의 작업중 1개를 입력으로 받는다.

        => 총 240개 생성

    3. 임의로 3가지의 작업중 하나가 입력된다. 각 작업의 처리속도는 아래와 같다.

        3-1. A작업 12초

        3-2. B작업 15초

        3-3. C작업 24초

    4. CPU에서 끝까지 일을 처리하면 success, 실패하면 fail을 출력한다.

        (success : A, B, C 작업의 drop이 없음, fail : 한번이라도 A, B, C 작업을 drop함)

    Prototype
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
    11. void PrintLoss(Task* task) => Task를 생성해서 Enqueue해야 할 때 Queue가 IsFull이면 실행하고 free(task)
*/

// 보강
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

typedef enum ETaskType { A, B, C, } ETaskType;

typedef struct Task
{
    int id; // Task ID
    ETaskType type; // Task Type
    int clock; // 초기 Clock (초)
    int remaining_clock; // 남은 Clock (초)
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
Task* CreateTaskByType(const int id, const ETaskType type);
bool IsFull(const Queue* q);
bool IsEmpty(const Queue* q);
bool Enqueue(Queue* q, const Task* task_created);
Task* Dequeue(Queue* q);
Task* Peek(const Queue* q);
void PrintQueue(const Queue* q);
void PrintTask(const Task* task_created);
void PrintLoss(const Task* task_created);
void PrintResult(const int current_time, const int number_of_tasks, const int number_of_tasks_failure);

main(void)
{
    srand((unsigned)time(NULL));

    // 상수 초기변수
    const int MAX_TASKS = 240; // 총 생성할 Task 수
    const int GAP = 15; // Task 입력 간격(초)
    const int MAX_QUEUE_TEST_VALUE = 30; // 테스트할 큐 용량 한계치
    const int TRY_TIME = 1000; // 테스트 시행횟수

    int QUEUE_CAPACITY = 4; // 첫번째로 테스트할 큐 크기 설정

    while (QUEUE_CAPACITY != MAX_QUEUE_TEST_VALUE + 1)
    {
        double* arr_success_rate = (double*)malloc(sizeof(double) * TRY_TIME);

        if (arr_success_rate == NULL)
            return;

        for (int i = 0; i < TRY_TIME; i++)
        {
            // 초기변수
            int number_of_tasks = 0; // 지금까지 생성된 Task 수
            int number_of_tasks_loss = 0; // 생성된 Task 중 Loss된 Task 수
            int task_id = 1; // Task에 부여할 ID
            int current_time = 0; // 프로세스 시간(초)
            Task* current_task = NULL; // CPU에서 처리 중인 Task
            bool is_success = true; // 성공했나? 조건: 단 한번의 loss도 없음
            bool should_continue = true; // CPU에서 TASK처리 완료시 false

            // SINGLE CPU QUEUE
            Queue* single_cpu = CreateQueue(QUEUE_CAPACITY);

            while (should_continue)
            {
                // 1) 15초마다 1개씩 Task 생성, 최대 240개
                if (number_of_tasks < MAX_TASKS
                    && current_time > 0
                    && current_time % GAP == 0)
                {
                    ETaskType task_type = rand() % 3;  // 0~3 랜덤값 생성
                    Task* task_created = CreateTaskByType(task_id++, task_type);
                    //printf("[%2d초 경과] Task 생성! ", current_time);
                    //PrintTask(task_created);

                    if (Enqueue(single_cpu, task_created))
                    {
                        //printf("Enqueue 성공! ");
                        //PrintQueue(single_cpu);
                    }
                    else
                    {
                        //printf("Enqueue 실패! Queue가 FULL\n");
                        //PrintLoss(task_created);
                        free(task_created);

                        is_success = false;
                        number_of_tasks_loss++;
                    }
                    //putchar('\n');

                    current_task = Peek(single_cpu);

                    number_of_tasks++;
                }

                // 2) CPU 처리
                if (current_task != NULL)
                {
                    current_task->remaining_clock--;
                    //PrintTask(current_task);

                    if (current_task->remaining_clock <= 0)
                    {
                        //printf("[%2d초 경과] Task 수행 완료! ", current_time);
                        //PrintTask(current_task);
                        Dequeue(single_cpu);
                        free(current_task);
                        current_task = Peek(single_cpu);
                        //PrintQueue(single_cpu);
                        //putchar('\n');
                    }
                }

                // 3) 종료: 240개 생성 완료 & 처리 중인 Task 없음 & 큐 비어있고
                if (number_of_tasks >= MAX_TASKS
                    && current_task == NULL
                    && IsEmpty(single_cpu))
                {
                    //PrintResult(current_time, number_of_tasks, number_of_tasks_loss);
                    should_continue = false;
                    //break;
                }

                //Sleep(1000);
                current_time++;
            }

            double success_rate = (((double)(number_of_tasks - number_of_tasks_loss) / (double)(number_of_tasks)) * 100.0);
            arr_success_rate[i] = success_rate;

            // 메모리 해제
            free(single_cpu->tasks);
            free(single_cpu);

            //i++;
        }

        double rate_sum = 0.0;

        for (int i = 0; i < TRY_TIME; i++)
        {
            rate_sum += arr_success_rate[i];
        }

        double rate_avg = rate_sum / TRY_TIME;

        double min_success_rate = arr_success_rate[0];

        for (int i = 0; i < TRY_TIME; i++)
        {
            if (min_success_rate > arr_success_rate[i])
            {
                min_success_rate = arr_success_rate[i];
            }
        }

        printf("=== 시뮬레이션 결과 ===\n");
        printf("큐    크 기: %d\n", QUEUE_CAPACITY);
        printf("시 행 횟 수: %d회\n", TRY_TIME);
        printf("최소 성공률: %.2f%%\n", min_success_rate);
        printf("평균 성공률: %.2f%%\n", rate_avg);
        putchar('\n');

        double* pDelete = arr_success_rate;
        arr_success_rate = malloc(sizeof(double) * TRY_TIME);

        if (arr_success_rate == NULL)
            return;

        free(pDelete);

        QUEUE_CAPACITY++;
    }
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

Task* CreateTaskByType(const int id, const ETaskType task_type)
{
    Task* task = malloc(sizeof(Task));
    if (task == NULL)
    {
        // 메모리 할당 실패
        return NULL;
    }

    task->id = id;
    task->type = task_type;

    switch (task_type)
    {
    case A:
        task->clock = 12;
        break;
    case B:
        task->clock = 15;
        break;
    case C:
        task->clock = 24;
        break;
    default:
        // 정의되지 않은 type이 넘어온 경우
        free(task);
        return NULL;
    }

    // 초기 clock 값을 remaining_clock에도 복사
    task->remaining_clock = task->clock;
    return task;
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
    printf("Task: [ID: %2d | 유형: %d | 처리시간 = %2d | 남은시간 = %2d]\n",
        task->id, task->type, task->clock, task->remaining_clock);
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
        printf("[Task ID:%2d | 처리시간 = %2d | 남은시간 = %2d] ",
            task->id, task->clock, task->remaining_clock);
    }
    printf("===\n");
}

// Loss된 Task 정보 출력
void PrintLoss(const Task* task)
{
    printf("Task 손실! [Task ID: %2d | clock = %2d]\n", task->id, task->clock);
}

// 한 번의 시행 결과 출력
void PrintResult(const int current_time, const int number_of_tasks, const int number_of_tasks_loss)
{
    double success_rate = (((double)(number_of_tasks - number_of_tasks_loss) / number_of_tasks) * 100.f);

    printf("===== RESULT =====\n");
    printf("총 처리시간: %d 초\n", current_time);
    printf("작업 생성수: %d 개\n", number_of_tasks);
    printf("작업 손실수: %d 개\n", number_of_tasks_loss);
    printf("작업 성공률: %.1f %\n", success_rate);
}
