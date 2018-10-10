/*************************************************************************
	> File Name: 17SBTree.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年10月10日 星期三 11时42分38秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ({ \
	__typeof(a) __a = (a); \
    __typeof(b) __b = (b); \
    (__a) > (__b) ? (__a) : (__b); \
})

typedef struct SBTNode {
    int key, size;
    struct SBTNode *lchild, *rchild;
} SBTNode;

SBTNode *NIL;

__attribute__((constructor))
void init_nil() {
    NIL = (SBTNode *)malloc(sizeof(SBTNode));
    NIL->lchild = NIL->rchild = NIL;
    NIL->size = 0;
    NIL->key = 0;
}

SBTNode *get_node(int data) {
    SBTNode *p = (SBTNode*)malloc(sizeof(SBTNode));
    p->key = data;
    p->lchild = p->rchild = NIL;
    p->size = 1;
    return p;
}

SBTNode *left_rotate(SBTNode *root) {
    SBTNode *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    root->size = root->lchild->size + root->rchild->size + 1;
    temp->size = temp->lchild->size + temp->rchild->size + 1;
    return temp;
}

SBTNode *right_rotate(SBTNode *root) {
    SBTNode *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    root->size = root->lchild->size + root->rchild->size + 1;
    temp->size = temp->lchild->size + temp->rchild->size + 1;
    return temp;
}

SBTNode *maintain(SBTNode *root) {
    if (root->rchild->size > MAX(root->lchild->lchild->size, root->lchild->rchild->size)
       && root->lchild->size > MAX(root->rchild->rchild->size, root->rchild->lchild->size)) {
        return root;
    }
    if (root->rchild->size < root->lchild->size) {
        if (root->rchild->size < root->lchild->rchild->size) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (root->lchild->size < root->rchild->lchild->size) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

SBTNode *precessor(SBTNode *root) {
    SBTNode *temp = root->lchild;
    while (temp != NIL && temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

SBTNode *insert(SBTNode *root, int data) {
    if (root == NIL) root = get_node(data);
    if (root->key == data) return root;
    if (root->key > data) root->lchild = insert(root->lchild, data);
    else root->rchild = insert(root->rchild, data);
    root->size = root->lchild->size + root->rchild->size + 1;
    return maintain(root);
}

SBTNode *delete_node(SBTNode *root, int data) {
    if (root == NIL) return root;
    if (root->key == data) {
        if (root->lchild == NIL && root->rchild == NIL) {
            free(root);
            return NIL;
        } else if (root->lchild == NIL || root->rchild == NIL) {
            SBTNode *temp = (root->lchild != NIL) ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            SBTNode *temp = precessor(root);
        	temp->size ^= root->size; root->size ^= temp->size; temp->size ^= root->size;
            temp->key ^= root->key; root->key ^= temp->key; temp->key ^= root->key;
        	root->lchild = delete_node(root->lchild, data);
        }
    } else {
        if (root->key > data) {
            root->lchild = delete_node(root->lchild, data);
        } else {
            root->rchild = delete_node(root->rchild, data);
        }
    }
    root->size = root->lchild->size + root->rchild->size + 1;
    return root;
}

void output(SBTNode *root) {
    if (root == NIL) return ;
    printf("%d\n", root->key);
    output(root->lchild);
    output(root->rchild);
}

int select(SBTNode *node, int k) {
    int rank = node->rchild->size + 1;
    if (rank == k) {
        return node->key;
    } else if (k < rank) {
        return select(node->rchild, k);
    } else {
        return select(node->lchild, k - rank);
    }
}

int main() {
    SBTNode *root = NIL;
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        root = insert(root, x);
    }
    for (int i = 0; i < n; i++) {
        char input[10] = {0};
        int k;
        scanf("%s", input);
        scanf("%d", &k);
        switch (input[0]) {
            case 'q': {
                printf("%d\n", select(root, k));
            } break;
            case 'i': {
                root = insert(root, k);
            } break;
            case 'd': {
                root = delete_node(root, k);
            } break;
        }
    }
    return 0;
}
