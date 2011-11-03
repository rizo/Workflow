
#ifndef _TREE_INC
#define _TREE_INC

#include <stdio.h>

#define TYPE_TREE   0    // ID para TREE
#define DESC_TREE   "Base da árvore"

typedef struct {
    char name[20];
    char owner[30];
} TREE;


const void *new_tree(char *name, char *owner);
void delete_tree(void *tree);

void *load_tree(FILE *file);
int save_tree(const void *tree, FILE *file);


void *read_tree();
void write_tree(const void *tree, int ident);

#endif /* _TREE_INC */

