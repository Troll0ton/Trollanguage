
//{----------------------------------------------------------------------------
//!                       CALCULATIONS CODEGEN
//}----------------------------------------------------------------------------

CMD_DEF(ADD, "ADD",
{
    curr_node->val.num = LEFT_NUM + RIGHT_NUM;
})

CMD_DEF(SUB, "SUB",
{
    curr_node->val.num = LEFT_NUM - RIGHT_NUM;
})

CMD_DEF(MUL, "MUL",
{
    curr_node->val.num = LEFT_NUM * RIGHT_NUM;
})

CMD_DEF(DIV, "DIV",
{
    curr_node->val.num = LEFT_NUM / RIGHT_NUM;
})

CMD_DEF(POW, "POW",
{
    curr_node->val.num = pow (LEFT_NUM, RIGHT_NUM);
})

CMD_DEF(SIN, "SIN",
{
    curr_node->val.num = sin (RIGHT_NUM);
})

CMD_DEF(COS, "COS",
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

