/*************************************************************************
	> File Name: binary_search.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年07月28日 星期六 15时29分47秒
 ************************************************************************/

#include <stdio.h>

int binary_search1(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}
//111100000
int binary_search2(int *num, int n, int x) {
    int head = -1, tail = n - 1, mid;//增加虚拟头结点
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}
//000001111
int binary_search3(int *num, int n, int x) {
    int head = 0, tail = n, mid;//增加虚拟尾节点
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return head == n ? -1 : head;
}

int main() {


    return 0;
}
