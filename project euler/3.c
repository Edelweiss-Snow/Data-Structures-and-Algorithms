/*************************************************************************
	> File Name: 3.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年07月18日 星期三 10时16分05秒
 ************************************************************************/

#include <stdio.h>
#include <inttypes.h>

#define NUM 600851475143

int main() {
    int64_t num = NUM;
    for (int i = 2; i < num; i++) {
        while (num % i == 0) {
            num /= i;
        }
    }
    printf("%"PRId64"\n", num);
    return 0;
}
