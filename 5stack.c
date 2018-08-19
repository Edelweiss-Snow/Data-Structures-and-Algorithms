/*************************************************************************
	> File Name: 5stack.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月17日 星期五 16时23分07秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Stack {
    int *data;
    int top, size;
} Stack;

Stack *init(int len) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * len);
    s->size = len;
    s->top = -1;
    return s;
}

int push(Stack *s, int data) {
    if (s->top + 1 >= s->size) return 0;
    s->data[++s->top] = data;
    return 1;
}

int empty(Stack *s) {
    return s->top == -1;
}

int pop(Stack *s) {
    if (empty(s)) return 0;
    s->top--;
    return 1;
}

int top_stack(Stack *s) {
    return s->data[s->top];
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

void output(Stack *s) {
    printf("{");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("}\n");
    return ;
}

int main() {
    srand(time(0));
    Stack *s = init(100);
    for (int i = 0; i < 20; i++) {
        int value = rand() % 100;
        push(s, value);
    }
    output(s);
    return 0;
}
