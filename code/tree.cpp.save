#include "../include/tree.h"

//-----------------------------------------------------------------------------

void tree_info_ctor_ (Tree_info *info, const char* log_file, int line)
{
    info->file_dump = fopen ("../dump/tree_dump.html", "w+");
    info->file_in = fopen ("../files/task1.txt", "rb");

    info->File_input = file_reader (info->file_in);
    info->Text = lines_separator (info->File_input);

    fclose (info->file_in);

    info->line     = line;
    info->log_file = log_file;
    info->root     = NULL;
    info->var_value = DELETED_PAR;

    info->graph_num = 0;
}

//-----------------------------------------------------------------------------

void nullify_tree_pars (Tree_info *info)
{
    info->curr_line = 0;
    info->curr_cell = 0;
    info->root = NULL;
    info->curr_parent = NULL;
}

//-----------------------------------------------------------------------------

void tree_info_dtor (Tree_info *info)
{
    fclose (info->file_dump);

    clear_mem (info->Text, info->File_input);

    info->log_file  = NULL;
    info->line      = DELETED_PAR;
    info->curr_line = DELETED_PAR;
    info->curr_cell = DELETED_PAR;
    info->var_value  = DELETED_PAR;
}

//-----------------------------------------------------------------------------

Node *create_node ()
{
    Node *New_node = (Node*) calloc (1, sizeof (Node));

    if(!New_node)
    {
        printf ("ERROR - memory allocation for new node!\n");
    }

    else
    {
        New_node->parent = NULL;
        New_node->left   = NULL;
        New_node->right  = NULL;
    }

    return New_node;
}

//-----------------------------------------------------------------------------

Node *copy_tree (Node *orig_root, Tree_info *info)
{
    INIT_NODE (new_root, NULL, NULL, orig_root->parent, orig_root->type, orig_root->val, orig_root->priority);

    info->curr_parent = new_root;

    if(orig_root->left)
    {
        new_root->left = copy_node (orig_root->left, info);
    }

    info->curr_parent = new_root;

    if(orig_root->right)
    {
        new_root->right = copy_node (orig_root->right, info);
    }

    return new_root;
}

//-----------------------------------------------------------------------------

Node *copy_node (Node *curr_node, Tree_info *info)
{
    INIT_NODE (new_node, NULL, NULL, info->curr_parent, curr_node->type, curr_node->val, curr_node->priority);

    info->curr_parent = new_node;

    if(curr_node->left)
    {
        new_node->left = copy_node (curr_node->left, info);
    }

    info->curr_parent = new_node;

    if(curr_node->right)
    {
        new_node->right = copy_node (curr_node->right, info);
    }

    return new_node;
}

//-----------------------------------------------------------------------------

Node *create_root (int type, value val, Tree_info *info)
{
    Node *root = create_node ();
    info->root = root;
    root->type = type;
    root->val = val;

    return root;
}

//-----------------------------------------------------------------------------

#define PARENT curr_node->parent
void print_tree_inorder (Node *curr_node, Tree_info *info)
{
    bool round_bracketing = false;
    bool figure_bracketing = false;

    if(PARENT &&
      (PARENT->priority > curr_node->priority ||
      (PARENT->priority == curr_node->priority &&
       PARENT->right == curr_node &&
      (IS_OP (PARENT, DIV) || IS_OP (PARENT, DIV)))))
    {
        round_bracketing = true;

        txprint ("(");
    }

    if(IS_OP (curr_node, DIV) || IS_OP (curr_node, POW))
    {
        figure_bracketing = true;

        txprint ("{");
    }

    if(curr_node->left)
    {
        if(figure_bracketing)
        {
            txprint ("{");
        }

        print_tree_inorder (curr_node->left, info);

        if(figure_bracketing)
        {
            txprint ("}");
        }
    }

    if(curr_node->type == OP)
    {
        #define CMD_DEF(cmd, cmd_name, code, ...) \
        case(cmd):                                \
        {                                         \
            txprint (cmd_name);                   \
                                                  \
            break;                                \
        }                                         \

        switch(curr_node->val.op)
        {
            //-----------------------------------------------------------------------------

            #include "../include/codegen/calc.h"

            //-----------------------------------------------------------------------------

            default:
            {
                printf ("UNKNOWN FUNCTION!\n");
            }
        }

        #undef CMD_DEF
    }

    else if(curr_node->type == NUM)
    {
        txprint ("%lg", curr_node->val.num);
    }

    else if(curr_node->type == VAR)
    {
        txprint ("%c", curr_node->val.var);
    }

    else
    {
        printf ("UNKNOWN VALUE!\n");
    }

    if(curr_node->right)
    {
        if(figure_bracketing)
        {
            txprint ("{");
        }

        print_tree_inorder (curr_node->right, info);

        if(figure_bracketing)
        {
            txprint ("}");
        }
    }

    if(figure_bracketing)
    {
        txprint ("}");
    }

    if(round_bracketing)
    {
        txprint (")");
    }
}

//-----------------------------------------------------------------------------

#define root info->root

