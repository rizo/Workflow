
#ifndef _PROJ_INC
#define _PROJ_INC

#include <stdio.h>
#include <time.h>

#define TYPE_PROJ   1    // ID para TREE
#define DESC_PROJ   "Projecto"

typedef struct {
    char name[20];
    char description[100];
    time_t creation_date;
} PROJECT;


const void *new_project(char *name, char *owner);
void delete_project(void *project);

void *load_project(FILE *file);
int save_project(const void *project, FILE *file);


void *read_project();
void write_project(const void *project, int ident);

#endif /* _PROJ_INC */

