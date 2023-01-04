#include "../include/differentiator.h"

//-----------------------------------------------------------------------------

void choose_mode (Tree_info *info)
{
    printf ("CHOOSE THE MODE:\n\
            0 - calc function in point;\n\
            1 - calc derivative\n");

    int sym = 0;

    scanf ("%d", &sym);

    switch(sym)
    {
        case CALC_POINT:
            calc_in_point_mode (info);
            break;
        case CALC_DERIV:
            calc_derivative_mode (info);
            break;
        default:
            printf ("MODE DOES NOT EXIST!\n");
            break;
    }
}

//-----------------------------------------------------------------------------

#define CURR_LINE    &(info->Text[line].begin_line)
#define NUM_OF_LINES info->File_input->num_of_lines

void calc_in_point_mode (Tree_info *info)
{
    printf ("INPUT VAR VALUE:");

    scanf ("%lf", &info->var_value);

    for(int line = 0; line < NUM_OF_LINES - 1; line++)
    {
        nullify_tree_pars (info);

        info->root = get_grammar (CURR_LINE);

        print_expression (info);

        print_simplified (info);

        tree_dtor (info->root);
    }
}

//-----------------------------------------------------------------------------

void calc_derivative_mode (Tree_info *info)
{
    for(int line = 0; line < NUM_OF_LINES - 1; line++)
    {
        nullify_tree_pars (info);

        info->root = get_grammar (CURR_LINE);

        print_expression (info);

        print_derivative (info);

        print_simplified (info);

        tree_dtor (info->root);
    }
}

#undef CURR_LINE
#undef NUM_OF_LINES

//-----------------------------------------------------------------------------

void print_expression (Tree_info *info)
{
    LINES;

    fprintf (info->file_tex, "Current expression:\\\\\n");

    txprint("\\( ");

    print_tree_inorder (info->root, info);

    txprint("\\) ");

    tree_dump (info);

    ENTER;
}

//-----------------------------------------------------------------------------

void print_derivative (Tree_info *info)
{
    fprintf (info->file_tex, "Calculate Derivative:\\\\\n");

    calc_derivative (info->root, info);

    txprint("\\( ");

    print_tree_inorder (info->root, info);

    txprint("\\) ");

    tree_dump (info);

    ENTER;
}

//-----------------------------------------------------------------------------

void print_simplified (Tree_info *info)
{
    fprintf (info->file_tex, "Simplify something:\\\\\n");

    simplify_tree (info->root, info);

    txprint("\\( ");

    print_tree_inorder (info->root, info);

    txprint("\\) ");

    tree_dump (info);

    ENTER;
    LINES;
    ENTER;
}

//-----------------------------------------------------------------------------
