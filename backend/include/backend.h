//! @file backend.h

#ifndef BACKEND_H
#define BACKEND_H

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

Node *get_funct      (char **grammar, char *name);

//-----------------------------------------------------------------------------

#endif //BACKEND_H
