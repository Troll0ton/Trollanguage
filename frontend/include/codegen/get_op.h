
//{----------------------------------------------------------------------------
//!                       SPECIAL GRAMMAR PROCESSING
//!                             (IN FRONTEND)
//}----------------------------------------------------------------------------

HANDLE_OP((strchr (*grammar, '>') || strchr (*grammar, '<')),
{
    Node *new_node = NULL;

    value val = { 0 };

    Node *left_node = get_str (grammar);

    (*grammar) += O(ASG);

    Node *right_node = get_expression (grammar);

    CHECK_EXPRESSION (**grammar == '\0', "END OF EXPRESSION\n");

    INIT (new_node, ASG, 0);

    comparison_node = ...
})

//-----------------------------------------------------------------------------

HANDLE_OP(!strncmp (*grammar, "if", O(IF)),
{
    Node *new_node  = NULL;
    Node *condition = NULL;

    value val = { 0 };

    (*grammar) += O(IF);

    if(comparison_node)
    {
        condition = comparison_node;
    }

    else
    {
        condition = get_brackets (grammar);
    }

    Node *if_body    = NULL;
    Node *left_node  = get_body (grammar, info);
    Node *right_node = NULL;

    info->curr_line++;

    char **curr_line = &CURR_LINE;

    if(!strncmp (*curr_line, "else", O(ELSE)))
    {
        (*curr_line) += O(ELSE);

        right_node = get_body (curr_line, info);
    }

    else
    {
        info->curr_line--;

        right_node = NULL;
    }

    INIT (if_body, BODY, 0);

    left_node  = condition;
    right_node = if_body;

    INIT (new_node, IF, 0);

    return new_node;
})

//-----------------------------------------------------------------------------

HANDLE_OP(!strncmp (*grammar, "funct", O(FUNCT)),
{
    Node *new_node = NULL;

    value val = { 0 };

    (*grammar) += O(FUNCT);

    (*grammar)++;

    Node *funct_name = get_str (grammar);

    info->curr_line++;

    Node *funct_body = NULL;
    Node *left_node  = NULL;

    Node *right_node = get_sequence (info);

    INIT (funct_body, BODY, 0);

    left_node  = funct_name;
    right_node = funct_body;

    INIT (new_node, FUNCT, 0);

    return new_node;
})

//-----------------------------------------------------------------------------

HANDLE_OP(!strncmp (*grammar, "while", O(WHILE)),
{
    Node *new_node = NULL;

    value val = { 0 };

    (*grammar) += O(WHILE);

    Node *left_node  = get_brackets (grammar);
    Node *right_node = get_body (grammar, info);

    INIT (new_node, WHILE, 0);

    return new_node;
})

//-----------------------------------------------------------------------------

HANDLE_OP(strchr (*grammar, '='),
{
    Node *new_node = NULL;

    value val = { 0 };

    Node *left_node = get_str (grammar);

    (*grammar) += O(ASG);

    Node *right_node = get_expression (grammar);

    CHECK_EXPRESSION (**grammar == '\0', "END OF EXPRESSION\n");

    INIT (new_node, ASG, 0);

    return new_node;
})

//-----------------------------------------------------------------------------
