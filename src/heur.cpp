#include "heur.hpp"

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
