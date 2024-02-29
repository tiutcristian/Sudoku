#include "solver.h"
#include <utility>
#include <algorithm>

struct stare_e
{
    bool continua;
    bool incompatibil;
};

stare_e completare_e1(Board &board)
{
    stare_e stare = {false, false};
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board.get(i, j) == 0)
            {
                int p = board.get_posib(i, j);
                if(p == 0)
                    return {.continua = false, .incompatibil = true};
                else if( (p & (p-1)) == 0 ) // are un singur bit de 1
                {
                    board.set(i, j, Board::bit2nr(p));
                    stare.continua = true;
                }
            }
    return stare;
}

stare_e completare_e2(Board &board)
{
    stare_e stare = {false, false};
    for(int l = 0; l < 9; l++)
    {
        int bitmask = (1<<9) - 1;
        for(int c = 0; c < 9; c++)
            if(board.get(l, c))
                bitmask &= ~Board::nr2bit(board.get(l, c));
        for(int nr = 1; nr <= 9; nr++)
            if(bitmask & Board::nr2bit(nr))
            {
                int nrLocuri = 0;
                int loc;
                for(int j = 0; j < 9; j++)
                    if(board.get(l, j) == 0 && board.is_posib(l, j, nr))
                    {
                        nrLocuri++;
                        loc = j;
                    }
                if(nrLocuri == 0)
                    return {.continua = false, .incompatibil = true};
                else if(nrLocuri == 1)
                {
                    board.set(l, loc, nr);
                    stare.continua = true;
                }
            }
    }
    for(int c = 0; c < 9; c++)
    {
        int bitmask = (1<<9) - 1;
        for(int l = 0; l < 9; l++)
            if(board.get(l, c))
                bitmask &= ~Board::nr2bit(board.get(l, c));
        for(int nr = 1; nr <= 9; nr++)
            if(bitmask & Board::nr2bit(nr))
            {
                int nrLocuri = 0;
                int loc;
                for(int i = 0; i < 9; i++)
                    if(board.get(i, c) == 0 && board.is_posib(i, c, nr))
                    {
                        nrLocuri++;
                        loc = i;
                    }
                if(nrLocuri == 0)
                    return {.continua = false, .incompatibil = true};
                else if(nrLocuri == 1)
                {
                    board.set(loc, c, nr);
                    stare.continua = true;
                }
            }
    }
    for(int ls = 0; ls < 9; ls += 3)
        for(int cs = 0; cs < 9; cs += 3)
        {
            int bitmask = (1<<9) - 1;
            for(int l = ls; l <= ls+2; l++)
                for(int c = cs; c <= cs+2; c++)
                    if(board.get(l, c))
                        bitmask &= ~Board::nr2bit(board.get(l, c));

            for(int nr = 1; nr <= 9; nr++)
                if(bitmask & Board::nr2bit(nr))
                {
                    int nrLocuri = 0;
                    std::pair<int,int> loc;
                    for(int l = ls; l <= ls+2; l++)
                        for(int c = cs; c <= cs+2; c++)
                            if(board.get(l, c) == 0 && board.is_posib(l, c, nr))
                            {
                                nrLocuri++;
                                loc = {l, c};
                            }
                    if(nrLocuri == 0)
                        return {.continua = false, .incompatibil = true};
                    else if(nrLocuri == 1)
                    {
                        board.set(loc.first, loc.second, nr);
                        stare.continua = true;
                    }
                }
        }
    return stare;
}

bool completare_e(Board &board)
{
    while(true)
    {
        stare_e s1 = completare_e1(board);
        if(s1.incompatibil)
            return false;
        else if(s1.continua)
            continue;

        stare_e s2 = completare_e2(board);
        if(s2.incompatibil)
            return false;

        if(s2.continua == false)
            break;
    }
    return true;
}

void backtracking(int i, int j, Board &board, Board &board_sol, int & sol)
{
    for(int nr = 1; nr <= 9; nr++)
        if(board.is_posib(i, j, nr))
        {
            Board board2 = board;
            board2.set(i, j, nr);
            bool ok = completare_e(board2);
            if(!ok)
                continue;
            if(board2.is_complete())
            {
                ++sol;
                if(sol == 1)
                    board_sol.swap(board2);
                if(sol >= 2)
                    return;
            }
            else
            {
                int i2 = i;
                int j2 = j;
                do
                {
                    if(j2 < 8)
                        j2++;
                    else
                    {
                        i2++;
                        j2 = 0;
                    }
                }
                while(board2.get(i2, j2));

                backtracking(i2, j2, board2, board_sol, sol);

                if(sol >= 2)
                    return;
            }
        }
}

void backtracking_random(int i, int j, Board &board, Board &board_sol, int & sol)
{
    int numbers[9];
    for (int i = 0; i < 9; ++i)
        numbers[i] = i+1;
    std::random_shuffle(numbers, numbers+9);

    for(int nri = 0; nri < 9; nri++)
    {
        int nr = numbers[nri];
        if(board.is_posib(i, j, nr))
        {
            Board board2 = board;
            board2.set(i, j, nr);
            bool ok = completare_e(board2);
            if(!ok)
                continue;
            if(board2.is_complete())
            {
                ++sol;
                board_sol.swap(board2);
                return;
            }
            else
            {
                int i2 = i;
                int j2 = j;
                do
                {
                    if(j2 < 8)
                        j2++;
                    else
                    {
                        i2++;
                        j2 = 0;
                    }
                }
                while(board2.get(i2, j2));

                backtracking(i2, j2, board2, board_sol, sol);

                if(sol >= 1)
                    return;
            }
        }
    }
}

solver_result solve(Board &board)
{
    bool ok = completare_e(board);
    if (!ok)
        return solver_result::IMPOSIBIL;
    else if (board.is_complete())
        return solver_result::REZOLVAT;
    else
    {
        int l = 0;
        int c = 0;
        while(board.get(l, c))
            if(c < 8)
                c++;
            else if(l < 8)
            {
                l++;
                c = 0;
            }
        int sol = 0;
        Board board_sol;
        backtracking(l, c, board, board_sol, sol);
        if(sol == 0)
            return solver_result::IMPOSIBIL;
        else
        {
            board.swap(board_sol);
            if(sol == 1)
                return solver_result::REZOLVAT;
            else
                return solver_result::NEDETERMINAT;
        }
    }
}

solver_result solve_random(Board &board)
{
    bool ok = completare_e(board);
    if (!ok)
        return solver_result::IMPOSIBIL;
    else if (board.is_complete())
        return solver_result::REZOLVAT;
    else
    {
        int l = 0;
        int c = 0;
        while(board.get(l, c))
            if(c < 8)
                c++;
            else if(l < 8)
            {
                l++;
                c = 0;
            }
        int sol = 0;
        Board board_sol;
        backtracking_random(l, c, board, board_sol, sol);
        if(sol == 0)
            return solver_result::IMPOSIBIL;
        else
        {
            board.swap(board_sol);
            if(sol == 1)
                return solver_result::REZOLVAT;
            else
                return solver_result::NEDETERMINAT;
        }
    }
}
