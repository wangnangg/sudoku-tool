#pragma once
#include "grid.hpp"
#include "heur.hpp"

GridNote init_note(const Grid& grid, const HeurList& hlist);
bool solve_one(Grid& grid, GridNote& note, const HeurList& hlist);
bool solve_one(Grid& grid);
struct GradeResult
{
    uint score;
    uint sol_count;
};
GradeResult grade(Grid grid);

Grid rand_grid_starter();

Grid rand_grid();

Grid gen_puzzle();

Grid gen_puzzle(uint min_score, uint max_iter);
