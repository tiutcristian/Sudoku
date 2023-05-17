#include "generator.h"
#include "solver.h"
#include <algorithm>
#include <vector>

using std::vector;

Board generate_completed_board()
{
    Board board;
    solve_random(board);
    return board;
}

std::vector<std::pair<int, int>> get_non_empty_positions(Board &board)
{
    std::vector<std::pair<int, int>> result;
    result.reserve(81);
    for(int l = 0; l < 9; l++)
        for(int c = 0; c < 9; c++)
            if(board.get(l, c))
                result.push_back({l, c});
    return result;
}

std::vector<std::pair<int, int>> get_positions()
{
    std::vector<std::pair<int, int>> result;
    result.reserve(81);
    for(int l = 0; l < 9; l++)
        for(int c = 0; c < 9; c++)
            result.push_back({l, c});
    return result;
}

Board generate_solveable_board(int nr_filled)
{
    while(true)
    {
        Board board = generate_completed_board();
        auto pos = get_positions();
        std::random_shuffle(pos.begin(), pos.end());

        int cnt = 0;
        for(int i = 0; i < 81 && cnt < 81-nr_filled; i++)
        {
            Board copy = board;
            copy.set(pos[i].first, pos[i].second, 0);
            auto result = solve(copy);
            if(result == REZOLVAT)
            {
                board.set(pos[i].first, pos[i].second, 0);
                cnt++;
            }
        }
        if(cnt == 81 - nr_filled)
            return board;
    }
}

Board generate(int nr_filled)
{
    while(true)
    {
        Board board = generate_solveable_board(nr_filled);
        if(board.no_complete_lcs())
            return board;
    }
}

vector<vector<int>> fill_extreme_board()
{
    vector<vector<int>> extreme_board = {
        {9, 0, 0,   0, 0, 0,   0, 6, 0},
        {0, 2, 0,   7, 0, 0,   0, 0, 0},
        {0, 0, 0,   0, 0, 0,   0, 5, 4},

        {0, 0, 0,   3, 0, 0,   7, 0, 0},
        {6, 7, 0,   0, 0, 0,   0, 0, 0},
        {5, 0, 0,   0, 0, 0,   0, 0, 0},

        {4, 0, 0,   0, 5, 9,   0, 0, 0},
        {0, 0, 8,   0, 0, 0,   3, 0, 0},
        {0, 0, 0,   0, 6, 0,   0, 0, 0}
    };
    return extreme_board;
}

void apply_random_permutation(vector<vector<int>> &v)
{
    int nr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::random_shuffle(nr+1, nr+10);
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            v[i][j] = nr[ v[i][j] ];
}

void apply_90_left_rotation(vector<vector<int>> &v)
{
    vector<vector<int>> board(9, vector<int>(9));
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board[i][j] = v[j][8-i];
    v.swap(board);
}

void apply_90_right_rotation(vector<vector<int>> &v)
{
    vector<vector<int>> board(9, vector<int>(9));
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board[i][j] = v[8-j][i];
    v.swap(board);
}

void apply_180_rotation(vector<vector<int>> &v)
{
    vector<vector<int>> board(9, vector<int>(9));
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board[i][j] = v[8-i][8-j];
    v.swap(board);
}

void apply_horizontal_flip(vector<vector<int>> &v)
{
    vector<vector<int>> board(9, vector<int>(9));
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board[i][j] = v[8-i][j];
    v.swap(board);
}

void apply_vertical_flip(vector<vector<int>> &v)
{
    vector<vector<int>> board(9, vector<int>(9));
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board[i][j] = v[i][8-j];
    v.swap(board);
}

void apply_main_diagonal_flip(vector<vector<int>> &v)
{
    vector<vector<int>> board(9, vector<int>(9));
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board[i][j] = v[j][i];
    v.swap(board);
}

void apply_secondary_diagonal_flip(vector<vector<int>> &v)
{
    vector<vector<int>> board(9, vector<int>(9));
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board[i][j] = v[8-j][8-i];
    v.swap(board);
}

Board generate_extreme()
{
    vector<vector<int>> extreme_board = fill_extreme_board();
    apply_random_permutation(extreme_board);
    int var = std::rand() % 8;

    switch (var) {
    case 0:
        apply_90_left_rotation(extreme_board);
        break;
    case 1:
        apply_90_right_rotation(extreme_board);
        break;
    case 2:
        apply_180_rotation(extreme_board);
        break;
    case 3:
        apply_horizontal_flip(extreme_board);
        break;
    case 4:
        apply_vertical_flip(extreme_board);
        break;
    case 5:
        apply_main_diagonal_flip(extreme_board);
        break;
    case 6:
        apply_secondary_diagonal_flip(extreme_board);
        break;
    default:
        break;
    }

    Board board;
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            board.set(i, j, extreme_board[i][j]);
    return board;
}
