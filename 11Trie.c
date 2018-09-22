/*************************************************************************
	> File Name: 10Trie.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月22日 星期六 18时40分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BASE 26
#define BASE_LETTER 'a'

typedef struct Node {
    int flag;
    struct Node *next[BASE];
}Node, *Trie;

Node *get_new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

void clear(Trie root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        clear(root->next[i]);
    }
    free(root);
    return ;
}

Node *insert(Trie root, const char *str) {
    if (root == NULL) root = get_new_node();
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BASE_LETTER;
        if (p->next[ind] == NULL) p->next[ind] = get_new_node();
        p = p->next[ind];
    }
    p->flag = 1;
    return root;
}

int search(Trie root, const char *str) {
    Node *p = root;
    int i = 0;
    while (p && str[i]) {
        int ind = str[i] - BASE_LETTER;
        p = p->next[ind];
    }
    return (p && p->flag);
}

char *get_random_string(char *str) {
    int len = rand() % 10 + 1;
    for (int i = 0; i < len; i++) {
        str[i] = rand() % BASE + BASE_LETTER;
    }
    str[len] = 0;
    return str;
}

void output(Trie root, char *str, int level) {
    if (root == NULL) return ;
    str[level] = 0;
    if (root->flag) {
        printf("find word : %s\n", str);
    }
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        str[level] = i + BASE_LETTER;
        output(root->next[i], str, level + 1);
    }
    return ;
}

int main() {
    srand(time(0));
    Trie root = NULL;
    char str[50] = {0};
    for (int i = 0; i < 20; i++) {
        get_random_string(str);
        root = insert(root, str);
        printf("insert: %s\n", str);
    }
    output(root, str, 0);
    return 0;
}
