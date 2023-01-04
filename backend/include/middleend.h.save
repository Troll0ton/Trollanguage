//! @file frontend.h

#ifndef MIDDLE_END
#define MIDDLE_END

//-----------------------------------------------------------------------------

#include "../include/tree.h"
#include <math.h>

//-----------------------------------------------------------------------------

Node *calc_derivative       (Node *curr_node, Tree_info *info);

bool  simplify_tree         (Node *curr_node, Tree_info *info);

bool  simplify_node         (Node *curr_node, Tree_info *info);

bool  simplify_const        (Node *curr_node, Tree_info *info);

bool  simplify_mul_div_one  (Node *curr_node, Tree_info *info);

bool  simplify_mul_div_null (Node *curr_node, Tree_info *info);

bool  simplify_add_sub_null (Node *curr_node, Tree_info *info);

//-----------------------------------------------------------------------------

#endif //MIDDLE_END
