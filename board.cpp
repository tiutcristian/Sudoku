#include "board.h"
#include <utility>

Board::Board() : nr_zero(9*9)  
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            val[i][j] = 0;
    for (int i = 0; i < 9; i++)
        bitmask_line[i] = bitmask_col[i] = bitmask_square[i] = 0;
}

void Board::set(int l, int c, int v)
{
    int old = val[l][c];

    if (old == v)
        return;

    if (old != 0)
    {
        val[l][c] = 0;
        int oldbit = nr2bit(old);

        bitmask_line[l] -= oldbit;
        bitmask_col[c] -= oldbit;
        bitmask_square[l/3*3 + c/3] -= oldbit;

        nr_zero++;
    }

    if (v != 0)
    {
        nr_zero--;

        int vbit = nr2bit(v);
        val[l][c] = v;

        bitmask_line[l] += vbit;
        bitmask_col[c] += vbit;
        bitmask_square[l/3*3 + c/3] += vbit;
    }
}

int Board::get_nr_posib(int l, int c)
{
    int nr = 0, p = get_posib(l,c);
    while (p != 0)
    {
        nr++;
        p &= (p-1);
    }
    return nr;
}

int Board::bit2nr(int bit)
{
    for(int nr = 1; nr <= 9; nr++)
        if(bit & (1 << (nr-1)))
            return nr;
    return 0;
}

void Board::swap(Board &other)
{
    for(int l = 0; l < 9; l++)
        for(int c = 0; c < 9; c++)
            std::swap(val[l][c], other.val[l][c]);

    std::swap(nr_zero, other.nr_zero);

    for(int i = 0; i < 9; i++)
    {
        std::swap(bitmask_line[i], other.bitmask_line[i]);
        std::swap(bitmask_col[i], other.bitmask_col[i]);
        std::swap(bitmask_square[i], other.bitmask_square[i]);
    }
}

bool Board::no_complete_lcs()
{
    int val = (1<<9) - 1;
    for(int i = 0; i < 9; i++)
        if(bitmask_col[i] == val || bitmask_line[i] == val || bitmask_square[i] == val)
            return false;
    return true;
}
