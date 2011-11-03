#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "node.h"

#define QUESTION(str)           printf("%10s: ",(str));

#define ANSWER(str,val,ident)   do { \
                                    int __putchar_i; \
                                    for(__putchar_i=0;__putchar_i<(ident);__putchar_i++) \
                                        putchar(' '); \
                                    printf("%10s: %s\n",(str),(val)); \
                                } while(0)

#define READ(str,size)          fgets((str), (size), stdin); \
                                (str)[strlen((str))-1]='\0';


const void *new_tree(char *name, char *owner)
{
    TREE *tree = (TREE *)malloc(sizeof(TREE));

    strcpy(tree->name, name);
    strcpy(tree->owner,owner);

    return tree;
}

void delete_tree(void *tree)
{
    free(tree);
}

void *load_tree(FILE *file)
{
    // Aloca uma nova tree
    TREE *tree = (TREE *)malloc(sizeof(TREE));
    
    // Lê do ficheiro
    fread(tree->name, sizeof(char), 20, file);
    fread(tree->owner, sizeof(char), 30, file);

    return tree;
}

int save_tree(const void *tree, FILE *file)
{
    TREE *t = (TREE *)tree;

    fwrite(t->name, sizeof(char), 20, file);
    fwrite(t->owner, sizeof(char), 30, file);

    return 0;
}


void *read_tree()
{
    // Aloca uma nova tree
    TREE *tree = (TREE *)malloc(sizeof(TREE));
    
    // Efectua a leitura do input
    QUESTION("Tree name");
    READ(tree->name, 20);

    QUESTION("Tree owner");
    READ(tree->owner, 30);

    return tree;
}


void write_tree(const void *tree, int ident)
{
    TREE *t = (TREE *)tree;

    ANSWER("Tree name",t->name,ident);
    ANSWER("Tree owner",t->owner,ident);
}

