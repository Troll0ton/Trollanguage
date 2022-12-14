
CMD_DEF(MUL, '*',
{
    Node *left_node_c  = COPY_LEFT;
    Node *right_node_c = COPY_RIGHT;

    val.op = MUL;

    INIT_NODE (new_node_1, CALC_DRV (LEFT_NODE), right_node_c, curr_node, OP, val, 2);

    val.op = MUL;

    INIT_NODE (new_node_2, left_node_c, CALC_DRV (RIGHT_NODE), curr_node, OP, val, 2);

    val.op = ADD;

    ASSIGN_NODE (curr_node, new_node_1, new_node_2, curr_node->parent, OP, val, 1);

    return curr_node;
})

CMD_DEF(DIV, '/',
{
    Node *left_node_c   = COPY_LEFT;
    Node *right_node_c  = COPY_RIGHT;
    Node *right_node_c1 = COPY_RIGHT;
    Node *right_node_c2 = COPY_RIGHT;

    val.op = MUL;
    INIT_NODE (new_node_1, CALC_DRV (LEFT_NODE), right_node_c, NULL, OP, val, 2);

    val.op = MUL;
    INIT_NODE (new_node_2, left_node_c, CALC_DRV (RIGHT_NODE), NULL, OP, val, 2);

    val.op = SUB;
    INIT_NODE (new_node_sub, new_node_1, new_node_2, curr_node, OP, val, 1);

    val.op = MUL;
    INIT_NODE (new_node_deg, right_node_c1, right_node_c2, curr_node, OP, val, 2);

    val.op = DIV;
    ASSIGN_NODE (curr_node, new_node_sub, new_node_deg, curr_node->parent, OP, val, 2);

    return curr_node;
})

