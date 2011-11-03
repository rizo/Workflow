#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "node.h"
#include "funcs.h"

/*
 * Lê a árvore de forma recursiva a partir de um ficheiro
 */
NODE *load_node(FILE *file)
{
    int i;
    struct node *node;
    void *(*func_load_handler)(FILE *);
    
    // Aloca um novo nó
    node = (NODE *)malloc(sizeof(NODE));
    if(!node) return NULL;

    // Lê do ficheiro os campos do nó
    fread(&(node->nchildren), sizeof(int), 1, file);
    fread(&(node->priority ), sizeof(int), 1, file);
    fread(&(node->state    ), sizeof(int), 1, file);
    fread(&(node->type     ), sizeof(int), 1, file);
    
    // Chama a função de leitura dos campos adicionais associados ao nó
    func_load_handler = func_load(node->type);
    node->info = func_load_handler(file);
    

    // Aloca espaço para os apontadores dos filhos
    node->children = (NODE **)malloc(sizeof(NODE)*node->nchildren);

    // Executa a leitura dos filhos de forma recursiva
    for(i=0;i<node->nchildren;i++)
    {
        node->children[i] = load_node(file);
    }
    
    return node;
}

/*
 * Escreve a árvore de forma recursiva para um ficheiro
 */
int save_node(NODE *node, FILE *file)
{
    int i;
    int (*func_save_handler)(const void *, FILE *);

    // Escreve no ficheiro os campos do nó
    fwrite(&(node->nchildren), sizeof(int), 1, file);
    fwrite(&(node->priority ), sizeof(int), 1, file);
    fwrite(&(node->state    ), sizeof(int), 1, file);
    fwrite(&(node->type     ), sizeof(int), 1, file);

    // Chama a função de escrita dos campos adicionais associados ao nó
    func_save_handler = func_save(node->type);
    func_save_handler(node->info,file);
    
    // Executa a escrita dos filhos de forma recursiva
    for(i=0;i<node->nchildren;i++)
    {
        save_node(node->children[i],file);
    }
    
    return 0;
}

/*
 * Cria um novo nó e executa a leitura
 */
NODE *new_node(int type)
{
    void *(*read)() = func_read(type);
    NODE *node = (NODE *)malloc(sizeof(NODE));

    if(!node) return NULL;
    
    node->nchildren = 0;
    node->children = NULL;

    node->type = type;
    node->priority = 0;

    node->info = read();

    return node;
}

/*
 * Adiciona o nó node ao nó parent
 */
void add_node(NODE *node, NODE *parent)
{
    printf("ParentNChildren:%d +1:%d\n", parent->nchildren, parent->nchildren+1);
    parent->children = (NODE **)realloc(parent->children, (parent->nchildren+1)*sizeof(NODE **));
    parent->children[parent->nchildren] = node;
    parent->nchildren++;
}

/*
 * Elimina um nó e todos os seus filhos
 */
void del_node(NODE *node)
{
    int i;
    int (*func_del_handler)(const void *);

    if(!node) return;

    // Elimina os filhos
    for(i=0;i<node->nchildren;i++)
        del_node(node->children[i]);
    
    free(node->children);
    
    // Chama a função para eliminar os campos adicinais do nó
    func_del_handler = func_del(node->type);
    func_del_handler(node->info);

    // Elimina o nó
    free(node);

    return;
}

/*
 * Localiza o nó na sub-árvore dada
 */
NODE *locate_node(NODE *node, char *location)
{
    int i;
    NODE *ret = node;

    for(i=1;isalnum(location[i]);i++)
    {
        if(! CHAR2INT(location[i]) < ret->nchildren)
            return NULL;
    
        ret = ret->children[CHAR2INT(location[i])];
    }

    printf("[%p]\n",ret);
    return ret;
}

/*
 * Input/Output
 */
void print_node(NODE *node, int pos, int index, char *indexs)
{
    if(node==NULL) return;

    int i;
    void (*write)(const void *, int) = func_write(node->type);
    
    indexs[pos]=INT2CHAR(index);
    indexs[pos+1]='\0';
    
    for(i=0;i<pos*4-1;i++)
        putchar('-');

    printf(" %s:\n", indexs);
    
    write(node->info,pos*4+1);

    
    for(i=0;i<node->nchildren;i++) {
        print_node(node->children[i],pos+1,i,indexs);
    }
}

/*
 * Lista a sub-árvore a partir do nó dado
 */
void list_node(NODE *node)
{
    char indexs[100];
    print_node(node, 0, 0, indexs);
}

/*
 * Lista a sub-árvore e pede a selecção de um nó
 */
char *select_list_node(NODE *node, char *op)
{
    list_node(node);

    do {
        printf("Select an option: ");
        scanf("%s",op);
    } while(0);

    while(getchar()!='\n'); // Clean the input for the next reading
    return op;
}

