#pragma once
#include <vector>
#include <iostream>
#include <cassert>
#include <vector>

const uint order = 3;
const uint dim = order * order;

template <typename CELL>
class GridTmpl
{
public:
    using Cell = CELL;
private:
    std::vector<Cell> _cells;
public:
    GridTmpl(): _cells(dim * dim) {}
    GridTmpl(std::vector<Cell> val) : _cells(std::move(val)) {}
    GridTmpl(Cell cell_init)
    {
        for(uint i=0; i<dim*dim; i++)
        {
            _cells.push_back(cell_init);
        }
    }
    const Cell& operator()(size_t i, size_t j) const
    {
        assert(i < dim);
        assert(j < dim);
        return _cells[i * dim + j];
    }
    Cell& operator()(size_t i, size_t j)
    {
        assert(i < dim);
        assert(j < dim);
        return _cells[i * dim + j];
    }
};

class CellNote
{
    std::vector<bool> _poss_set;
    uint _count;
public:
    CellNote(bool full = false) : _poss_set(dim, full)
    {
        if(full)
        {
            _count = 9;
        } else {
            _count = 0;
        }
    }
    void add(uint val)
    {
        assert(val <= dim);
        if(_poss_set[val - 1])
        {
            return;
        }
        _poss_set[val - 1] = true;
        _count += 1;
    }
    void remove(uint val)
    {
        assert(val <= dim);
        if(!_poss_set[val - 1])
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
        for(uint i=0; i<dim; i++)
        {
            if(_poss_set[i])
            {
                if(idx == 0)
                {
                    return i + 1;
                } else {
                    idx -= 1;
                }
            }
        }
        assert(false);
        return 0;
    }
    uint count() const
    {
        return _count;
    }
};



using Grid = GridTmpl<uint>;
using GridNote = GridTmpl<CellNote>;


std::ostream& operator<<(std::ostream& os, const Grid& grid);
std::ostream& operator<<(std::ostream& os, const GridNote& note);
Grid create_grid(const std::vector<uint>& val);

void simple_print(std::ostream& os,  const Grid& grid);
