#include "board.hpp"

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
            if( jj % order == order - 1)
            {
                os << " | ";
            }
            if (jj % (order * order) == (order * order) - 1)
            {
                os << "\b| ";
            }
        }
        os << std::endl;
        if( ii % order == order - 1)
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
