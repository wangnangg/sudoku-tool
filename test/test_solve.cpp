#include <gtest/gtest.h>
#include "sudoku.hpp"

TEST(test_solve, print_grid)
{
    Grid grid({
        5, 3, 0, 0, 7, 0, 0, 0, 0,  //
        6, 0, 0, 1, 9, 5, 0, 0, 0,  //
        0, 9, 8, 0, 0, 0, 0, 6, 0,  //
        8, 0, 0, 0, 6, 0, 0, 0, 3,  //
        4, 0, 0, 8, 0, 3, 0, 0, 1,  //
        7, 0, 0, 0, 2, 0, 0, 0, 6,  //
        0, 6, 0, 0, 0, 0, 2, 8, 0,  //
        0, 0, 0, 4, 1, 9, 0, 0, 5,  //
        0, 0, 0, 0, 8, 0, 0, 7, 9   //

    });
    std::cout << grid << std::endl;
}

TEST(test_solve, print_grid_heur)
{
    Grid grid({
        5, 3, 0, 0, 7, 0, 0, 0, 0,  //
        6, 0, 0, 1, 9, 5, 0, 0, 0,  //
        0, 9, 8, 0, 0, 0, 0, 6, 0,  //
        8, 0, 0, 0, 6, 0, 0, 0, 3,  //
        4, 0, 0, 8, 0, 3, 0, 0, 1,  //
        7, 0, 0, 0, 2, 0, 0, 0, 6,  //
        0, 6, 0, 0, 0, 0, 2, 8, 0,  //
        0, 0, 0, 4, 1, 9, 0, 0, 5,  //
        0, 0, 0, 0, 8, 0, 0, 7, 9   //

    });
    std::cout << grid << std::endl;

    auto note = init_note(grid, {heur_exclu});
    std::cout << note << std::endl;

    note = init_note(grid, {heur_exclu, heur_single_choice});
    std::cout << note << std::endl;
}

TEST(test_solve, simple_solve1)
{
    Grid grid({
        5, 3, 0, 0, 7, 0, 0, 0, 0,  //
        6, 0, 0, 1, 9, 5, 0, 0, 0,  //
        0, 9, 8, 0, 0, 0, 0, 6, 0,  //
        8, 0, 0, 0, 6, 0, 0, 0, 3,  //
        4, 0, 0, 8, 0, 3, 0, 0, 1,  //
        7, 0, 0, 0, 2, 0, 0, 0, 6,  //
        0, 6, 0, 0, 0, 0, 2, 8, 0,  //
        0, 0, 0, 4, 1, 9, 0, 0, 5,  //
        0, 0, 0, 0, 8, 0, 0, 7, 9   //

    });
    std::cout << grid << std::endl;
    auto note = init_note(grid, {heur_exclu});
    std::cout << note << std::endl;
    ASSERT_TRUE(solve_one(grid, note, {heur_exclu}));
    std::cout << grid << std::endl;
}

TEST(test_solve, simple_solve2)
{
    Grid grid({
        5, 3, 0, 0, 7, 0, 0, 0, 0,  //
        6, 0, 0, 1, 9, 5, 0, 0, 0,  //
        0, 9, 8, 0, 0, 0, 0, 6, 0,  //
        8, 0, 0, 0, 6, 0, 0, 0, 3,  //
        4, 0, 0, 8, 0, 3, 0, 0, 1,  //
        7, 0, 0, 0, 2, 0, 0, 0, 6,  //
        0, 6, 0, 0, 0, 0, 2, 8, 0,  //
        0, 0, 0, 4, 1, 9, 0, 0, 5,  //
        0, 0, 0, 0, 8, 0, 0, 7, 9   //

    });
    std::cout << grid << std::endl;
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(grid, hlist);
    std::cout << note << std::endl;
    ASSERT_TRUE(solve_one(grid, note, hlist));
    std::cout << grid << std::endl;
}

TEST(test_solve, complex_solve1)
{
    Grid grid({
        0, 0, 8, 5, 0, 0, 4, 0, 2,  //
        0, 5, 0, 1, 0, 0, 0, 0, 0,  //
        0, 0, 0, 0, 2, 0, 0, 0, 9,  //
        0, 0, 0, 2, 0, 0, 0, 4, 0,  //
        5, 6, 0, 7, 0, 1, 0, 9, 3,  //
        0, 1, 0, 0, 0, 3, 0, 0, 0,  //
        1, 0, 0, 0, 6, 0, 0, 0, 0,  //
        0, 0, 0, 0, 0, 7, 0, 8, 0,  //
        8, 0, 9, 0, 0, 2, 7, 0, 0,  //
    });
    std::cout << grid << std::endl;
    auto note = init_note(grid, {heur_exclu});
    std::cout << note << std::endl;
    ASSERT_TRUE(solve_one(grid, note, {heur_exclu}));
    std::cout << grid << std::endl;
}

