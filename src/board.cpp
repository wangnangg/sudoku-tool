#include "board.hpp"

void heur_exclu(const Board& board, uint id, uint jd, BoardNote& note)
{
    uint val = board(id, jd);
    for (uint k = 0; k < dim; k++)
    {
        note(id, k).remove(val);
        note(k, jd).remove(val);
    }
    for (uint i = 0; i < order; i++)
    {
        for (uint j = 0; j < order; j++)
        {
            note(id / order * order + i, jd / order * order + j).remove(val);
        }
    }
}

void heur_single_choice(const Board& board, uint id, uint jd, BoardNote& note)
{
    uint val = board(id, jd);
    // row
    for (uint i = 0; i < dim; i++)
    {
        uint count = 0;
        uint last_j = 0;
        for (uint j = 0; j < dim; j++)
        {
            if (board(i, j) == 0 && note(i, j).has(val))
            {
                last_j = j;
                count += 1;
            }
        }
        if (count == 1 && note(i, last_j).count() > 1)
        {
            note(i, last_j).remove_all();
            note(i, last_j).add(val);
        }
    }
    // col
    for (uint j = 0; j < dim; j++)
    {
        uint count = 0;
        uint last_i = 0;
        for (uint i = 0; i < dim; i++)
        {
            if (board(i, j) == 0 && note(i, j).has(val))
            {
                last_i = i;
                count += 1;
            }
        }
        if (count == 1 && note(last_i, j).count() > 1)
        {
            note(last_i, j).remove_all();
            note(last_i, j).add(val);
        }
    }
    // box
    uint vbi = id / 3;
    uint vbj = jd / 3;
    // box row
    for (uint bj = 0; bj < order; bj++)
    {
        if (vbj == bj)
        {
            continue;
        }
        uint count = 0;
        uint last_i = 0;
        uint last_j = 0;
        for (uint ii = 0; ii < order; ii++)
        {
            for (uint jj = 0; jj < order; jj++)
            {
                uint i = vbi * order + ii;
                uint j = bj * order + jj;
                if (board(i, j) == 0 && note(i, j).has(val))
                {
                    last_i = i;
                    last_j = j;
                    count += 1;
                }
            }
        }
        if (count == 1 && note(last_i, last_j).count() > 1)
        {
            note(last_i, last_j).remove_all();
            note(last_i, last_j).add(val);
        }
    }
    // box col
    for (uint bi = 0; bi < order; bi++)
    {
        if (vbi == bi)
        {
            continue;
        }
        uint count = 0;
        uint last_i = 0;
        uint last_j = 0;
        for (uint ii = 0; ii < order; ii++)
        {
            for (uint jj = 0; jj < order; jj++)
            {
                uint i = bi * order + ii;
                uint j = vbj * order + jj;
                if (board(i, j) == 0 && note(i, j).has(val))
                {
                    last_i = i;
                    last_j = j;
                    count += 1;
                }
            }
        }
        if (count == 1 && note(last_i, last_j).count() > 1)
        {
            note(last_i, last_j).remove_all();
            note(last_i, last_j).add(val);
        }
    }
}

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

std::ostream& operator<<(std::ostream& os, const Board& board)
{
    os << "-----------------------------------" << std::endl;
    for (uint i = 0; i < dim; i++)
    {
        os << "| ";
        for (uint j = 0; j < dim; j++)
        {
            os << ' ' << board(i, j) << ' ';
            if (j % order == order - 1)
            {
                os << " |";
            }
        }
        os << std::endl;
        if (i % order == order - 1)
        {
            os << "-----------------------------------" << std::endl;
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const BoardNote& note)
{
    os << "--------------------------------------------------------------------"
          "---------------------------"
       << std::endl;
    for (uint ii = 0; ii < dim * order; ii++)
    {
        os << "| ";
        uint i = ii / order;
        for (uint jj = 0; jj < dim * order; jj++)
        {
            os << ' ';
            uint j = jj / order;
            uint bi = ii % order;
            uint bj = jj % order;
            uint val = bi * order + bj + 1;
            if (note(i, j).has(val))
            {
                os << val;
            }
            else
            {
                os << ' ';
            }
            os << ' ';
            if( jj % order == order - 1)
            {
                os << "|";
            }
            if (jj % (order * order) == (order * order) - 1)
            {
                os << "|";
            }
        }
        os << std::endl;
        if( ii % order == order - 1)
        {
            os << "--------------------------------------------------------------------"
                "---------------------------"
               << std::endl;
        }
        if (ii % (order * order) == (order * order) - 1)
        {
            os << "--------------------------------------------------------------------"
                "---------------------------"
               << std::endl;
        }
    }
    return os;
}
