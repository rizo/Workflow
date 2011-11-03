#ifndef _IOTREE_INC
#define _IOTREE_INC

#include "node.h"

NODE *load_file(const char *filename);
int save_file(NODE *node, const char *filename);
char *ask_filename(char *filename, int n);

#endif /* _IOTREE_INC */

