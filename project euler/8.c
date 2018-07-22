/*************************************************************************
	> File Name: 8.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年07月22日 星期日 11时48分50秒
 ************************************************************************/

#include <stdio.h>
#include <inttypes.h>
#include "8.h"

int main() {
    int zero = 0;
    int64_t ans = 1, max = 0;
    for (int i = 0; i < 1000; i++) {
        if (a[i] != '0') {
            ans *= a[i] - '0';
        } else {
            ++zero;
        }
        if (i >= 13) {
            if (a[i - 13] != '0') {
                ans /= a[i - 13] - '0';
            } else {
                --zero;
            }
        }
        if (zero == 0 && ans > max) max = ans;
    }
    printf("%"PRId64"\n", max);
    return 0;
}
