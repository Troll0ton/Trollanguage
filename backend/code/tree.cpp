#include "../include/tree.h"

//-----------------------------------------------------------------------------

void tree_info_ctor_ (Tree_info *info, const char* log_file, int line)
{
    info->file_dump = fopen ("backend/dump/tree_dump.html", "w+");
    info->file_asm  = fopen ("COMMON/files/input.asm",      "w+");

    info->file_in = fopen ("COMMON/files/tree.txt", "rb");
    info->File_input = file_reader (info->file_in);
    info->Text = lines_separator (info->File_input);
    fclose (info->file_in);

    info->line      = line;
    info->log_file  = log_file;
    info->root      = NULL;
    info->var_value = DELETED_PAR;

    info->graph_num  = 0;
    info->curr_label = 0;
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
    fclose (info->file_asm);

    clear_mem (info->Text, info->File_input);

    info->log_file   = NULL;
    info->line       = DELETED_PAR;
    info->curr_line  = DELETED_PAR;
    info->curr_cell  = DELETED_PAR;
    info->var_value  = DELETED_PAR;
    info->curr_label = DELETED_PAR;
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
    INIT_NODE (new_root, NULL, NULL, orig_root->parent,
               orig_root->type, orig_root->val, orig_root->priority);

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
    INIT_NODE (new_node, NULL, NULL, info->curr_parent,
               curr_node->type, curr_node->val, curr_node->priority);

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
    root->val  = val;

    return root;
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
    info->file_dot = fopen ("backend/dump/list_graph.dot", "w+");

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
    sprintf (dot_name, "dot -Tpng backend/dump/list_graph.dot -o backend/dump/graph%d.png", info->graph_num);

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

    if(IS_TYPE (root, OP))
    {
        dot_print ("fillcolor = paleturquoise1, label = \" { <ptr> TYPE: OPERATION (%d) | ",
                   root->priority);

        #define OP_DEF(cmd, cmd_name)             \
        case(cmd):                                \
        {                                         \
            dot_print (cmd_name);                 \
                                                  \
            break;                                \
        }                                         \

        switch(root->val.op)
        {
            //-----------------------------------------------------------------------------

            #include "../include/codegen/op_def.h"

            //-----------------------------------------------------------------------------

            default:
            {
                printf ("UNKNOWN FUNCTION!\n");
            }
        }

        #undef OP_DEF
    }

    else if(IS_TYPE (root, NUM))
    {
        dot_print ("fillcolor = coral2, label = \" { <ptr> TYPE: NUMERIC (%d) | %lg",
                   root->priority,root->val.num);
    }

    else if(IS_TYPE (root, VAR))
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





