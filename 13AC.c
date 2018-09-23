/*************************************************************************
	> File Name: 13AC.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月22日 星期六 21时58分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BASE 26
#define BL 'a'

typedef struct Node {
    char *str;
    int flag;
    struct Node *fail;
    struct Node *next[BASE];
} Node;

Node *get_new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

void clear(Node *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        clear(root->next[i]);
    }
    if (root->flag == 1) free(root->str);
    free(root);
    return ;
}

Node *insert(Node *root, const char *str) {
    if (root == NULL) root = get_new_node();
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BL;
        if (p->next[ind] == NULL) p->next[ind] = get_new_node();
        p = p->next[ind];
    }
    p->flag = 1;
    p->str = strdup(str);
    return root;
}

void build(Node *root) {
    if (root == NULL) return ;
    Node **queue = (Node **)malloc(sizeof(Node *) * 10000);
    int head = 0, tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        Node *node = queue[head++];
        for (int i = 0; i < BASE; i++) {
            if (node->next[i] == NULL) continue;
            Node *p = node->fail;
            while (p && p->next[i] == NULL) p = p->fail;
            if (p == NULL) node->next[i]->fail = root;
            else node->next[i]->fail = p->next[i];
            queue[tail++] = node->next[i];
        }
    }
    free(queue);
    return ;
}

void search(Node *root, const char *text) {
    if (root == NULL) return ;
    Node *p = root;
    for (int i = 0; text[i]; i++) {
        while (p && p->next[text[i] - BL] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else p = p->next[text[i] - BL];
        Node *q = p;
        while (q) {
            if (q->flag == 1) printf("find string:%s\n", q->str);
            q = q->fail;
        }
    }
    return ;
}

int main() {
    Node *root = NULL;
    root = insert(root, "she");
    root = insert(root, "say");
    root = insert(root, "shr");
    root = insert(root, "he");
    root = insert(root, "her");
    build(root);
    search(root, "sasherhs");
    clear(root);
    return 0;
}
