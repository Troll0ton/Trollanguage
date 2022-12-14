
CMD_DEF(POW, '^',
{
    Node *right_node_c = COPY_RIGHT;
    Node *left_node_c  = COPY_LEFT;
    Node *old_right = RIGHT_NODE;
    Node *old_left  = LEFT_NODE;
    RIGHT_NODE = NULL;
    LEFT_NODE = NULL;

    val.num = 1;

    INIT_NODE (one_node, NULL, NULL, NULL, NUM, val, 4);

    val.op = SUB;

    INIT_NODE (new_pow, old_right, one_node, NULL, OP, val, 1);

    val.op = POW;

    INIT_NODE (pow_expression, left_node_c, new_pow, NULL, OP, val, 3);

    val.op = MUL;

    INIT_NODE (new_node_1, CALC_DRV (old_left), pow_expression, NULL, OP, val, 2);

    val.op = MUL;

    ASSIGN_NODE (curr_node, right_node_c, new_node_1, curr_node->parent, OP, val, 2);

    return curr_node;
})

