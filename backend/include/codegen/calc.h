
//{----------------------------------------------------------------------------
//!                       CALCULATIONS CODEGEN
//}----------------------------------------------------------------------------

CMD_DEF(ADD, "add",
{
    curr_node->val.num = LEFT_NUM + RIGHT_NUM;
})

CMD_DEF(SUB, "sub",
{
    curr_node->val.num = LEFT_NUM - RIGHT_NUM;
})

CMD_DEF(MUL, "mul",
{
    curr_node->val.num = LEFT_NUM * RIGHT_NUM;
})

CMD_DEF(DIV, "div",
{
    curr_node->val.num = LEFT_NUM / RIGHT_NUM;
})

CMD_DEF(POW, "pow",
{
    curr_node->val.num = pow (LEFT_NUM, RIGHT_NUM);
})

CMD_DEF(SIN, "sin",
{
    curr_node->val.num = sin (RIGHT_NUM);
})

CMD_DEF(COS, "cos",
{
    curr_node->val.num = cos (RIGHT_NUM);
})

CMD_DEF(LN, "LOG",
{
    curr_node->val.num = log (RIGHT_NUM);
})

CMD_DEF(TG, "TAN",
{
    curr_node->val.num = tan (RIGHT_NUM);
})

CMD_DEF(CTG, "CTN",
{
    curr_node->val.num = 1 / tan (RIGHT_NUM);
})

