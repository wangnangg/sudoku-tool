#include "algo.hpp"
#include <cstdlib>
#include <ctime>
GridNote init_note(const Grid& grid, const HeurList& hlist)
{
    GridNote note;
    for (uint i = 0; i < dim; i++)
    {
        for (uint j = 0; j < dim; j++)
        {
            if (grid(i, j) == 0)
            {
                note(i, j) = CellNote(true);
            }
        }
    }
    for (const auto& h : hlist)
    {
        for (uint i = 0; i < dim; i++)
        {
            for (uint j = 0; j < dim; j++)
            {
                if (grid(i, j) != 0)
                {
                    h(grid, i, j, note);
                }
            }
        }
    }

    return note;
}

uint find_first(const CellNote& cn)
{
    for (uint i = 1; i <= dim; i++)
    {
        if (cn.has(i))
        {
            return i;
        }
    }
    return 0;
}

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

class SolutionRecord
{
public:
    struct Node
    {
        std::vector<uint> children;
    };

private:
    std::vector<Node> _node_list;

public:
    SolutionRecord() : _node_list(1) {}
    uint add_child(uint parent)
    {
        uint nid = _node_list.size();
        _node_list.push_back(Node{});
        _node_list[parent].children.push_back(nid);
        return nid;
    }
    const std::vector<uint>& children(uint nid) const
    {
        return _node_list[nid].children;
    }
    uint root() const { return 0; }
    uint node_count() const { return _node_list.size(); }
};

uint record_solution(Grid& grid, GridNote& note, const HeurList& hlist,
                     SolutionRecord& record, uint nid)
{
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
                    return 0;  // no solution is possible
                }
                else if (note(i, j).count() == 1)
                {
                    // simple case
                    grid(i, j) = find_first(note(i, j));
                    for (const auto& h : hlist)
                    {
                        h(grid, i, j, note);
                    }
                    uint child = record.add_child(nid);
                    return record_solution(grid, note, hlist, record, child);
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
        return 1;
    }

    const Grid saved_grid = grid;
    const GridNote saved_note = note;
    const auto& cellnote = saved_note(min_i, min_j);
    // try every possible values
    uint sol_count = 0;
    for (uint k = 1; k <= dim; k++)
    {
        if (cellnote.has(k))
        {
            grid(min_i, min_j) = k;
            for (const auto& h : hlist)
            {
                h(grid, min_i, min_j, note);
            }

            uint child = record.add_child(nid);
            sol_count += record_solution(grid, note, hlist, record, child);
            grid = saved_grid;
            note = saved_note;
        }
    }
    return sol_count;
}
GradeResult grade(Grid grid)
{
    SolutionRecord record;
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(grid, hlist);
    uint sol_count = record_solution(grid, note, hlist, record, record.root());
    return {record.node_count(), sol_count};
}

bool srand_init = false;
uint randint(uint N)
{
    assert(N > 0);
    if (!srand_init)
    {
        std::srand(time(nullptr));
        srand_init = true;
    }
    return (uint)std::rand() % N;
}

void permute(std::vector<uint>& val)
{
    for (uint i = 0; i < val.size() - 1; i++)
    {
        uint j = randint(val.size() - i) + i;
        std::swap(val[i], val[j]);
    }
}

// only works for 3 * 3
Grid rand_grid_starter()
{
    Grid grid;
    // box 1
    for (uint i = 0; i < order; i++)
    {
        for (uint j = 0; j < order; j++)
        {
            grid(i, j) = i * order + j + 1;
        }
    }

    // box 2, row 1
    std::vector<uint> vals = std::vector<uint>{4, 5, 6, 7, 8, 9};
    permute(vals);
    for (uint j = order; j < 2 * order; j++)
    {
        grid(0, j) = vals[j - order];
    }
    // box 2, row 2, row 3
    uint row1_val = 1;
    std::vector<uint> row2_vals;
    std::vector<uint> row3_vals;
    for (uint j = order; j < 2 * order; j++)
    {
        if (vals[j] <= 6)
        {
            row2_vals.push_back(row1_val);
            row3_vals.push_back(vals[j]);
        }
        else
        {
            row3_vals.push_back(row1_val);
            row2_vals.push_back(vals[j]);
        }
        row1_val += 1;
    }
    permute(row2_vals);
    permute(row3_vals);
    for (uint k = 0; k < order; k++)
    {
        grid(1, k + order) = row2_vals[k];
        grid(2, k + order) = row3_vals[k];
    }
    // box 3
    for (uint i = 0; i < order; i++)
    {
        CellNote cnote(true);
        for (uint j = 0; j < 2 * order; j++)
        {
            cnote.remove(grid(i, j));
        }
        std::vector<uint> rval;
        for (uint k = 1; k <= dim; k++)
        {
            if (cnote.has(k))
            {
                rval.push_back(k);
            }
        }
        permute(rval);
        for (uint j = 2 * order; j < order * order; j++)
        {
            grid(i, j) = rval[j - 2 * order];
        }
    }
    // first col
    auto col_vals = std::vector<uint>({2, 3, 5, 6, 8, 9});
    permute(col_vals);
    for (uint i = order; i < dim; i++)
    {
        grid(i, 0) = col_vals[i - order];
    }
    // relabeling
    auto label = std::vector<uint>({1, 2, 3, 4, 5, 6, 7, 8, 9});
    permute(label);
    for (uint i = 0; i < dim; i++)
    {
        for (uint j = 0; j < dim; j++)
        {
            if (grid(i, j) > 0)
            {
                grid(i, j) = label[grid(i, j) - 1];
            }
        }
    }
    return grid;
}

