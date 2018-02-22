#pragma once
#include <cassert>
#include <iostream>
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
    GridTmpl() : _cells(dim * dim) {}
    GridTmpl(std::vector<Cell> val) : _cells(std::move(val)) {}
    GridTmpl(Cell cell_init)
    {
        for (uint i = 0; i < dim * dim; i++)
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

using Grid = GridTmpl<uint>;

std::ostream& operator<<(std::ostream& os, const Grid& grid);
Grid create_grid(const std::vector<uint>& val);

void simple_print(std::ostream& os, const Grid& grid);
