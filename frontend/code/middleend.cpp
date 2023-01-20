//{----------------------------------------------------------------------------
//!                         OPTIMIZATION
//}----------------------------------------------------------------------------

#include "../include/middleend.h"

//-----------------------------------------------------------------------------

#define COPY_LEFT copy_tree (curr_node->left, info)
#define COPY_RIGHT copy_tree (curr_node->right, info)
#define LEFT_NODE curr_node->left
#define RIGHT_NODE curr_node->right

#define LEFT_NUM  curr_node->left->val.num
#define RIGHT_NUM curr_node->right->val.num
#define DETECTED return true
#define OLD_VAL                         \
        Node *old_right = RIGHT_NODE;   \
        Node *old_left  = LEFT_NODE;
#define FREE_OLD                        \
        if(old_right) free (old_right); \
        if(old_left) free (old_left);

//-----------------------------------------------------------------------------

bool simplify_tree (Node *curr_node, Tree_info *info)
{
    if(LEFT_NODE)
    {
        while(simplify_tree (LEFT_NODE, info))  { }
    }

    if(RIGHT_NODE)
    {
        while(simplify_tree (RIGHT_NODE, info)) { }
    }

    simplify_node (curr_node, info);

    return false;
}

//-----------------------------------------------------------------------------

bool simplify_node (Node *curr_node, Tree_info *info)
{
    if(simplify_const (curr_node, info))
    {
        // return true;
         DETECTED;
    }

    #define COND_DEF(condition, ...) \
    if(condition)                    \
    {                                \
        OLD_VAL;                     \
                                     \
        __VA_ARGS__                  \
                                     \
        FREE_OLD;                    \
                                     \
        DETECTED;                    \
    }

    //-----------------------------------------------------------------------------

    #include "../include/codegen/conditions.h"

    //-----------------------------------------------------------------------------

    #undef COND_DEF

    if(info->var_value != DELETED_PAR && IS_TYPE (curr_node, VAR))
    {
         ASSIGN_NUM (curr_node, info->var_value);

         DETECTED;
    }

    return false;
}

//-----------------------------------------------------------------------------

bool simplify_const (Node *curr_node, Tree_info *info)
{
    if(IS_TYPE (curr_node, OP) &&
       IS_TYPE (RIGHT_NODE, NUM) &&
     ((LEFT_NODE && IS_TYPE (LEFT_NODE, NUM)) ||
      !LEFT_NODE))
    {
        curr_node->type = NUM;
        curr_node->priority = 4;

        #define OP_DEF(cmd, cmd_name, ...)  \
        case cmd:                           \
        {                                   \
            __VA_ARGS__                     \
                                            \
            break;                          \
        }

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

        if(LEFT_NODE)
        {
            tree_dtor (LEFT_NODE);
        }

        if(RIGHT_NODE)
        {
            tree_dtor (RIGHT_NODE);
        }

        DETECTED;
    }

    return false;
}

#undef LEFT_NUM
#undef RIGHT_NUM
#undef LEFT_NODE
#undef RIGHT_NODE
#undef COPY_LEFT
#undef COPY_RIGHT

//-----------------------------------------------------------------------------



