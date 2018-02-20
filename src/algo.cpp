#include "algo.hpp"

BoardNote init_note(const Board& board, const HeurList& hlist)
{
    BoardNote note;
    for (uint i = 0; i < dim; i++)
    {
        for (uint j = 0; j < dim; j++)
        {
            if (board(i, j) == 0)
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
                if (board(i, j) != 0)
                {
                    h(board, i, j, note);
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

bool solve_one(Board& board, BoardNote& note, const HeurList& hlist)
{
#ifndef NDEBUG
    std::cout << board << std::endl;
    std::cout << note << std::endl;
#endif
    uint min_i = 0;
    uint min_j = 0;
    uint min = dim + 1;
    for (uint i = 0; i < dim; i++)
    {
        for (uint j = 0; j < dim; j++)
        {
            if (board(i, j) == 0)
            {
                if (note(i, j).count() == 0)
                {
                    return false;  // no solution is possible
                }
                else if (note(i, j).count() == 1)
                {
                    // simple case
                    board(i, j) = find_first(note(i, j));
                    for (const auto& h : hlist)
                    {
                        h(board, i, j, note);
                    }
                    return solve_one(board, note, hlist);
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

    const Board saved_board = board;
    const BoardNote saved_note = note;
    const auto& cellnote = saved_note(min_i, min_j);
    // try every possible values
    for (uint k = 1; k <= dim; k++)
    {
        if (cellnote.has(k))
        {
            board(min_i, min_j) = k;
            for (const auto& h : hlist)
            {
                h(board, min_i, min_j, note);
            }
            if (solve_one(board, note, hlist))
            {
                return true;
            }
            board = saved_board;
            note = saved_note;
        }
    }
    return false;
}

bool solve_one(Board& board)
{
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(board, hlist);
    return solve_one(board, note, hlist);
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
    uint node_count() const {return _node_list.size(); }
};

uint record_solution(Board& board, BoardNote& note, const HeurList& hlist,
                     SolutionRecord& record, uint nid)
{
    uint min_i = 0;
    uint min_j = 0;
    uint min = dim + 1;
    for (uint i = 0; i < dim; i++)
    {
        for (uint j = 0; j < dim; j++)
        {
            if (board(i, j) == 0)
            {
                if (note(i, j).count() == 0)
                {
                    return 0;  // no solution is possible
                }
                else if (note(i, j).count() == 1)
                {
                    // simple case
                    board(i, j) = find_first(note(i, j));
                    for (const auto& h : hlist)
                    {
                        h(board, i, j, note);
                    }
                    uint child = record.add_child(nid);
                    return record_solution(board, note, hlist, record, child);
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

    const Board saved_board = board;
    const BoardNote saved_note = note;
    const auto& cellnote = saved_note(min_i, min_j);
    // try every possible values
    uint sol_count = 0;
    for (uint k = 1; k <= dim; k++)
    {
        if (cellnote.has(k))
        {
            board(min_i, min_j) = k;
            for (const auto& h : hlist)
            {
                h(board, min_i, min_j, note);
            }

            uint child = record.add_child(nid);
            sol_count += record_solution(board, note, hlist, record, child);
            board = saved_board;
            note = saved_note;
        }
    }
    return sol_count;
}
uint grade(Board& board, uint& sol_count)
{
    SolutionRecord record;
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(board, hlist);
    sol_count = record_solution(board, note, hlist, record, record.root());
    return record.node_count();
}
