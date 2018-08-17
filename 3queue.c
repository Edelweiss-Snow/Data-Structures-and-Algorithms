/*************************************************************************
	> File Name: 3queue.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月17日 星期五 16时09分11秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERROR 0
#define OK 1

typedef struct Queue{
    int *data;
    int head, tail, length;
}Queue;

Queue *init(int length) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *) malloc(sizeof(int) * length);
    q->length = length;
    q->head = 0;
    q->tail = -1;
    return q;
}

int push(Queue *q, int element) {
    if (q->tail + 1 >= q->length) {
        return ERROR;
    }
    q->data[++q->tail] = element;
    return OK;
}

int front(Queue *q) {
    return q->data[q->head];
}

int pop(Queue *q) {
    if (q->head > q->tail) return ERROR;
    q->head++;
    return OK;
}

int empty(Queue *q) {
    return q->head > q->tail;
}

void clear(Queue *q) {
    free(q->data);
    free(q);
}

void output(Queue *q) {
    for (int i = q->head; i <= q->tail; i++) {
        if (i != q->head) {
            printf(" ");
        }
        printf("%d", q->data[i]);
    }
    printf("\n");
}

int main() {
    srand(time(0));
    Queue *q = init(100);
    for (int i = 0; i < 10; i++) {
        int x = rand() % 100; 
        push(q, x); 
    }
    output(q);
    for (int i = 0; i < 3; i++) {
        pop(q);
    }
    output(q);
    return 0;
}
