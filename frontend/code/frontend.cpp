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

        #define OP_DEF(cmd, cmd_name, code, ...)  \
        if(curr_op == cmd_name[0])                \
        {                                         \
            INIT (cmd, 2);                        \
                                                  \
            left_node = new_node;                 \
        }                                         \
        else

        //-----------------------------------------------------------------------------

        #include "../include/codegen/op_def.h"

        //-----------------------------------------------------------------------------

        #undef OP_DEF

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

        #define OP_DEF(cmd, cmd_name, code, ...)  \
        if(curr_op == cmd_name[0])                \
        {                                         \
            INIT (cmd, 1);                        \
                                                  \
            left_node = new_node;                 \
        }                                         \
        else

        //-----------------------------------------------------------------------------

        #include "../include/codegen/op_def.h"

        //-----------------------------------------------------------------------------

        #undef OP_DEF

        //else (IN CODEGEN)

        printf ("UNKOWN COMMAND - PRIORITY 1!\n");
    }

    return left_node;
}

//-----------------------------------------------------------------------------

Node *get_assignment (char **grammar)
{
    Node *left_node = get_str (grammar);

    (*grammar)++;

    Node *right_node = get_expression (grammar);

    CHECK_EXPRESSION (**grammar == '\0', "END OF EXPRESSION\n");

    INIT (ASG, 0);

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_grammar (char **grammar, Tree_info *info)
{
    if(**grammar == '\0' || **grammar == '\r' || **grammar == '\n')   //handle empty lines
    {
        info->curr_line++;

        return get_grammar (&info->Text[info->curr_line].begin_line, info);
    }

    if(!strncmp (*grammar, "if", 2))
    {
        return get_condition (grammar, info);
    }

    /*if(!strncmp (*grammar, "funct", 5))
    {
        return get_funct_init (grammar, info);
    } */

    if(!strncmp (*grammar, "while", 5))
    {
        return get_cycle (grammar, info);
    }

    if(strchr (*grammar, '='))
    {
        return get_assignment (grammar);
    }

    Node *root = get_expression (grammar);

    CHECK_EXPRESSION (**grammar == '\0', "END OF EXPRESSION\n");

    return root;
}

//-----------------------------------------------------------------------------

Node *get_condition (char **grammar, Tree_info *info)
{
    (*grammar) += 2;

    //    condition
    //        V
    Node *left_node = get_brackets (grammar);

    //      body
    //       V
    Node *right_node = get_if_body (grammar, info);

    INIT (IF, 0);

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_if_body (char **grammar, Tree_info *info)
{
    Node *left_node = NULL;

    Node *right_node = NULL;

    if(**grammar == '{')
    {
        info->curr_line++;

        left_node = get_sequence (info);
    }

    else
    {
        (*grammar)++;

        left_node = get_grammar (grammar, info);
    }

    info->curr_line++;

    right_node = get_else_body (&info->Text[info->curr_line].begin_line, info);

    INIT (BODY, 0);

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_else_body (char **grammar, Tree_info *info)
{
    if(!strncmp (*grammar, "else", 4))
    {
        (*grammar) += 4;

        if(**grammar == '{')
        {
            info->curr_line++;

            return get_sequence (info);
        }

        else
        {
            (*grammar)++;

            return get_grammar (grammar, info);
        }
    }

    else
    {
        info->curr_line--;

        return NULL;
    }
}

//-----------------------------------------------------------------------------

Node *get_cycle (char **grammar, Tree_info *info)
{
    (*grammar) += 5;

    Node *left_node = get_brackets (grammar);

    Node *right_node = NULL;

    if(**grammar == '{')
    {
        info->curr_line++;

        right_node = get_sequence (info);
    }

    else
    {
        (*grammar)++;

        right_node = get_grammar (grammar, info);
    }

    INIT (WHILE, 0);

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_sequence (Tree_info *info)
{
    Node *left_node = get_grammar (&info->Text[info->curr_line].begin_line, info);

    nullify_tree_pars (info);

    info->curr_line++;

    while(info->curr_line < info->File_input->num_of_lines && info->Text[info->curr_line].begin_line[0] != '}')
    {
        Node *right_node = get_grammar (&info->Text[info->curr_line].begin_line, info);

        info->curr_line++;

        INIT (SEQ, 0);

        left_node = new_node;
    }

    return left_node;
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
        return get_math_funct (grammar, name);
    }

    val.var = *name;

    INIT_VAR (val);

    return new_node;
}

//-----------------------------------------------------------------------------

Node *get_math_funct (char **grammar, char *name)
{
    Node *right_node = NULL;
    Node *left_node = NULL;

    #define OP_DEF(cmd, cmd_name, code, ...)  \
    if(stricmp (name, cmd_name) == 0)         \
    {                                         \
        right_node = get_brackets (grammar);  \
        INIT (cmd, 4);                        \
                                              \
        return new_node;                      \
    }

    //-----------------------------------------------------------------------------

    #include "../include/codegen/op_def.h"

    //-----------------------------------------------------------------------------

    #undef OP_DEF

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



