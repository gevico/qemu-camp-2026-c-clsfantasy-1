#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

static void enqueue(Queue *q, People person)
{
    q->data[q->tail] = person;
    q->tail = (q->tail + 1) % MAX_PEOPLE;
    q->count++;
}

static People dequeue(Queue *q)
{
    People person = q->data[q->head];
    q->head = (q->head + 1) % MAX_PEOPLE;
    q->count--;
    return person;
}

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    q.head = 0;
    q.tail = 0;
    q.count = 0;

    for (int i = 1; i <= total_people; i++) {
        People person = {i};
        enqueue(&q, person);
    }

    while (q.count > 1) {
        for (int i = 1; i < report_interval; i++) {
            enqueue(&q, dequeue(&q));
        }

        People eliminated = dequeue(&q);
        printf("淘汰: %d\n", eliminated.id);
    }
    
    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}