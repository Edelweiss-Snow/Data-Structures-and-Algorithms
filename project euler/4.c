/*************************************************************************
	> File Name: 4.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年07月22日 星期日 11时05分17秒
 ************************************************************************/

#include<stdio.h>

int palindrome(int n) {
    int x = n;
    int num = 0;
    while (x) {
        num = num * 10 + x % 10;
        x /= 10;
    }
    return num == n;
}

int main() {
    int max = 0;
    for (int i = 100; i <= 999; i++) {
        for (int j = i; j <= 999; j++) {
            if (palindrome(i * j) && (max < i * j)) {
                max = i * j;
            }
        }
    }
    printf("%d\n", max);
    return 0;
}
