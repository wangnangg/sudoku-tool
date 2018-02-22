#include "heur.hpp"
std::ostream& operator<<(std::ostream& os, const GridNote& note)
{
    os << "----------------------------------------------------------"
       << std::endl;
    for (uint ii = 0; ii < dim * order; ii++)
    {
        os << "| ";
        uint i = ii / order;
        for (uint jj = 0; jj < dim * order; jj++)
        {
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
            if (jj % order == order - 1)
            {
                os << " | ";
            }
            if (jj % (order * order) == (order * order) - 1)
            {
                os << "\b| ";
            }
        }
        os << std::endl;
        if (ii % order == order - 1)
        {
            os << "----------------------------------------------------------"
               << std::endl;
        }
        if (ii % (order * order) == (order * order) - 1)
        {
            os << "----------------------------------------------------------"
               << std::endl;
        }
    }
    return os;
}
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

void heur_exclu(const Grid& grid, uint id, uint jd, GridNote& note)
{
    uint val = grid(id, jd);
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

void heur_single_choice(const Grid& grid, uint id, uint jd, GridNote& note)
{
    uint val = grid(id, jd);
    // row
    for (uint i = 0; i < dim; i++)
    {
        uint count = 0;
        uint last_j = 0;
        for (uint j = 0; j < dim; j++)
        {
            if (grid(i, j) == 0 && note(i, j).has(val))
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
            if (grid(i, j) == 0 && note(i, j).has(val))
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
                if (grid(i, j) == 0 && note(i, j).has(val))
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
                if (grid(i, j) == 0 && note(i, j).has(val))
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
