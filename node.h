#ifndef _NODE_INC
#define _NODE_INC

#include <stdio.h>

 #define CHAR2INT(ch)    ((ch)>='0' && (ch)<='9' ? (ch)-'0' : \
                         (ch)>='a' && (ch)<='z' ? (ch)-'a' + ('9'-'0') + 1 : \
                         (ch)>='A' && (ch)<='Z' ? (ch)-'A' + ('9'-'0') + ('z'-'a') + 2 : \
                         0)

#define INT2CHAR(n) ((n)>=0 && (n)<=('9'-'0') ? \
                        (n) + '0' : \
                     (n)>('9'-'0') && (n)<=('9'-'0') + ('z'-'a') + 1 ? \
                        (n) + 'a' - ('9'-'0') - 1 : \
                     (n)>('9'-'0') + ('z'-'a') && (n)<=('9'-'0') + ('z'-'a') + ('Z'-'A') + 2 ? \
                        (n) + 'A' - ('9'-'0') - ('z'-'a') - 2 : \
                     '\0')

typedef struct node {
    struct node **children;
    int nchildren;

    int priority;
    int state;

    int type;
    void *info;
} NODE;


NODE *load_node(FILE *file);
int save_node(NODE *node, FILE *file);

NODE *new_node(int type);
void add_node(NODE *node, NODE *parent);
void del_node(NODE *node);
NODE *locate_node(NODE *node, char *location);

// Input/Output
void list_node(NODE *node);
char *select_list_node(NODE *node, char *op);

#endif /* _NODE_INC */

