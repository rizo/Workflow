#include <stdio.h>
#include <string.h>
#include "funcs.h"


int funcs_add(int type, char *description, const void *new_func, const void *del_func,
                const void *load_func, const void *save_func)
{
    funcs[type][FNEW] = new_func;
    funcs[type][FDEL] = del_func;
    funcs[type][FLOAD] = load_func;
    funcs[type][FSAVE] = save_func;

    strcpy(funcs_description[type],description);

    nfuncs++;

    return type;
}


const void *func_new(int type)
{
    return funcs[type][FNEW];
}

const void *func_del(int type)
{
    return funcs[type][FDEL];
}

const void *func_load(int type)
{
    return funcs[type][FLOAD];
}

const void *func_save(int type)
{
    return funcs[type][FSAVE];
}

const char *func_description(int type)
{
    return funcs_description[type];
}


/**************
 * Input/Output
 */
int funcs_add_io(int type, const void *read_func, const void *write_func)
{
    funcs_io[type][FREAD] = read_func;
    funcs_io[type][FWRITE] = write_func;

    return type;
}

const void *func_read(int type)
{
    return funcs_io[type][FREAD];
}

const void *func_write(int type)
{
    return funcs_io[type][FWRITE];
}


/*****************
 * General Purpose
 */
int funcs_select_list()
{
    int i, op=0;

    for(i=0;i<nfuncs;i++) {
        printf("%2d: %s\n",i+1,funcs_description[i]);
    }

    while(op<1 || op>nfuncs) {
        printf("Select an option [1-%d]: ",nfuncs);
        scanf("%d",&op);
    }

    while(getchar()!='\n'); // Clean the input for the next reading
    return op-1;
}

