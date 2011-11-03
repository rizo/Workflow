#include <stdio.h>
#include "node.h"
#include "tree.h"
#include "project.h"
#include "funcs.h"
#include "iotree.h"

void help(char *name)
{
    printf("Usage: %s [task file]\n",name);
}

int menu(int loaded_tree)
{
    int op;

    if(loaded_tree)
    {
        puts("1: List");
        puts("2: List from node");
        puts("3: Write node");
        puts("4: Create");
        puts("5: Modify");
        puts("6: Delete");
        puts("7: Save");
        puts("8: Close");
    }
    else
    {
        puts("1: New");
        puts("2: Open");
    } 
    puts("0: Quit");
    
    do {
        printf("Select an option [0-%d]: ",(loaded_tree ? 8 : 2));
        scanf("%d",&op);
    } while( op < 0 || (loaded_tree ? op > 8 : op > 2) );

    while(getchar()!='\n'); // Clean the input for the next reading
    return op;
}

int main(int argc, char **argv)
{
    int op, sub_op;
    NODE *root=NULL;
    char sub_op_str[100];

    
    //for(op=0;op<65;op++)
    //    printf("%d: I2C: %c %d -- C2I: %d\n",op,INT2CHAR(op),INT2CHAR(op), CHAR2INT(INT2CHAR(op)) );
    //return 0;

    funcs_add(TYPE_TREE, DESC_TREE, new_tree, delete_tree, load_tree, save_tree);
    funcs_add_io(TYPE_TREE, read_tree, write_tree);

    funcs_add(TYPE_PROJ, DESC_PROJ, new_project, delete_project, load_project, save_project);
    funcs_add_io(TYPE_PROJ, read_project, write_project);

    // Processa os parâmetros passados
    switch(argc)
    {
        case 1:
            puts("INFO: No arguments");
            break;
        case 2:
            root = load_file(argv[1]);
            break;
        default:
            help(argv[0]);
            return 1;
    }

    // Ciclo do menu
    do {
        op = menu(root!=NULL);
        // Se já existe uma árvore a ser usada
        if(root!=NULL)
        {
            switch(op)
            {
                case 1: // List
                    list_node(root);
                    break;
                case 2: // List from node
                    select_list_node(root,sub_op_str);
                    list_node(locate_node(root,sub_op_str));
                    break;
                case 3:
                    select_list_node(root,sub_op_str);
                    NODE *node = locate_node(root,sub_op_str);
                    printf("[%p] \n",node);
                    void (*write)(const void *, int) = func_write(node->type);
                    write(node->info,0);
                    break;
                case 4: // Create
                    select_list_node(root,sub_op_str);
                    sub_op = funcs_select_list();
                    add_node(new_node(sub_op),locate_node(root,sub_op_str));
                    break;
                case 5: // Modify
                case 6: // Delete
                    fputs("Not implemented",stderr);
                    break;
                case 7: // Save
                    ask_filename(sub_op_str,100);
                    save_file(root,sub_op_str);
                    break;
                case 8: // Close
                    del_node(root);
                    root = NULL;
                    break;
            }
        }
        else    // Se ainda não existe nenhuma árvore
        {
            switch(op)
            {
                case 1: // New
                    sub_op = funcs_select_list();
                    root = new_node(sub_op);
                    break;
                case 2: // Open
                    ask_filename(sub_op_str,100);
                    root = load_file(sub_op_str);
                    break;
            }
        }
    } while(op!=0);     // Quit

    puts("Bye!");

    return 0;
}

