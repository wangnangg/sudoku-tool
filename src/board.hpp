#pragma once
#include <vector>
#include <iostream>
#include <cassert>
#include <vector>

const uint order = 3;
const uint dim = order * order;

template <typename CELL>
class BoardTmpl
{
public:
    using Cell = CELL;
private:
    std::vector<Cell> _cells;
public:
    BoardTmpl(): _cells(dim * dim) {}
    BoardTmpl(std::vector<Cell> val) : _cells(std::move(val)) {}
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
    uint count() const
    {
        return _count;
    }
};



using Board = BoardTmpl<uint>;
using BoardNote = BoardTmpl<CellNote>;


std::ostream& operator<<(std::ostream& os, const Board& board);
std::ostream& operator<<(std::ostream& os, const BoardNote& note);
Board create_board(const std::vector<uint>& val);
