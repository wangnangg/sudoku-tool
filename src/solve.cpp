#include <cstdlib>
#include <ctime>
#include "algo.hpp"
bool solve_one(Grid& grid, GridNote& note, const HeurList& hlist)
{
#ifndef NDEBUG
    std::cout << grid << std::endl;
    std::cout << note << std::endl;
#endif
    uint min_i = 0;
    uint min_j = 0;
    uint min = dim + 1;
    for (uint i = 0; i < dim; i++)
    {
        for (uint j = 0; j < dim; j++)
        {
            if (grid(i, j) == 0)
            {
                if (note(i, j).count() == 0)
                {
                    return false;  // no solution is possible
                }
                else if (note(i, j).count() == 1)
                {
                    // simple case
                    grid(i, j) = find_first(note(i, j));
                    for (const auto& h : hlist)
                    {
                        h(grid, i, j, note);
                    }
                    return solve_one(grid, note, hlist);
                }
                else
                {
                    if (min > note(i, j).count())
                    {
                        min = note(i, j).count();
                        min_i = i;
                        min_j = j;
                    }
                }
            }
        }
    }
    if (min == dim + 1)
    {
        // solved
        return true;
    }

    const Grid saved_grid = grid;
    const GridNote saved_note = note;
    const auto& cellnote = saved_note(min_i, min_j);
    // try every possible values
    for (uint k = 1; k <= dim; k++)
    {
        if (cellnote.has(k))
        {
            grid(min_i, min_j) = k;
            for (const auto& h : hlist)
            {
                h(grid, min_i, min_j, note);
            }
            if (solve_one(grid, note, hlist))
            {
                return true;
            }
            grid = saved_grid;
            note = saved_note;
        }
    }
    return false;
}

bool solve_one(Grid& grid)
{
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(grid, hlist);
    return solve_one(grid, note, hlist);
}
