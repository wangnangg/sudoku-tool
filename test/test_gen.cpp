#include <gtest/gtest.h>
#include "sudoku.hpp"

TEST(test_gen, grade1)
{
    Board board({
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
    uint sol;
    std::cout << grade(board, sol) << std::endl;
    ASSERT_EQ(sol, 1);
}

TEST(test_gen, grade2)
{
    Board b1({
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
    Board b2({
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
    uint sol;
    auto g1 = grade(b1, sol);
    ASSERT_EQ(sol, 1);
    auto g2 = grade(b2, sol);
    ASSERT_EQ(sol, 1);
    std::cout << g1 << std::endl;
    std::cout << g2 << std::endl;
    ASSERT_GT(g2, g1);
}
Board b_zero({
    0, 0, 0, 0, 0, 0, 0, 0, 0,  //
    0, 0, 0, 0, 0, 0, 0, 0, 0,  //
    0, 0, 0, 0, 0, 0, 0, 0, 0,  //

    0, 0, 0, 0, 0, 0, 0, 0, 0,  //
    0, 0, 0, 0, 0, 0, 0, 0, 0,  //
    0, 0, 0, 0, 0, 0, 0, 0, 0,  //

    0, 0, 0, 0, 0, 0, 0, 0, 0,  //
    0, 0, 0, 0, 0, 0, 0, 0, 0,  //
    0, 0, 0, 0, 0, 0, 0, 0, 0,  //
});
TEST(test_gen, grade3)
{
    Board b_easy({
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

    Board b_medium({
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
    Board b_hard({
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

    Board b_evil({
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

    uint sol;
    auto g_easy = grade(b_easy, sol);
    ASSERT_EQ(sol, 1);
    auto g_medium = grade(b_medium, sol);
    ASSERT_EQ(sol, 1);
    auto g_hard = grade(b_hard, sol);
    ASSERT_EQ(sol, 1);
    auto g_evil = grade(b_evil, sol);
    ASSERT_EQ(sol, 1);
    std::cout << g_easy << std::endl;
    std::cout << g_medium << std::endl;
    std::cout << g_hard << std::endl;
    std::cout << g_evil << std::endl;
    ASSERT_GT(g_medium, g_easy);
    ASSERT_GT(g_hard, g_medium);
    ASSERT_GT(g_evil, g_hard);
}