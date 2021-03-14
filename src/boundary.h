#ifndef BOUNDARY_H
#define BOUNDARY_H
#include<vector>
class Boundary
{
private:
    std::size_t top_row;
    std::size_t bot_row;
    std::size_t lft_col;
    std::size_t rgt_col;
public:
    std::size_t Top_row(){return top_row;}
    std::size_t Bot_row(){return bot_row;}
    std::size_t Lft_col(){return lft_col;}
    std::size_t Rgt_col(){return rgt_col;}
    void Top_row(std::size_t tp_row){top_row = tp_row;} 
    void Bot_row(std::size_t bt_row){bot_row = bt_row;}
    void Lft_col(std::size_t lt_col){lft_col = lt_col;}
    void Rgt_col(std::size_t rt_col){rgt_col = rt_col;}
    bool BoundaryCell(int x,int y);
};
#endif