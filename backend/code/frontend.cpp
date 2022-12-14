#include "../include/frontend.h"

//{----------------------------------------------------------------------------
//!                                (and with union value)
//! INIT_OP_1 - initialize operator-node with 1-priority and left and right son;
//! INIT_OP_2 - initialize operator-node with 2-priority and left and right son;
//! INIT_OP_3 - initialize operator-node with 3-priority and left and right son;
//! INIT_OP_4 - initialize operator-node with 4-priority;
//!
//! 1 = +, -
//! 2 = *, /
//! 3 = ^
//! 4 = sin, cos, tg, ctg, ln, arcsin, arccos, arctg, arcctg
//!
//}----------------------------------------------------------------------------

Node *get_mul_div (char **grammar)
{
    Node *left_node = get_pow (grammar);

    while(IS_('*') || IS_('/'))
    {
        char curr_op = **grammar;
        (*grammar)++;

        Node *right_node = get_mul_div (grammar);

        #define CMD_DEF(cmd, cmd_name, code, ...) \
        if(curr_op == cmd_name)                   \
        {                                         \
            INIT (cmd, 2);                        \
                                                  \
            left_node = new_node;                 \
        }                                         \
        else

        //-----------------------------------------------------------------------------

        #include "../include/codegen/op_2.h"

        //-----------------------------------------------------------------------------

        #undef CMD_DEF

        //else
        printf ("UNKOWN COMMAND - PRIORITY 1!\n");
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_pow (char **grammar)
{
    Node *left_node = get_brackets (grammar);

    while(IS_('^'))
    {
        (*grammar)++;

        Node *right_node = get_brackets (grammar);

        // oper_name  oper_priority
        //     V       V
        INIT (POW,     3);

        left_node = new_node;
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_brackets (char **grammar)
{
    Node *new_node = NULL;

    if(IS_('('))
    {
        (*grammar)++;

        new_node = get_expression (grammar);

        CHECK_EXPRESSION (**grammar == ')', "CLOSING BRACKET\n");

        (*grammar)++;
    }

    else
    {
        new_node = get_bottom (grammar);
    }

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_expression (char **grammar)
{
    Node *left_node = get_mul_div (grammar);

    while(IS_('+') || IS_('-'))
    {
        char curr_op = **grammar;
        (*grammar)++;

        Node *right_node = get_mul_div (grammar);

        #define CMD_DEF(cmd, cmd_name, code, ...) \
        if(curr_op == cmd_name)                   \
        {                                         \
            INIT (cmd, 1);                        \
                                                  \
            left_node = new_node;                 \
        }                                         \
        else

        //-----------------------------------------------------------------------------

        #include "../include/codegen/op_1.h"

        //-----------------------------------------------------------------------------

        #undef CMD_DEF

        //else
        printf ("UNKOWN COMMAND - PRIORITY 1!\n");
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_grammar (char **grammar)
{
    Node *root = get_expression (grammar);

    CHECK_EXPRESSION (**grammar == '\0', "END OF EXPRESSION\n");

    return root;
}

//-----------------------------------------------------------------------------

Node *get_str (char **grammar)
{
    char name[MAX_LEN] = "";

    value val = { 0 };

    int i = 0;

    while(isalpha (**grammar) && i < MAX_LEN)
    {
        name[i] = **grammar;
        i++;

        (*grammar)++;
    }

    if(IS_('('))
    {
        return get_funct (grammar, name);
    }

    val.var = *name;

    INIT_VAR (val);

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_funct (char **grammar, char *name)
{
    Node *right_node = get_brackets (grammar);
    Node *left_node = NULL;

    #define CMD_DEF(cmd, cmd_name, code, ...) \
    if(stricmp (name, cmd_name) == 0)         \
    {                                         \
        INIT (cmd, 4);                        \
                                              \
        return new_node;                      \
    }

    //-----------------------------------------------------------------------------

    #include "../include/codegen/op_4.h"

    //-----------------------------------------------------------------------------

    #undef CMD_DEF

    else
    {
        printf ("UNKNOWN COMMAND!\n");

        return NULL;
    }
}

//-----------------------------------------------------------------------------

#define VALUE_NUM val.num

Node *get_bottom (char **grammar)
{
    value val = { 0 };

    const char *str_old = *grammar;

    if(isalpha (**grammar))
    {
        return get_str (grammar);
    }

    if(is_num (**grammar))
    {
        int num_offset = 0;

        sscanf (*grammar, "%lf%n", &VALUE_NUM, &num_offset);

        *grammar += num_offset;
    }

    INIT_NUM (val);

    CHECK_EXPRESSION (*grammar != str_old, "ERROR WHILE GET NUM\n");

    return new_node;
}

#undef VALUE_NUM

//-----------------------------------------------------------------------------

void save_tree (Node *Curr_node, Tree_info *Info)
{
    value val = { 0 };

    switch(curr_node->type)
    {
        case NUM:
        {
            curr_node->val.num = 0;

            return curr_node;
        }

        case VAR:
        {
            curr_node->type = NUM;
            curr_node->val.num = 1;

            return curr_node;
        }

        case OP:
        {
            #define CMD_DEF(cmd, cmd_name, ...) \
            case cmd:                           \
            {                                   \
                __VA_ARGS__                     \
            }

            switch(curr_node->val.op)
            {
                //-----------------------------------------------------------------------------

                #include "../include/codegen/op_1.h"
                #include "../include/codegen/op_2.h"
                #include "../include/codegen/op_3.h"
                #include "../include/codegen/op_4.h"

                //-----------------------------------------------------------------------------

                default:
                {
                    printf ("UNKNOWN FUNCTION!\n");
                }
            }

            #undef CMD_DEF

            return NULL;
        }

        default:
        {
            printf ("MIDDLEEND - UNKNOWN TYPE!: %d\n", curr_node->type);

            return NULL;
        }
    }

    trprint("{%s", Curr_node->name);

    if(Curr_node->Left || Curr_node->Right)
    {
        trprint("\n");

        if(Curr_node->Left)
        {
            save_tree (Curr_node->Left, Info);
        }

        else trprint("{NULL}\n");

        if(Curr_node->Right)
        {
            save_tree (Curr_node->Right, Info);
        }

        else trprint("{NULL}\n");
    }

    trprint("}\n");
}

//-----------------------------------------------------------------------------


