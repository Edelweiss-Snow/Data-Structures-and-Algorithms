/*************************************************************************
	> File Name: 7string-shift_and-large.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月16日 星期日 19时18分15秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TEST(func) { \
    printf("%s = %d\n", #func, func); \
}

#define BASE 30

typedef struct BitData {
    int *data;
    int cnt;
} BitData;

BitData *init(int n) {
    BitData *p = (BitData *)malloc(sizeof(BitData));
    p->data = (int *)calloc(sizeof(int), n / BASE + 1);
    p->cnt = n / BASE + 1;
    return p;
}

void clear(BitData *d) {
    if (d == NULL) return ;
    free(d->data);
    free(d);
}

void operator_or(BitData *d, int n) {
    int x = n / BASE;
    int y = n % BASE;
    d->data[x] |= (1 << y);
    return ;
}

void operator_and(BitData *d1, BitData *d2) {
    int len = d1->cnt < d2->cnt ? d1->cnt : d2->cnt;
    for (int i = 0; i < len; i++) {
        d1->data[i] &= d2->data[i];
    }
    for (int i = len; i < d1->cnt; i++) {
        d1->data[i] = 0;
    }
    return ;
}

int operator_get(BitData *d, int n) {
    int x = n / BASE;
    int y = n % BASE;
    return d->data[x] & (1 << y);
}

int operator_left(BitData *d) {
    for (int i = d->cnt - 1; i >= 0; i--) {
        if (i != d->cnt - 1) {
            d->data[i + 1] |= (d->data[i] >> (BASE - 1));
        }
        d->data[i] <<= 1;
    }
    return 0;
}

int shift_and(const char *text, const char *pattern) {
    BitData *d[127] = {0};
    int n = strlen(pattern);
    for (int i = 0; i < 127; i++) {
        d[i] = init(n);
    }
    for (int i = 0; i < n; i++) {
        operator_or(d[pattern[i]], i);
    }
    BitData *p = init(n);
    for (int i = 0; text[i]; i++) {
        operator_left(p);
        operator_or(p, 0);
        operator_and(p, d[text[i]]);
        if (operator_get(p, n - 1)) return 1;
    }
    return 0;
}

int main() {
    srand(time(0));
    char str1[300] = {0}, str2[60];
    for (int i = 0; i < 200; i++) str1[i] = rand() % 26 + 'A';
    for (int i = 0; i < 58; i++) str2[i] = rand() % 26 + 'A';
    TEST(shift_and("hello world", "hello"))
    TEST(shift_and("hello world", "wr"))
    TEST(shift_and(str1, str2))
    strcat(str1, str2);
    TEST(shift_and(str1, str2))
    return 0;
}
