#include "frontend/include/frontend.h"
#include "frontend/include/optimization.h"

//-----------------------------------------------------------------------------

#define NUM_OF_LINES info.File_input->num_of_lines

int main ()
{
    Tree_info info = { 0 };

    tree_info_ctor (&info);

    info.root = get_statement (&info);

    simplify_tree (info.root, &info);

    save_tree (info.root, &info);

    tree_dump (&info);

    tree_dtor (info.root);

    tree_info_dtor (&info);

    return 0;
}

//-----------------------------------------------------------------------------
