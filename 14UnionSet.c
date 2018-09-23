/*************************************************************************
	> File Name: 14UnionSet.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月23日 星期日 12时02分30秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct UnionSet {
    int *data;
    int *size;
    int cnt;
} UnionSet;

UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->data = (int *)malloc(sizeof(int) * n);
    u->size = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        u->data[i] = i;
        u->size[i] = 1;
    }
    u->cnt = n;
    return u;
}

void clear(UnionSet *u) {
    if (u == NULL) return ;
    free(u->data);
    free(u->size);
    free(u);
    return ;
}

int find(UnionSet *u, int n) {
    if (u->data[n] == n) return n;
    return (u->data[n] = find(u, u->data[n]));
}

int merge(UnionSet *u, int a, int b) {
    int father_a = find(u, a);
    int father_b = find(u, b);
    if (father_a == father_b) return 0;
    if (u->size[father_a] > u->size[father_b]) {
        u->data[father_b] = father_a;
        u->size[father_a] += u->size[father_b];
    } else {
        u->data[father_a] = father_b;
        u->size[father_b] += u->size[father_a];
    }
    u->cnt--;
    return 1;
}

int main() {
    srand(time(0));
    UnionSet *u = init(10);
    #define OP_NUM 20
    for (int i = 0; i < OP_NUM; i++) {
        int a = rand() % 10, b = rand() % 10;
        printf("union %d with %d = %d\n", a, b, merge(u, a, b));
        printf("Union Set Cnt = %d\n", u->cnt);
    }
    #undef OP_NUM
    return 0;
}
