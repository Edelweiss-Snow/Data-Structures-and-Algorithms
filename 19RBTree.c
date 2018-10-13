/*************************************************************************
	> File Name: test.cpp
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月28日 星期五 16时21分13秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct RBNode {
    int key, color; // 0: red 1: black 2:double black
    struct RBNode *lchild, *rchild;
} RBNode;

RBNode *NIL;

__attribute__((constructor))
void init_nil() {
    NIL = (RBNode *)malloc(sizeof(RBNode));
    NIL->color = 1;
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

RBNode *get_node(int key) {
    RBNode *p = (RBNode *)malloc(sizeof(RBNode));
    p->key = key;
    p->color = 0;
    p->lchild = p->rchild = NIL;
    return p;
}

int hasRedchild(RBNode *node) {
    return node->lchild->color == 0 || node->rchild->color == 0;
}

RBNode *left_rotate(RBNode *root) {
    RBNode *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

RBNode *right_rotate(RBNode *root) {
    RBNode *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

RBNode *insert_maintain(RBNode *root) {
    if (!hasRedchild(root)) return root;//当前节点没有红色孩子节点的时候，插入不会发生冲突，如果是判断是否为NIL节点时，当他的2个子孩子为黑时也会调整
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        if (hasRedchild(root->lchild) || hasRedchild(root->rchild)) {
            root->color = 0;
            root->lchild->color = root->rchild->color = 1;
        }
        return root;
    }
    if (root->lchild->color == 0) {
        if (!hasRedchild(root->lchild)) return root;
        if (root->lchild->rchild->color == 0) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (!hasRedchild(root->rchild)) return root;
        if (root->rchild->lchild->color == 0) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    root->color = 0;
    root->lchild->color = root->rchild->color = 1;
    return root;
}

RBNode *__insert(RBNode *root, int key) {
    if (root == NIL) return get_node(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = __insert(root->lchild, key);
    else root->rchild = __insert(root->rchild, key);
    return insert_maintain(root);
}

RBNode *insert(RBNode *root, int key) {
    root = __insert(root, key);
    root->color = 1;
    return root;
}

RBNode *predecessor(RBNode *node) {
    RBNode *temp = node->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

RBNode *erase_maintain(RBNode *root) {
    if (root->lchild->color != 2 && root->rchild->color != 2) return root;
    if (root->lchild->color == 0 || root->rchild->color == 0) {
        root->color = 0;
        if (root->lchild->color == 2) {
            root->rchild->color = 1;
            root = left_rotate(root);
            root->lchild = erase_maintain(root->lchild);
        } else {
            root->lchild->color = 1;
            root = right_rotate(root);
            root->rchild = erase_maintain(root->rchild);
        }
        return root;
    } 
    if (root->lchild->color == 2) {
        if (!hasRedchild(root->rchild)) {
            root->color += 1;
            root->lchild->color = 1;
            root->rchild->color = 0;
            return root;
        } else if (root->rchild->lchild->color == 0) {
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = 1;
            root->rchild->rchild->color = 0;
        }
        root->lchild->color = 1;
        root = left_rotate(root);
        root->color = root->lchild->color;
        root->lchild->color = root->rchild->color = 1;
    } else {
        if (!hasRedchild(root->lchild)) {
            root->color += 1;
            root->rchild->color = 1;
            root->lchild->color = 0;
            return root;
        } else if (root->lchild->rchild->color == 0) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = 1;
            root->lchild->lchild->color = 0;
        }
        root->rchild->color = 1;
        root = right_rotate(root);
        root->color = root->rchild->color;
        root->lchild->color = root->rchild->color = 1;
    }
    return root;
}

RBNode *__erase(RBNode *root, int key) {
    if (root == NIL) return root;
    if (root->key == key) {
        if (root->lchild == NIL && root->rchild == NIL) {
            NIL->color += root->color;
            free(root);
            return NIL;
        } else if (root->lchild == NIL || root->rchild == NIL) {
            RBNode *temp = (root->lchild != NIL) ? root->lchild : root->rchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            RBNode *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root, temp->key);
        }
    } else {
        if (root->key > key) root->lchild = __erase(root->lchild, key);
        else root->rchild = __erase(root->rchild, key);
    }
    return erase_maintain(root);
}

RBNode *erase(RBNode *root, int key) {
    root = __erase(root, key);
    root->color = 1;
    return root;
}

void clear(RBNode *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(RBNode *root) {
    if (root == NIL) return ;
    printf("(%d | %d, %d, %d)\n", root->color, root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int op, value;
    RBNode *root = NIL;
    while (scanf("%d%d", &op, &value) != EOF) {
        switch (op) {
            case 0: 
                printf("\ninsert %d\n", value);
                root = insert(root, value); break;
            case 1: 
                printf("\ndelete %d\n", value);
                root = erase(root, value); break;
            default: printf("error\n");
        }
        printf("----------\n");
        output(root);
    }
    return 0;
}
