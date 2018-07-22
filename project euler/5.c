/*************************************************************************
	> File Name: 5.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年07月22日 星期日 11时17分27秒
 ************************************************************************/

#include <stdio.h>
#include <inttypes.h>

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    return (a % b) == 0 ? b : gcd(b, a % b);
}

int main() {
    int64_t ans = 1;
    for (int i = 11; i <= 20; i++) {
        ans = (ans * i) / (gcd(ans, i));
    }
    printf("%"PRId64"\n", ans);
    return 0;
}
