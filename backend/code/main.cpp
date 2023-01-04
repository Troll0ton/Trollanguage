#include "../include/differentiator.h"

//-----------------------------------------------------------------------------

int main ()
{
    Tree_info info = { 0 };

    tree_info_ctor (&info);

    create_latex_file (&info);

    choose_mode (&info);

    convert_to_pdf (&info);

    tree_info_dtor (&info);

    return 0;
}

//-----------------------------------------------------------------------------
