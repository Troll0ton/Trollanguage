
CMD_DEF(ADD, '+',
{
    LEFT_NODE  = CALC_DRV (LEFT_NODE);
    RIGHT_NODE = CALC_DRV (RIGHT_NODE);

    return curr_node;
})

CMD_DEF(SUB, '-',
{
    LEFT_NODE  = CALC_DRV (LEFT_NODE);
    RIGHT_NODE = CALC_DRV (RIGHT_NODE);

    return curr_node;
})