bool rand_fill_grid(Grid& grid, GridNote& note, const HeurList& hlist)
{
    uint min_i = 0;
    uint min_j = 0;
    uint min = dim + 1;

    std::vector<uint> li;
    std::vector<uint> lj;
    for (uint k = 0; k < dim; k++)
    {
        li.push_back(k);
        lj.push_back(k);
    }
    permute(li);
    permute(lj);
    for (uint ii = 0; ii < dim; ii++)
    {
        uint i = li[ii];
        for (uint jj = 0; jj < dim; jj++)
        {
            uint j = lj[jj];
            if (grid(i, j) == 0)
            {
                if (note(i, j).count() == 0)
                {
                    return false;  // no filling is possible
                }
                else if (note(i, j).count() == 1)
                {
                    // simple case
                    grid(i, j) = find_first(note(i, j));
                    for (const auto& h : hlist)
                    {
                        h(grid, i, j, note);
                    }
                    return rand_fill_grid(grid, note, hlist);
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
        return true;
    }

    const Grid saved_grid = grid;
    const GridNote saved_note = note;
    const auto& cellnote = saved_note(min_i, min_j);
    // try every possible values
    auto vals = std::vector<uint>();
    for (uint k = 1; k <= dim; k++)
    {
        if (cellnote.has(k))
        {
            vals.push_back(k);
        }
    }
    permute(vals);
    for (auto k : vals)
    {
        grid(min_i, min_j) = k;
        for (const auto& h : hlist)
        {
            h(grid, min_i, min_j, note);
        }
        if (rand_fill_grid(grid, note, hlist))
        {
            return true;
        }
        grid = saved_grid;
        note = saved_note;
    }
    return false;
}

Grid rand_grid()
{
    Grid grid = rand_grid_starter();
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(grid, hlist);
    rand_fill_grid(grid, note, hlist);
    return grid;
}

//0: no solution, 1: single solution 2: more than one
uint is_proper_puzzle(Grid& grid, GridNote& note, const HeurList& hlist)
{
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
                    return 0;  // no solution is possible
                }
                else if (note(i, j).count() == 1)
                {
                    // simple case
                    grid(i, j) = find_first(note(i, j));
                    for (const auto& h : hlist)
                    {
                        h(grid, i, j, note);
                    }
                    return is_proper_puzzle(grid, note, hlist);
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
        return 1;
    }

    const Grid saved_grid = grid;
    const GridNote saved_note = note;
    const auto& cellnote = saved_note(min_i, min_j);
    // try every possible values
    uint sol_count = 0;
    for (uint k = 1; k <= dim; k++)
    {
        if (cellnote.has(k))
        {
            grid(min_i, min_j) = k;
            for (const auto& h : hlist)
            {
                h(grid, min_i, min_j, note);
            }
            sol_count += is_proper_puzzle(grid, note, hlist);
            if(sol_count >= 2)
            {
                break;
            }
            grid = saved_grid;
            note = saved_note;
        }
    }
    return sol_count;
}

uint is_proper_puzzle(Grid grid)
{
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(grid, hlist);
    return is_proper_puzzle(grid, note, hlist);
}

Grid gen_puzzle()
{
    Grid grid = rand_grid();
    auto perm = std::vector<uint>();
    for (uint i = 0; i < dim * dim; i++)
    {
        perm.push_back(i);
    }
    permute(perm);
    for (uint kk = 0; kk < perm.size(); kk++)
    {
        uint k = perm[kk];
        uint i = k / dim;
        uint j = k % dim;
        uint saved_val = grid(i, j);
        grid(i, j) = 0;
        auto sol_count = is_proper_puzzle(grid);
        assert(sol_count > 0);
        if (sol_count != 1)
        {
            grid(i, j) = saved_val;
        }
    }
    return grid;
}


Grid gen_puzzle(uint min_score, uint max_iter)
{
    const Grid sol_grid = rand_grid();
    auto perm = std::vector<uint>();
    for (uint i = 0; i < dim * dim; i++)
    {
        perm.push_back(i);
    }
    Grid best;
    uint best_s = 0;
    for(uint i = 0; i < max_iter; i++)
    {
        permute(perm);
        Grid grid = sol_grid;
        for (uint kk = 0; kk < perm.size(); kk++)
        {
            uint k = perm[kk];
            uint i = k / dim;
            uint j = k % dim;
            uint saved_val = grid(i, j);
            grid(i, j) = 0;
            auto sol_count = is_proper_puzzle(grid);
            assert(sol_count > 0);
            if (sol_count != 1)
            {
                grid(i, j) = saved_val;
            }
        }
        auto res = grade(grid);
        if(res.score > best_s)
        {
            best = grid;
            best_s = res.score;
        }
        if(best_s >= min_score)
        {
            break;
        }
    }
    return best;
}
