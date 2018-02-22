/*
 * ./sdtool generate 200 500
 * ./sdtool count_sol [sudoku]
 * ./sdtool hint [sudoku]
 */
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include "sudoku.hpp"

class ArgException : public std::exception
{
};

void print_help()
{
    std::cout << "sdtool generate [num] [min_level] [max_level] [max_iter]"
              << std::endl;
    std::cout << "sdtool count_sol [sudoku]" << std::endl;
    std::cout << "sdtool grade [sudoku]" << std::endl;
    std::cout << "sdtool solve [sudoku]" << std::endl;
    std::cout
        << "  where [sudoku] is 81 numbers with 0 representing empty cell."
        << std::endl;
}
void print_grid(const Grid& grid)
{
    for (uint i = 0; i < dim; i++)
    {
        for (uint j = 0; j < dim; j++)
        {
            std::cout << grid(i, j);
        }
    }
}
Grid parse_grid(const std::string& str)
{
    Grid grid;
    if (str.length() != 81)
    {
        throw ArgException();
    }
    for (uint i = 0; i < str.length(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            throw ArgException();
        }
        grid(i / dim, i % dim) = (uint)(str[i] - '0');
    }
    return grid;
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            throw ArgException();
        }
        std::string action = argv[1];
        if (action == "generate")
        {
            if (argc < 6)
            {
                throw ArgException();
            }
            uint num = (uint)std::stoi(argv[2]);
            uint min_level = (uint)std::stoi(argv[3]);
            uint max_level = (uint)std::stoi(argv[4]);
            uint max_iter = (uint)std::stoi(argv[5]);
            for (uint i = 0; i < num; i++)
            {
                Grid grid = gen_puzzle(min_level, max_level, max_iter);
                auto res = grade(grid);
                std::cout << res.score << ' ';
                print_grid(grid);
                std::cout << ' ';
                solve_one(grid);
                print_grid(grid);
                std::cout << std::endl;
            }
        }
        else if (action == "count_sol")
        {
            if (argc < 3)
            {
                throw ArgException();
            }
            Grid grid = parse_grid(argv[2]);
            auto res = grade(grid);
            std::cout << res.sol_count << std::endl;
        }
        else if (action == "solve")
        {
            if (argc < 3)
            {
                throw ArgException();
            }
            Grid grid = parse_grid(argv[2]);
            solve_one(grid);
            print_grid(grid);
            std::cout << std::endl;
        }
        else if (action == "grade")
        {
            if (argc < 3)
            {
                throw ArgException();
            }
            Grid grid = parse_grid(argv[2]);
            auto res = grade(grid);
            std::cout << res.score << std::endl;
        }
        else
        {
            throw ArgException();
        }
    }
    catch (std::exception&)
    {
        print_help();
        return 1;
    }
}
