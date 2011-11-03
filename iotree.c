#include <stdio.h>
#include <string.h>
#include "node.h"


NODE *load_file(const char *filename)
{
    NODE *node;
    FILE *f=fopen(filename, "rb");

    if(f==NULL) {
        fprintf(stderr,"Cannot open '%s' for reading!\n",filename);
        return NULL;
    }

    node = load_node(f);

    fclose(f);

    return node;
}

int save_file(NODE *node, const char *filename)
{
    int ret;
    FILE *f=fopen(filename, "wb");
    
    if(f==NULL) {
        fprintf(stderr,"Cannot open '%s' for writing!\n",filename);
        return -1;
    }
    

    ret=save_node(node, f);

    fclose(f);

    return ret;
}

char *ask_filename(char *filename, int n){
    printf("Insert the path to the file: ");
    fgets(filename, n, stdin);
    filename[strlen(filename)-1]='\0';
    return filename;
}

