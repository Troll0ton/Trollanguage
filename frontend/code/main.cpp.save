#include "../include/frontend.h"
#include "../include/middleend.h"

//-----------------------------------------------------------------------------

#define NUM_OF_LINES info.File_input->num_of_lines
                                                     //sequence - SEQ (последовательность )
                                                     //&info.Text[0].begin_line
int main ()
{
    Tree_info info = { 0 };

    tree_info_ctor (&info);

    info.root = get_sequence (&info);

    //simplify_tree (info.root, &info);

    save_tree (info.root, &info);

    tree_dump (&info);

    tree_dtor (info.root);

    tree_info_dtor (&info);

    return 0;
}

//-----------------------------------------------------------------------------
