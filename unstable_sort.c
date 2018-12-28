/*************************************************************************
	> File Name: unstable_sort.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年07月28日 星期六 09时52分52秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a, b) { \
    __typeof(a) temp; \
    temp = a, a = b; b = temp; \
}

void select_sort(int *, int); 
void quick_sort1(int *, int, int);
void quick_sort2(int *, int, int);
void quick_sort(int *, int, int);
void output(int *, int);
void ungarded_insert_sort(int *, int);

int num[200000] = {0};
int main() {
    srand(time(0));
    for (int i = 0; i < 100000; i++) {
        num[i] = rand() % 1000000;
    }
    //output(num, 10000);
    quick_sort(num, 0, 100000);
    output(num, 100000);
    return 0;
}

void output(int *num, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
    return ;
}

void select_sort(int *num, int n) {
    for (int i = 0; i < n - 1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {
            if (num[j] < num[ind]) ind = j;
        }
        swap(num[i], num[ind]);
    }
    return ;
}

void quick_sort1(int *num, int l, int r) {
    if (r - l < 1) return ;
    int x = l, y = r, z = num[l];
    while (x < y) {
        while (x < y && num[y] >= z) --y;
        if (x < y) num[x++] = num[y];
        while (x < y && num[x] <= z) ++x;
        if (x < y) num[y--] = num[x];
    }
    num[x] = z;
    quick_sort1(num, l, x - 1);
    quick_sort1(num, x + 1, r);
}

void quick_sort2(int *num, int l, int r) {
    while (r - l >= 1) {    
        int x = l, y = r, z = (rand() % (r - l + 1)) + l;
        swap(num[z], num[l]);
        z = num[l];
        while (x < y) {
            while (x < y && num[y] >= z) --y;
            if (x < y) num[x++] = num[y];
            while (x < y && num[x] <= z) ++x;
            if (x < y) num[y--] = num[x];
        }
        num[x] = z;
        quick_sort2(num, l, x - 1);
        l = x + 1;
    }
    return ;
}

void quick_sort(int *num, int l, int r) {
    while (r - l >= 1) {
        int x = l, y = r, z = num[rand() % (r - l + 1) + l];
        while (x <= y) {
            while (num[y] > z) --y;
            while (num[x] < z) ++x;
            if (x <= y) {
                swap(num[x], num[y]);
                ++x, --y;
            }
        }
        //printf("%d %d\n", x, y);
        //fflush(stdout);
        quick_sort(num, l, y);
        l = x;
    }
    ungarded_insert_sort(num + l, r - l + 1);
    return ;
}

void ungarded_insert_sort(int *num, int n) {
    int ind = 0;
    for (int i = 1; i < n; i++) {
        if (num[ind] > num[i]) ind = i; 
    }
    swap(num[ind], num[0]);
    for (int i = 2; i < n; i++) {
        int j = i;
        while (num[j] < num[j - 1]) {
            swap(num[j], num[j - 1]);
            j--;
        }
    }
}
