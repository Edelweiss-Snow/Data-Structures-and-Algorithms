/*************************************************************************
	> File Name: 15BST.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月23日 星期日 15时23分53秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BSTNode {
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode;

BSTNode *get_new_node(int key) {
    BSTNode *p = (BSTNode *)malloc(sizeof(BSTNode));
    p->lchild = p->rchild = NULL;
    p->key = key;
    return p;
}

BSTNode *insert(BSTNode *root, int key) {
    if (root == NULL) return get_new_node(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

BSTNode *precursor(BSTNode *node) {
    BSTNode *p = node->lchild;
    while (p->rchild) p = p->rchild;
    return p;
}

BSTNode *delete_node(BSTNode *root, int key) {
    if (root == NULL) return root;
    if (root->key == key) {
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
        } else if (root->lchild == NULL || root->rchild == NULL) {
            BSTNode *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            BSTNode *temp = precursor(root);
            temp->key ^= root->key;
            root->key ^= temp->key;
            temp->key ^= root->key;
            root->lchild = delete_node(root->lchild, key);
        }
    } else {
        if (root->key > key) root->lchild = delete_node(root->lchild, key);
        else root->rchild = delete_node(root->rchild, key);
    }
}

void output(BSTNode *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("%d ", root->key);
    output(root->rchild);
}

int main() {
    srand(time(0));
    BSTNode *root = NULL;
    #define OP_NUM 20
    int key;
    for (int i = 0; i < OP_NUM; i++) {
        key = rand() % 30;
        root = insert(root, key);
        printf("insert %d to tree\n", key);
        output(root), printf("\n");
    }
    for (int i = 0; i < OP_NUM; i++) {
        int key = rand() % 30;
        root = delete_node(root, key);
        printf("delete %d from tree\n", key);
        output(root), printf("\n");
    }
    return 0;
}
