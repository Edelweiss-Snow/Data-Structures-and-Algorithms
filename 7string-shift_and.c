/*************************************************************************
	> File Name: 7string-shift_and.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月16日 星期日 16时52分45秒
 ************************************************************************/

#include <stdio.h>

int shift_and(const char *text, const char *pattern) {
    int n = 0;
    int d[127] = {0};
    while (pattern[n]) {
        d[pattern[n]] |= 1 << n;
        n++;
    }
    int p = 0;
    for (int i = 0; text[i]; i++) {
        p = (p << 1 | 1) & d[text[i]];
        if (p & (1 << (n - 1))) return 1;
    }
    return 0;
}

int main() {
    printf("%d\n", shift_and("hello world", "world"));
    return 0;
}
