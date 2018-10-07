/*************************************************************************
	> File Name: 16AVL.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年10月07日 星期日 16时23分24秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b) ({ \
    __typeof(a) _a = (a); \
    __typeof(b) _b = (b); \
    _a > _b ? _a : _b; \
})

typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
} Node;

Node *NIL;

__attribute__((constructor))
void init_nil() {
    NIL = (Node *)malloc(sizeof(Node));
    NIL->h = 0;
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
}

Node *get_node(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->lchild = p->rchild = NIL;
    p->key = key;
    p->h = 1;
    return p;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;
    temp->h = MAX(temp->lchild->h, temp->rchild->h) + 1;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;
    temp->h = MAX(temp->lchild->h, temp->rchild->h) + 1;
    return temp;
}

Node *maintain(Node *root) {
    if (abs(root->lchild->h - root->rchild->h) < 2) return root;
    if (root->lchild->h > root->rchild->h) {
        if (root->lchild->rchild->h > root->lchild->lchild->h) {
            root->lchild = left_rotate(root);
        }
        root = right_rotate(root);
    } else {
        if (root->rchild->lchild->h > root->rchild->rchild->h) {
            root->rchild = right_rotate(root);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return get_node(key);
    if (root->key == key) return root;
    if (root->key > key) {
        root->lchild = insert(root->lchild, key);
    } else {
        root->rchild = insert(root->rchild, key);
    }
    root->h = MAX(root->lchild->h, root->rchild->h) + 1;
    return maintain(root);
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d, %d, %d)\n", root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    srand(time(0));
    /*Node *root = NIL;
    for (int i = 1; i <= 5; i++) {
        root = insert(root, i);
        output(root);
        printf("-------------\n");
    }
    clear(root);*/
    Node *root = NIL;
    int a[10] = {5, 6, 1, 2, 3, 8, 9, 4, 7}; 
    for (int i = 0; i < 10; i++) {
        root = insert(root, a[i]);
        output(root);
        printf("------------\n");
    }
    clear(root);
    return 0;
}
