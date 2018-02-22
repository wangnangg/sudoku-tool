#include <cstdlib>
#include <ctime>
#include "algo.hpp"

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
