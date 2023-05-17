#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"

enum solver_result { IMPOSIBIL, REZOLVAT, NEDETERMINAT };
solver_result solve(Board &board);
solver_result solve_random(Board &board);

#endif // SOLVER_H
