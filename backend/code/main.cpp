#include "backend/include/backend.h"

//-----------------------------------------------------------------------------

int main ()
{
    Tree_info info = { 0 };

    tree_info_ctor (&info);

    nullify_tree_pars (&info);

    read_tree (&info);

    tree_dump (&info);

    create_asm_file (&info);

    tree_dtor (info.root);

    tree_info_dtor (&info);

    return 0;
}

//-----------------------------------------------------------------------------
