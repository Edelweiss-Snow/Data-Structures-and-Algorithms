/*************************************************************************
	> File Name: 7.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年07月22日 星期日 11时28分38秒
 ************************************************************************/

#include<stdio.h>
#define NUM 1000000

int prime[NUM] = {0};

void Prime() {
    for (int i = 2; i <= NUM; i++) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0]; j++) {
            if (i * prime[j] > NUM) break;
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    Prime();
    printf("%d\n", prime[10001]);
    return 0;
}
