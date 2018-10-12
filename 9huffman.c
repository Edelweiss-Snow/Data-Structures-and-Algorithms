/*************************************************************************
	> File Name: 9huffman.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月16日 星期日 10时25分54秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(a, b) { \
    __typeof(a) temp; \
    temp = a; a = b; b = temp; \
}

typedef struct HFNode {
    char ch;
    int freq;
    struct HFNode *lchild, *rchild;
} HFNode;

HFNode *get_node() {
    HFNode *p = (HFNode *)calloc(sizeof(HFNode), 1);
    p->lchild = p->rchild = NULL;
}

void build(int n, HFNode *arr[]) {
    for (int times = 0; times < n - 1; times++) {
        HFNode *minNode = arr[0];
        int ind = 0;
        for (int i = 1; i < n - times; i++) {
            if (arr[i]->freq >= minNode->freq) continue;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[n - times - 1]);
        minNode = arr[0];
        for (int i = 1; i < n - times - 1; i++) {
            if (arr[i]->freq >= minNode->freq) continue;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[n - times - 2]);
        HFNode *newNode = get_node();
        newNode->lchild = arr[n - times - 2];
        newNode->rchild = arr[n - times - 1];
        newNode->freq = arr[n - times - 2]->freq + arr[n - times - 1]->freq;
        arr[n - times - 2] = newNode;
    }
    return ;
}
void extract(char (*hfnode)[100], char *buffer, HFNode *root, int n) {
    buffer[n] = '\0';
    if (root->lchild == NULL && root->rchild == NULL) {
        strcpy(hfnode[root->ch + 128], buffer);
        return ;
    }
    buffer[n] = '0';
    extract(hfnode, buffer, root->lchild, n + 1);
    buffer[n] = '1';
    extract(hfnode, buffer, root->rchild, n + 1);
    return ;
}

int main() {
    FILE *fp = fopen("./1vector.c", "r");
    char hfnode[256][100] = {0};
    HFNode *arr[256] = {0};
    char buffer[1024] = {0};
    for (int i = 0; i < 256; i++) {
        arr[i] = get_node();
    }
    int freq[256] = {0};
    while (fread(buffer, sizeof(char), 1024, fp) != 0) {
        for (int i = 0; buffer[i]; i++) {
            int ind = buffer[i] + 128;
            freq[buffer[i] + 128]++;
        }
        memset(buffer, 0, 1024);
    }
    fclose(fp);
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] == 0) continue;
        HFNode *newNode = get_node();
        newNode->ch = (char)i;
        newNode->freq = freq[i];
        arr[count++] = newNode;
    }
    //fflush(stdout);
    build(count, arr);
    extract(hfnode, buffer, arr[0], 0);
    for (int i = 0; i < 256; i++) {
        if (hfnode[i][0] == 0) continue;
        printf("%d %s\n", i, hfnode[i]);
    }
    return 0;
}
