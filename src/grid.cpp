#include "grid.hpp"

std::ostream& operator<<(std::ostream& os, const Grid& grid)
{
    os << "-----------------------------------" << std::endl;
    for (uint i = 0; i < dim; i++)
    {
        os << "| ";
        for (uint j = 0; j < dim; j++)
        {
            os << ' ' << grid(i, j) << ' ';
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

void simple_print(std::ostream& os, const Grid& grid)
{
    for (uint i = 0; i < dim; i++)
    {
        for (uint j = 0; j < dim; j++)
        {
            if (grid(i, j) == 0)
            {
                os << '_' << ' ';
            }
            else
            {
                os << grid(i, j) << ' ';
            }
        }
        os << std::endl;
    }
}
