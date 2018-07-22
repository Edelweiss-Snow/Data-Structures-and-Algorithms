/*************************************************************************
	> File Name: 6.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年07月22日 星期日 11时26分00秒
 ************************************************************************/

#include <stdio.h>

int main() {
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i <= 100; i++) {
        sum1 += i * i;
        sum2 += i;
    }
    printf("%d\n", sum2 * sum2 - sum1);
    return 0;
}
