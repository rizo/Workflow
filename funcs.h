#ifndef _FUNCS_INC
#define _FUNCS_INC

#define FNEW    0
#define FDEL    1
#define FLOAD   2
#define FSAVE   3

#define FREAD   0
#define FWRITE  1

const void *funcs[30][4];
const void *funcs_io[30][2];
char funcs_description[30][30];
int nfuncs;

int funcs_add(int type, char *description, const void *new_func, const void *del_func,
                const void *load_func, const void *save_func);

const void *func_new(int type);
const void *func_del(int type);
const void *func_load(int type);
const void *func_save(int type);

// Input/Output
int funcs_add_io(int type, const void *read, const void *write);

const void *func_write(int type);
const void *func_read(int type);

int funcs_select_list();

#endif /* _FUNCS_INC */

