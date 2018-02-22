#pragma once
#include "grid.hpp"

class CellNote
{
    std::vector<bool> _poss_set;
    uint _count;

public:
    CellNote(bool full = false) : _poss_set(dim, full)
    {
        if (full)
        {
            _count = 9;
        }
        else
        {
            _count = 0;
        }
    }
    void add(uint val)
    {
        assert(val <= dim);
        if (_poss_set[val - 1])
        {
            return;
        }
        _poss_set[val - 1] = true;
        _count += 1;
    }
    void remove(uint val)
    {
        assert(val <= dim);
        if (!_poss_set[val - 1])
        {
            return;
        }
        _poss_set[val - 1] = false;
        _count -= 1;
    }
    void remove_all()
    {
        std::fill(_poss_set.begin(), _poss_set.end(), false);
        _count = 0;
    }
    bool has(uint val) const
    {
        assert(val >= 1 && val <= dim);
        return _poss_set[val - 1];
    }
    uint at(uint idx) const
    {
        for (uint i = 0; i < dim; i++)
        {
            if (_poss_set[i])
            {
                if (idx == 0)
                {
                    return i + 1;
                }
                else
                {
                    idx -= 1;
                }
            }
        }
        assert(false);
        return 0;
    }
    uint count() const { return _count; }
};

uint find_first(const CellNote& cn);
using GridNote = GridTmpl<CellNote>;

std::ostream& operator<<(std::ostream& os, const GridNote& note);

typedef void (*HeurFunc)(const Grid& grid, uint id, uint jd, GridNote& note);
using HeurList = std::vector<HeurFunc>;
void heur_exclu(const Grid& grid, uint id, uint jd, GridNote& note);
void heur_single_choice(const Grid& grid, uint id, uint jd, GridNote& note);

GridNote init_note(const Grid& grid, const HeurList& hlist);
