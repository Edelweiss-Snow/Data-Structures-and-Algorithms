/*************************************************************************
	> File Name: vector.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月16日 星期四 20时24分14秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DataBase int

typedef struct Vector {
    DataBase *data;
    int len, size;
} Vector;

Vector *init(int);
void clear(Vector *);
int insert(Vector *, int, DataBase);
int delete_value(Vector *, int);
int expand(Vector *);
void output(Vector *);

int main() {
    srand(time(0));
    Vector *v = init(10);
    for (int i = 1; i <= 10; i++) {
        int x = rand() % 100, index = rand() % (i + 2) - 1;
        printf("%d : insert(%d, %d) : ", i, x, index);
        insert(v, index, x);
        output(v);
    }
    printf("\n");
    for (int i = 1; i <= 5; i++) {
        int index = rand() % (v->len + 2) - 1;
        printf("%d : delete_value(%d) = ", i + 1, index);
        delete_value(v, index);
        output(v);
    }
    output(v);
    return 0;
}

Vector *init(int size) {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->data = (DataBase *)malloc(sizeof(DataBase) * size);
    v->size = size;
    v->len = 0;
    return v;
}

void clear(Vector *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
}

int insert(Vector *v, int index, DataBase data) {
    if (v->len >= v->size) {
        if (!expand(v)) return 0;
    }
    if (index < 0 || index > v->len) return 0;
    for (int i = v->len; i > index; i--) {
        v->data[i - 1] = v->data[i];
    }
    v->data[index] = data;
    v->len++;
    return 1;
}

int expand(Vector *v) {
    int new_size = v->size;
    int *data;
    while (new_size) {
        data = (int *)realloc(v->data, sizeof(int) * (v->size + new_size));
        if (data == NULL) {
            new_size >>= 1;
            continue;
        }
        break;
    }
    if (new_size == 0) return 0;
    v->data = data;
    v->size += new_size;
    printf("expand");
    return 1;
}

int delete_value(Vector *v, int ind) {
    if (ind < 0 || ind >= v->len) return 0;
    for (int i = ind + 1; i < v->len; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->len--;
    return 1;
}
void output(Vector *v) {
    if (v == NULL) return ;
    printf("vector:{");
    for (int i = 0; i < v->len; i++) {
        printf("%d ", v->data[i]);
    }
    printf("}\n");
    return ;
}
