/*************************************************************************
	> File Name: 10binary.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年09月16日 星期日 15时26分31秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0
#define OK 1

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
}Node;

typedef struct Stack {
    Node **data;
    int length, top_index;
}Stack;

void init(Stack *s, int length) {
    s->length = length;
    s->data = (Node**) malloc(sizeof(Node*) * length);
    s->top_index = -1;
}

int push(Stack *s, Node* data) {
    if (s->top_index + 1 >= s->length) {
        return ERROR;
    }
    s->data[++s->top_index] = data;
    return OK;
}

int pop(Stack *s) {
    if (s->top_index < 0) {
        return ERROR;
    }
    s->top_index--;
    return OK;
}

Node* top(Stack *s) {
    if (s->top_index < 0) {
        return NULL;
    }
    return s->data[s->top_index];
}

int empty(Stack *s) {
    return s->top_index < 0;
}

void clear(Stack *s) {
    free(s->data);
    free(s);
}

Node* init_node(char data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

Node *create_binary_tree(char *buffer, Stack *stack) {
    Node *root = NULL;
    Node *p = NULL;
    int i = 0;
    int k = 0;
    while (i < strlen(buffer)) {
        switch(buffer[i]) {
            case '(': {
                k = 1;
                push(stack, p);
                break;
            }
            case ',': {
                k = 2;
                break;
            }
            case ')': {
                pop(stack);
                break;
            }
            default: {
                p = init_node(buffer[i]);
                    switch (k) {
                        case 0: {
                            root = p;
                            break;
                        }
                        case 1: {
                            top(stack)->lchild = p;
                            break;
                        }
                        case 2: {
                            top(stack)->rchild = p;
                            break;
                        }
                    }
             }
        }
        i++;
    }
    return root;
}

void output(Node *root) {
    if (root != NULL) {
        printf("%c", root->data);
        if (root->lchild != NULL) {
            printf("(");
            output(root->lchild);
            if (root->rchild == NULL) {
                printf(")");
            }
        }
        if (root->rchild != NULL) {
            if (root->lchild == NULL) {
                printf("(");
            }
            printf(",");
            output(root->rchild);
            printf(")");
        }
    } else {
        return;
    }
}

void clear_tree(Node *node) {
    if (node == NULL) {
        //printf("111");
        return;
    }
    if (node->lchild != NULL) {
        clear_tree(node->lchild);
    }
    if (node->rchild != NULL) {
        clear_tree(node->rchild);
    }
    free(node);
}

void delete_node(Node *p, char value) {
 //   printf("%c\n", value);
//     printf("%c == %c\n", p->data, value);    
 //   printf("%c\n", p->lchild->data);
    if(p->lchild != NULL) {
        if (p->lchild->data == value ) {
    //    printf("%c == %c", p->data, value);
            p->lchild = NULL;
            free(p->lchild);
            return;
        } else {
            delete_node(p->lchild, value);
        }    
    }
    
    if (p->rchild != NULL) {
        if (p->rchild->data == value) {
            p->rchild = NULL;
            free(p->rchild);
            return;
        } else {
            delete_node(p->rchild, value);
        }
    }  
/*
    if (p->lchild->data != value) {
        if (p->lchild != NULL) {
            delete_node(p->lchild, value);
        }
        if (p->rchild != NULL) {
            delete_node(p->rchild, value);
        }
    }
    if (p->rchild->data != value) {
        if (p->lchild != NULL) {
            delete_node(p->lchild, value);
        }
        if (p->rchild != NULL) {
            delete_node(p->rchild, value);
        }
    }*/
}

int main() {
    char buffer[40];
    scanf("%s", buffer);
//    printf("b = %d", buffer[0]);
    char value;
    scanf("%c", &value); 
//    printf("v = %c\n", value);
    if (buffer[0] == 0) {
        return 0;
    }
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    init(stack, 30);
    Node *root = create_binary_tree(buffer, stack);
    if (root->data == value) {
        return 0;
    }
    //printf("%c", root->data);
    //printf("%c", root->lchild->data);
    delete_node(root, value);
    output(root);
    clear(stack);
    clear_tree(root);
    return 0;
}
