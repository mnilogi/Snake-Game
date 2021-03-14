#include "boundary.h"
bool Boundary::BoundaryCell(int x,int y){
        if(x == lft_col || x == rgt_col)
            return true;
        else if(y == top_row || y == bot_row)
            return true;
        else 
            return false;
    }