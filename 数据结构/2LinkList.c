/*************************************************************************
	> File Name: LinkList.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月17日 星期五 14时52分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode;

typedef struct LinkList {
    LinkNode *head;
    int len;
} LinkList;

LinkList *init() {
    LinkList *l = (LinkList *)malloc(sizeof(LinkList));
    l->head = NULL;
    l->len = 0;
    return l;
}

LinkNode *newnode(int data) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = data;
    p->next = NULL;
    return p;
}

int insert(LinkList *l, int data, int index) {
    if (index < 0 || index > l->len) return 0;
    LinkNode *ret;
    ret = (LinkNode*)malloc(sizeof(LinkNode));
    ret->next = l->head;
    LinkNode *p = ret;
    while (p && index--) {
        p = p->next;
    }
    if (p == NULL) return 0;
    LinkNode *node = newnode(data);
    node->next = p->next;
    p->next = node;
    l->head = ret->next;
    l->len++;
    return 1;
}

int delete_node(LinkList *l, int index) {
    if (index < 0 || index >= l->len) return 0;
    LinkNode *ret;
    ret = (LinkNode*)malloc(sizeof(LinkNode));
    ret->next = l->head;
    LinkNode *p = ret;
    while (index--) {
        p = p->next;
    }
    LinkNode *del_node = p->next;
    p->next = del_node->next;
    free(del_node);
    l->head = ret->next;
    l->len--;
    return 1;
}

void output1(LinkList *l) {
    LinkNode *p = l->head;
    while (p) {
        printf("%d\n", p->data);
        p = p->next;
    }
    return ;
}

void output(LinkList *l) {
    LinkNode *p = l->head;
    int count = (l->len + 1) / 2;
    while (p && --count) {
        p = p->next;
    }
    printf("%d\n", p->data);
    return ;
}

void clear(LinkList *l) {
    LinkNode *p = l->head;
    while (p) {
        LinkNode *next = p->next;
        free(p);
        p = next;
    }
    return ;
}

int main() {
    LinkList *l = init();
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        insert(l, i + 1, i);
    }
    for (int i = 0; i < m; i++) {
        int index;
        scanf("%d", &index);
        delete_node(l, index - 1);
    }
    output(l);
    clear(l);
    return 0;
}
