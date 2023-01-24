#include "../include/backend.h"

//-----------------------------------------------------------------------------

int main ()
{
    Tree_info info = { 0 };

    tree_info_ctor (&info);

    nullify_tree_pars (&info);

    read_tree (&info);

    tree_dump (&info);

    fprintf (info.file_asm, "call 97:\n");

    convert_to_asm (info.root, &info);

    fprintf (info.file_asm, "hlt\n");

    tree_dtor (info.root);

    tree_info_dtor (&info);

    return 0;
}

//-----------------------------------------------------------------------------
