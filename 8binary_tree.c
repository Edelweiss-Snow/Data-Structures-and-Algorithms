/*************************************************************************
	> File Name: 8binary_tree.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月14日 星期五 15时31分18秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node *get_node(int data) {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->data = data;
    return p;
}

void preorder(Node *root) {
    if (root == NULL) return ;
    printf("%d ", root->data);
    preorder(root->left);
    printf("left\n");
    preorder(root->right);
    printf("right\n");
    return ;
}

void inorder(Node *root) {
    if (root == NULL) return ;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(Node *root) {
    if (root == NULL) return ;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

Node *insert_node(Node *root) {
    if (root == NULL) root = get_node(1);
    root->left = get_node(2);
    root->right = get_node(3);
    root->left->left = get_node(4);
    root->right->right = get_node(5);
    return root;
}

int main() {
    Node *root = NULL;
    root = insert_node(root);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    return 0;
}
