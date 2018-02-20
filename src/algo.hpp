#pragma once
#include "board.hpp"
#include "heur.hpp"

BoardNote init_note(const Board& board, const HeurList& hlist);
bool solve_one(Board& board, BoardNote& note, const HeurList& hlist);
bool solve_one(Board& board);
uint grade(Board& board, uint& sol_count);

