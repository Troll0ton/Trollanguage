#include "../include/backend.h"

//-----------------------------------------------------------------------------

#define CURR_LINE info->Text[info->curr_line].begin_line

Node *read_tree (Tree_info *info)
{
    char sym = 0;

    sscanf (CURR_LINE, "%c", &sym);

    if(sym == '{')
    {
        Node *new_node = init_node (info);

        char *parenth_pos = strchr (CURR_LINE, '}');

        if(parenth_pos == NULL)
        {
            return handle_branch_node (info, new_node);
        }

        else
        {
            *parenth_pos = '\0';

            return handle_end_node (info, new_node);
        }
    }

    else
    {
        printf ("unidentified symbol;\n");
    }

    return NULL;
}

//-----------------------------------------------------------------------------

Node *init_node (Tree_info *info)
{
    char type = 0;

    value val = { 0 };

    sscanf (CURR_LINE + OFFSET_PARENTHESES, "%c", &type);

    type -= '0';

    switch((int) type)
    {
        case NUM:
        {
            sscanf (CURR_LINE + OFFSET_PARENTHESES + OFFSET_TYPE, "%lg", &val.num);

            break;
        }

        case VAR:
        {
            sscanf (CURR_LINE + OFFSET_PARENTHESES + OFFSET_TYPE, "%c", &val.var);

            break;
        }

        case OP:
        {
            sscanf (CURR_LINE + OFFSET_PARENTHESES + OFFSET_TYPE, "%d", &val.op);

            break;
        }

        case NUL:
        {
            return NULL;
        }

        default:
        {
            printf ("UNKNOWN TYPE!\n");
        }
    }

    INIT_NODE (new_node, NULL, NULL, NULL, type, val, 0);

    return new_node;
}

//-----------------------------------------------------------------------------

Node *handle_branch_node (Tree_info *info, Node *new_node)
{
    if(!info->root)
    {
        info->root = new_node;
    }

    else
    {
        new_node->parent = info->curr_parent;
    }

    info->curr_parent = new_node;

    info->curr_line++;

    new_node->left  = read_tree (info);
    new_node->right = read_tree (info);

    info->curr_line++;

    return new_node;
}

//-----------------------------------------------------------------------------

Node *handle_end_node (Tree_info *info, Node *new_node)
{
    if(!info->root)
    {
        info->root = new_node;
    }

    else if(new_node)
    {
        new_node->parent = info->curr_parent;
    }

    info->curr_line++;

    return new_node;
}

#undef CURR_LINE

//-----------------------------------------------------------------------------

void convert_to_asm (Node *curr_node, Tree_info *info)
{
    if(IS_OP (curr_node, ASG))
    {
        convert_to_asm (curr_node->right, info);

        trprint ("pop r%cx\n", curr_node->left->val.var);
    }

    else
    {
        if(curr_node->left || curr_node->right)
        {
            if(curr_node->left)
            {
                convert_to_asm (curr_node->left, info);
            }

            if(curr_node->right)
            {
                convert_to_asm (curr_node->right, info);
            }
        }

        if(!IS_OP(curr_node, SEQ))
        {
            print_values (curr_node, info);

            trprint ("\n");
        }
    }
}

//-----------------------------------------------------------------------------

void print_values (Node *curr_node, Tree_info *info)
{
    if(IS_TYPE (curr_node, OP))
    {
        #define OP_DEF(cmd, cmd_name)             \
        case(cmd):                                \
        {                                         \
            trprint (cmd_name);                   \
                                                  \
            break;                                \
        }                                         \

        switch(curr_node->val.op)
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

    else if(IS_TYPE (curr_node, NUM))
    {
        trprint ("push %lg", curr_node->val.num);
    }

    else if(IS_TYPE (curr_node, VAR))
    {
        trprint ("push r%cx", curr_node->val.var);
    }

    else
    {
        printf ("UNKNOWN VALUE!\n");
    }
}

//-----------------------------------------------------------------------------
