
//{----------------------------------------------------------------------------
//!                       OPERATIONS CODEGEN
//}----------------------------------------------------------------------------

OP_DEF(ADD, "+",
{
    curr_node->val.num = LEFT_NUM + RIGHT_NUM;
})

OP_DEF(SUB, "-",
{
    curr_node->val.num = LEFT_NUM - RIGHT_NUM;
})

OP_DEF(MUL, "*",
{
    curr_node->val.num = LEFT_NUM * RIGHT_NUM;
})

OP_DEF(DIV, "/",
{
    curr_node->val.num = LEFT_NUM / RIGHT_NUM;
})

OP_DEF(POW, "^",
{
    curr_node->val.num = pow (LEFT_NUM, RIGHT_NUM);
})

OP_DEF(SIN, "sin",
{
    curr_node->val.num = sin (RIGHT_NUM);
})

OP_DEF(COS, "cos",
{
    curr_node->val.num = cos (RIGHT_NUM);
})

OP_DEF(LN, "ln",
{
    curr_node->val.num = log (RIGHT_NUM);
})

OP_DEF(TG, "tg",
{
    curr_node->val.num = tan (RIGHT_NUM);
})

OP_DEF(CTG, "ctg",
{
    curr_node->val.num = 1 / tan (RIGHT_NUM);
})

OP_DEF(ASG, "ASSIGNMENT",
{

})

OP_DEF(SEQ, "SEQUENCE",
{

})

