/*************************************************************************
	> File Name: 7string-2.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月16日 星期日 16时26分42秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int sunday(const char *text, const char *pattern) {
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int ind[127] = {0};
    for (int i = 0; i < 127; i++) ind[i] = len2 + 1;
    for (int i = 0; pattern[i]; i++) ind[pattern[i]] = len2 - i;
    int i = 0;
    while (i <= len1 - len2) {
        int j = 0;
        while (j < len2 && pattern[j] == text[i + j]) j++;
        if (j == len2) return 1;
        i += ind[text[i + len2]];
    }
    return 0;
}


int main() {
    printf("%d\n", sunday("hello world", "world"));
    return 0;
}
