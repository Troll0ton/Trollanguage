//! @file frontend.h

#ifndef FRONTEND_H
#define FRONTEND_H

//-----------------------------------------------------------------------------

#include "../include/tree.h"

//-----------------------------------------------------------------------------

Node *get_grammar    (char **grammar, Tree_info *info);

Node *get_condition  (char **grammar, Tree_info *info);

Node *get_if_body    (char **grammar, Tree_info *info);

Node *get_else_body  (char **grammar, Tree_info *info);

Node *get_cycle      (char **grammar, Tree_info *info);

Node *get_funct_init (char **grammar, Tree_info *info);

Node *get_funct_body (char **grammar, Tree_info *info);

Node *get_expression (char **grammar);

Node *get_mul_div    (char **grammar);

Node *get_brackets   (char **grammar);

Node *get_str        (char **grammar);

Node *get_bottom     (char **grammar);

Node *get_pow        (char **grammar);

Node *get_math_funct (char **grammar, char *name);

Node *get_assignment (char **grammar);

Node *get_sequence   (Tree_info *info);

//-----------------------------------------------------------------------------

#endif //FRONTEND_H
