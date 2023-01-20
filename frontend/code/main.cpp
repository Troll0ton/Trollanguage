#include "../include/frontend.h"
#include "../include/middleend.h"

//-----------------------------------------------------------------------------

//NUM_OF_LINES &info->File_input->num_of_lines       //sequence - SEQ (последовательность )

int main ()
{
    Tree_info info = { 0 };

    tree_info_ctor (&info);

    nullify_tree_pars (&info);

    info.root = get_grammar (&info.Text[0].begin_line);

    simplify_tree (info.root, &info);

    save_tree (info.root, &info);

    tree_dump (&info);

    tree_dtor (info.root);

    tree_info_dtor (&info);

    return 0;
}

//-----------------------------------------------------------------------------
