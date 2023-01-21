//! @file frontend.h

#ifndef FRONTEND_H
#define FRONTEND_H

//-----------------------------------------------------------------------------

#include "../include/tree.h"

//-----------------------------------------------------------------------------

Node *get_grammar    (char **grammar);

Node *get_expression (char **grammar);

Node *get_mul_div    (char **grammar);

Node *get_brackets   (char **grammar);

Node *get_str        (char **grammar);

Node *get_bottom     (char **grammar);

Node *get_pow        (char **grammar);

Node *get_math_funct (char **grammar, char *name);

Node *get_assignment (char **grammar);

//-----------------------------------------------------------------------------

#endif //FRONTEND_H