TEST(test_solve, complex_solve2)
{
    Grid grid({
        0, 0, 8, 5, 0, 0, 4, 0, 2,  //
        0, 5, 0, 1, 0, 0, 0, 0, 0,  //
        0, 0, 0, 0, 2, 0, 0, 0, 9,  //
        0, 0, 0, 2, 0, 0, 0, 4, 0,  //
        5, 6, 0, 7, 0, 1, 0, 9, 3,  //
        0, 1, 0, 0, 0, 3, 0, 0, 0,  //
        1, 0, 0, 0, 6, 0, 0, 0, 0,  //
        0, 0, 0, 0, 0, 7, 0, 8, 0,  //
        8, 0, 9, 0, 0, 2, 7, 0, 0,  //
    });
    std::cout << grid << std::endl;
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(grid, hlist);
    std::cout << note << std::endl;
    ASSERT_TRUE(solve_one(grid, note, hlist));
    std::cout << grid << std::endl;
}

TEST(test_solve, all_levels)
{
    Grid b_easy({
        2, 0, 7, 0, 0, 3, 0, 0, 4,  //
        0, 0, 4, 0, 1, 5, 0, 0, 3,  //
        1, 0, 3, 0, 0, 0, 0, 7, 8,  //
        0, 1, 5, 0, 0, 0, 6, 0, 9,  //
        3, 2, 0, 0, 0, 0, 0, 8, 1,  //
        8, 0, 6, 0, 0, 0, 3, 5, 0,  //
        6, 7, 0, 0, 0, 0, 1, 0, 2,  //
        4, 0, 0, 2, 6, 0, 8, 0, 0,  //
        5, 0, 0, 9, 0, 0, 7, 0, 6   //
    });

    Grid b_medium({
        9, 0, 7, 3, 0, 0, 0, 5, 0,  //
        0, 8, 0, 0, 9, 0, 2, 0, 3,  //
        0, 0, 3, 8, 0, 0, 1, 4, 0,  //

        0, 0, 0, 0, 0, 0, 9, 0, 4,  //
        0, 2, 0, 0, 0, 0, 0, 8, 0,  //
        4, 0, 8, 0, 0, 0, 0, 0, 0,  //

        0, 9, 4, 0, 0, 2, 8, 0, 0,  //
        8, 0, 5, 0, 7, 0, 0, 6, 0,  //
        0, 6, 0, 0, 0, 4, 5, 0, 7,  //
    });
    Grid b_hard({
        0, 7, 5, 4, 0, 6, 0, 0, 0,  //
        0, 0, 8, 0, 0, 2, 9, 0, 0,  //
        2, 0, 0, 0, 0, 0, 4, 6, 0,  //

        8, 0, 0, 2, 3, 0, 0, 0, 0,  //
        0, 0, 4, 0, 0, 0, 6, 0, 0,  //
        0, 0, 0, 0, 4, 1, 0, 0, 8,  //

        0, 8, 9, 0, 0, 0, 0, 0, 3,  //
        0, 0, 6, 7, 0, 0, 8, 0, 0,  //
        0, 0, 0, 9, 0, 4, 1, 7, 0,  //
    });

    Grid b_evil({
        3, 0, 0, 0, 7, 4, 0, 0, 0,  //
        0, 4, 0, 8, 5, 0, 7, 0, 0,  //
        0, 8, 0, 0, 0, 2, 0, 0, 0,  //

        0, 0, 2, 0, 0, 0, 0, 9, 8,  //
        0, 6, 0, 0, 0, 0, 0, 5, 0,  //
        1, 5, 0, 0, 0, 0, 3, 0, 0,  //

        0, 0, 0, 3, 0, 0, 0, 7, 0,  //
        0, 0, 3, 0, 8, 5, 0, 2, 0,  //
        0, 0, 0, 6, 4, 0, 0, 0, 5,  //
    });

    std::cout << b_easy << std::endl;
    ASSERT_TRUE(solve_one(b_easy));
    std::cout << b_easy << std::endl;

    std::cout << b_medium << std::endl;
    ASSERT_TRUE(solve_one(b_medium));
    std::cout << b_medium << std::endl;

    std::cout << b_hard << std::endl;
    ASSERT_TRUE(solve_one(b_hard));
    std::cout << b_hard << std::endl;

    std::cout << b_evil << std::endl;
    ASSERT_TRUE(solve_one(b_evil));
    std::cout << b_evil << std::endl;
}
