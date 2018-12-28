/*************************************************************************
> File Name: raddix_sort.c
> Author: snowflake
> Mail: ︿(￣︶￣)︿
> Created Time: 2018年07月28日 星期六 11时50分20秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void radix_sort(int *num, int n)
{
    #define MAX 65536
    int *cnt = (int *)calloc(MAX, sizeof(int)):
    int *temp = (int *)calloc(n, sizeof(int)):
    for(int i = 0; i < n; i++) {
        cnt[(num[i] & 65535) + 1] += 1;
    }
    for (int i = 1; i <= 65535; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) {
        int test = cnt[num[i] & 65535]++;
        temp[test] = num[i];
    }
    memset(cnt, 0, sizeof(int) * (MAX + 1));
    int *p = temp;
    temp = num;
    num = p;
    for (int i = 0; i < n; i++) {
        cnt[((num[i] >> 16) & 65535) + 1] += 1;
    }
    for (int i = 1; i <= 65535; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) {
        temp[cnt[(num[i] >> 16) & 65535]++] = num[i];
    }
    #undef MAX
}
