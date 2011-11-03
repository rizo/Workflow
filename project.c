#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "project.h"
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


const void *new_project(char *name, char *owner)
{
    PROJECT *project = (PROJECT *)malloc(sizeof(PROJECT));

    strcpy(project->name, name);
    strcpy(project->description,owner);

    return project;
}

void delete_project(void *project)
{
    free(project);
}

void *load_project(FILE *file)
{
    // Aloca uma nova tree
    PROJECT *project = (PROJECT *)malloc(sizeof(PROJECT));
    
    // Lê do ficheiro
    fread(project->name, sizeof(char), 20, file);
    fread(project->description, sizeof(char), 100, file);
    fread(&project->creation_date, sizeof(time_t), 1, file);

    return project;
}

int save_project(const void *project, FILE *file)
{
    PROJECT *p = (PROJECT *)project;

    fwrite(p->name, sizeof(char), 20, file);
    fwrite(p->description, sizeof(char), 100, file);
    fwrite(&p->creation_date, sizeof(time_t), 1, file);

    return 0;
}


void *read_project()
{
    // Aloca uma nova tree
    PROJECT *project = (PROJECT *)malloc(sizeof(PROJECT));
    
    // Efectua a leitura do input
    QUESTION("Project name");
    READ(project->name, 20);

    QUESTION("Description");
    READ(project->description, 30);

    QUESTION("Creation date");
    scanf("%lu",&project->creation_date);

    return project;
}


void write_project(const void *project, int ident)
{
    PROJECT *p = (PROJECT *)project;

    ANSWER("Project name",p->name,ident);
    ANSWER("Description",p->description,ident);
    ANSWER("Creation date",ctime(&p->creation_date),ident);
}

