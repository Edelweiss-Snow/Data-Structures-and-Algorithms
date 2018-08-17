/*************************************************************************
	> File Name: 3queue.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月17日 星期五 15时10分01秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int size;
    int count;
    int head, tail;
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(Queue) * n);
    q->head = 0;
    q->tail = -1;
    q->count = 0;
    q->size = n;
    return q;
}

int push(Queue *q, int data) {
    if (q->count >= q->size) return 0;
    q->tail = (q->tail + 1) % q->size;
    q->data[q->tail] = data;
    q->count++;
    return 1;
}

int empty(Queue *q) {
    return q->count == 0;
}

int pop(Queue *q) {
    if (q->count <= 0) return 0;
    q->head = (q->head + 1) % q->size;
    q->count--;
    return 1;
}

int front(Queue *q) {
    return q->data[q->head];
}

void clear(Queue *q) {
    free(q->data);
    free(q);
    return ;
}

void output(Queue *q) {
    printf("queue:[");
    for (int i = 0, h = q->head; i < q->count; i++, h = (h + 1) % q->size) {
        printf("%d ", q->data[h]);
    }
    printf("]");
    return ;
}

int main() {
    srand(time(0));
    Queue *q = init(20);
    for (int i = 0; i < 20; i++) {
        push(q, i); 
    }
    output(q);
    for (int i = 0; i < 5; i++) {
        pop(q);
    }
    output(q);
    for (int i = 0; i < 4; i++) {
        push(q, i);
    }
    output(q);
    return 0;
}
