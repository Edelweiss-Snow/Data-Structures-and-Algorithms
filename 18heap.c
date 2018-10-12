/*************************************************************************
	> File Name: 18heap.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月23日 星期一 17时20分10秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define swap(a, b) { \
    __typeof(a) temp; \
    temp = a; a = b; b = temp; \
}

typedef struct Heap {
    int *data;
    int n, size;
} Heap;

Heap *init(int); 
void push(Heap *, int);
void pop(Heap *);
void clear(Heap *);

void output(Heap *h) {
    if (h == NULL);
    printf("[");
    for (int i = 0; i < h->size; i++) {
        printf("%d, ", h->data[i]);
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    Heap *h = init(26);
    int num[25] = {0};
    for (int i = 0; i < 25; i++) {
        num[i] = rand() % 100;
        push(h, num[i]);
    }
    output(h);
    int c = 25;
    while (c--) {
        pop(h);
    }
    output(h);
    return 0;
}

Heap *init(int n) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (int *)malloc(sizeof(int) * n);
    memset(h->data, 0, sizeof(int) * n);
    h->n = 0;
    h->size = n;
    return h;
}

void push(Heap *h, int value) {
    if (h->n >= h->size) return ;
    h->n += 1;
    h->data[h->n] = value;
    int ind = h->n;
    while (ind > 1) {
        if (h->data[ind] <= h->data[ind >> 1]) break;
        swap(h->data[ind], h->data[ind >> 1]);
        ind >>= 1;
    }
    return ;
}

void pop(Heap *h) {
    if (h->n <= 1) {
        h->n = 0;
        return ;
    }
    swap(h->data[h->n], h->data[1]);
    h->n -= 1;
    int ind = 1;
    while (ind << 1 <= h->n) {
        int swap_ind = ind;
        if (h->data[swap_ind] < h->data[ind << 1]) 
            swap_ind = ind << 1;
        if ((ind << 1 | 1) <= h->n && h->data[swap_ind] < h->data[ind << 1 | 1]) 
            swap_ind = (ind << 1 | 1);
        if (swap_ind == ind) break;
        swap(h->data[ind], h->data[swap_ind]);
        ind <<= 1;
    }
    return ;
}

void clear(Heap *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
}

void build(int *num, int n) {
    int ind = n >> 1;
    for (int i = ind; i >= 1; --i) {
        int ind = i;
        while (ind * 2 <= n) {
            int max_ind = ind;
            if (num[i * 2] > num[max_ind]) max_ind = i * 2;
            if (i * 2 + 1 <= n && num[i * 2 + 1] > num[max_ind]) max_ind = i * 2 + 1;
            if (ind == max_ind) break;
            swap(num[ind], num[max_ind]);
            ind = max_ind;
        }
    }
    return ;
}