void tree_dump (Tree_info *info)
{
    fprintf (info->file_dump,
             "<pre>\n"
             "_________________________TREE__________________________________\n\n"
             "TREE - [root - %p] at %s, LINE - %d \n\n",
             root, info->log_file, info->line);

    create_tree_graph (info);

    fprintf (info->file_dump,
             "_______________________________________________________________ \n</pre>\n\n");
}

//-----------------------------------------------------------------------------

#define CURR_CELL info->curr_cell

void create_tree_graph (Tree_info *info)
{
    info->file_dot = fopen ("../dump/list_graph.dot", "w+");

    dot_print ("digraph structs {    \n"
               "rankdir = TB;        \n"
               "graph [dpi = 200];   \n"
               "ranksep = 1.5;       \n"
               "edge[penwidth = 10]; \n");

    CURR_CELL = 0;

    create_cell (root, info);

    CURR_CELL = 1;

    dot_print("cell0 ");

    if(root->left)
    {
        build_connections (root->left, info);

        CURR_CELL++;
    }

    dot_print("cell0 ");

    if(root->right)
    {
        build_connections (root->right, info);
    }

    dot_print ("}\n");

    fclose (info->file_dot);

    char img_name[MAX_LEN] = "";
    char dot_name[MAX_LEN] = "";

    sprintf (img_name, "<img width=\"1400px\" src=\"../dump/graph%d.png\">   \n", info->graph_num);
    sprintf (dot_name, "dot -Tpng ../dump/list_graph.dot -o ../dump/graph%d.png", info->graph_num);

    info->graph_num++;

    system (dot_name);

    fprintf (info->file_dump, "%s", img_name);
}

#undef root

//-----------------------------------------------------------------------------

void create_cell (Node *root, Tree_info *info)
{
    dot_print ("cell%d [style = filled, color = black, shape=record, \n",
               CURR_CELL);

    if(root->type == OP)
    {
        dot_print ("fillcolor = paleturquoise1, label = \" { <ptr> TYPE: OPERATION (%d) | ",
                   root->priority);

        #define CMD_DEF(cmd, cmd_name, code, ...) \
        case(cmd):                                \
        {                                         \
            dot_print (cmd_name);                 \
                                                  \
            break;                                \
        }                                         \

        switch(root->val.op)
        {
            //-----------------------------------------------------------------------------

            #include "../include/codegen/calc.h"

            //-----------------------------------------------------------------------------

            default:
            {
                printf ("UNKNOWN FUNCTION!\n");
            }
        }

        #undef CMD_DEF
    }

    else if(root->type == NUM)
    {
        dot_print ("fillcolor = coral2, label = \" { <ptr> TYPE: NUMERIC (%d) | %lg",
                   root->priority,root->val.num);
    }

    else if(root->type == VAR)
    {
        dot_print ("fillcolor = darkolivegreen2, label = \" { <ptr> TYPE: VARIABLE (%d) | %c",
                   root->priority, root->val.var);
    }

    else
    {
        printf ("|UNKNOWN VALUE - %d!\n", root->type);
    }

    dot_print ("} \" ];                         \n"),

    CURR_CELL++;

    if(root->left)
    {
        create_cell (root->left, info);
    }

    if(root->right)
    {
        create_cell (root->right, info);
    }
}

//-----------------------------------------------------------------------------

void build_connections (Node *root, Tree_info *info)

{
    dot_print("-> cell%d;\n", CURR_CELL);

    int prev_cell = CURR_CELL;

    if(root->left)
    {
        dot_print("cell%d ", prev_cell);

        CURR_CELL++;

        build_connections (root->left, info);
    }

    if(root->right)
    {
        dot_print("cell%d ", prev_cell);

        CURR_CELL++;

        build_connections (root->right, info);
    }
}

#undef CURR_CELL

//-----------------------------------------------------------------------------

void create_latex_file (Tree_info *info)
{
    info->file_tex = fopen ("../files/file_out.tex", "w+");

    const char header[] = R"(
    \documentclass[12pt]{article}
    \usepackage[utf8]{inputenc}
    \usepackage{cmap}
    \usepackage{amsmath}
    \usepackage{amssymb}
    \usepackage{mathtools}
    \usepackage{mathtext}

    \usepackage[english, russian]{babel}

    \title{DIFFERENTIATOR}
    \author{Anton}
    \date{12 november 2022}

    \begin{document}

    \maketitle
    Your input: \\
    )";

    txprint ("%s\n", header);
}

//-----------------------------------------------------------------------------

void convert_to_pdf (Tree_info *info)
{
    char ending_lines[] = R"(
        End of the file
        \end{document}
    )";

    txprint ("%s\n", ending_lines);

    fclose (info->file_tex);

    system ("run_tex.bat");
}

//-----------------------------------------------------------------------------

void tree_dtor (Node *curr_node)
{
    if(curr_node->left)
    {
        tree_dtor (curr_node->left);
    }

    if(curr_node->right)
    {
        tree_dtor (curr_node->right);
    }

    if(curr_node->parent)
    {
        if(curr_node->parent->left == curr_node)
        {
            curr_node->parent->left = NULL;
        }

        if(curr_node->parent->right == curr_node)
        {
            curr_node->parent->right = NULL;
        }
    }

    free (curr_node);
}

//-----------------------------------------------------------------------------





