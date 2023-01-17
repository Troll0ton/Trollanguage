//! @file differentiator.h

#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

//-----------------------------------------------------------------------------

#include "../include/tree.h"
#include "../include/frontend.h"
#include "../include/middleend.h"
#include "../include/common.h"

//-----------------------------------------------------------------------------

#define trprint(...) fprintf (Info->file_tree, __VA_ARGS__

//-----------------------------------------------------------------------------

enum MODES
{
    CALC_POINT,
    CALC_DERIV,
    CALC_DERIV_POINT,
};

//-----------------------------------------------------------------------------

void  print_expression     (Tree_info *info);

void  print_derivative     (Tree_info *info);

void  print_simplified     (Tree_info *info);

void  calc_in_point_mode   (Tree_info *info);

void  calc_derivative_mode (Tree_info *info);

void  choose_mode          (Tree_info *info);

//-----------------------------------------------------------------------------

#endif //DIFFERENTIATOR_H
