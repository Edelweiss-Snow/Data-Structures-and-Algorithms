/*************************************************************************
	> File Name: string.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月14日 星期五 11时09分13秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int BF(const char *text, const char *pattern) {
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    for (int i = 0; i < len1 - len2 + 1; i++) {
        int flag = 1;
        for (int j = i; pattern[j] && flag; j++) {
            if (pattern[j] == text[i + j]) continue;
            flag = 0;
        }
        if (flag) return 1;
    }
    return 0;
}

int KMP(const char *text, const char *pattern) {
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int *next = (int *)malloc(sizeof(int) * len2);
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < len2; i++) {
        while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) j += 1;
        next[i] = j;
    }
    j = -1;
    for (int i = 0; i < len1; i++) {
        while (j != -1 && pattern[j + 1] != text[i]) j = next[j];
        if (pattern[j + 1] == text[i]) j += 1;
        if (pattern[j + 1] == 0) return 1;
    }
    return 0;
}

int main() {
    printf("%d\n", BF("112345", "3456"));
    printf("%d\n", KMP("1123645", "364"));
    return 0;
}
