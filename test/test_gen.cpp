#include <gtest/gtest.h>
#include "sudoku.hpp"

TEST(test_gen, grade1)
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
    auto sres = grade(grid);
    std::cout << sres.score << std::endl;
    ASSERT_EQ(sres.sol_count, 1);
}

TEST(test_gen, grade2)
{
    Grid b1({
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
    Grid b2({
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
    auto g1 = grade(b1);
    ASSERT_EQ(g1.sol_count, 1);
    auto g2 = grade(b2);
    ASSERT_EQ(g2.sol_count, 1);
    std::cout << g1.score << std::endl;
    std::cout << g2.score << std::endl;
    ASSERT_GT(g2.score, g1.score);
}
Grid b_zero({
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

    auto g_easy = grade(b_easy);
    ASSERT_EQ(g_easy.sol_count, 1);
    auto g_medium = grade(b_medium);
    ASSERT_EQ(g_medium.sol_count, 1);
    auto g_hard = grade(b_hard);
    ASSERT_EQ(g_hard.sol_count, 1);
    auto g_evil = grade(b_evil);
    ASSERT_EQ(g_evil.sol_count, 1);
    std::cout << g_easy.score << std::endl;
    std::cout << g_medium.score << std::endl;
    std::cout << g_hard.score << std::endl;
    std::cout << g_evil.score << std::endl;
    ASSERT_GT(g_medium.score, g_easy.score);
    ASSERT_GT(g_hard.score, g_medium.score);
    ASSERT_GT(g_evil.score, g_hard.score);
}

TEST(test_gen, topband)
{
    for (uint i = 0; i < 1000; i++)
    {
        rand_grid_starter();
    }
    Grid grid = rand_grid_starter();
    std::cout << grid << std::endl;
}

TEST(test_gen, gen_grid)
{
    Grid grid = rand_grid();
    std::cout << grid << std::endl;
}

TEST(test_gen, gen_puzzle)
{
    for (uint i = 0; i < 1000; i++)
    {
        Grid grid = gen_puzzle();
        auto sres = grade(grid);
        ASSERT_EQ(sres.sol_count, 1);
        std::cout << "score:" << sres.score << std::endl;
    }
    Grid grid = gen_puzzle();
    auto sres = grade(grid);
    ASSERT_EQ(sres.sol_count, 1);
    std::cout << grid << std::endl;
    std::cout << "score:" << sres.score << std::endl;
}

TEST(test_gen, gen_puzzle_min_score_100)
{
    uint min_s = 100;
    uint max_iter = 10000;
    Grid grid = gen_puzzle(min_s, max_iter);
    auto g = grade(grid);
    simple_print(std::cout, grid);
    std::cout << g.score << std::endl;
    ASSERT_GT(g.score, min_s);
}

TEST(test_gen, gen_puzzle_min_score_200)
{
    uint min_s = 200;
    uint max_iter = 10000;
    Grid grid = gen_puzzle(min_s, max_iter);
    auto g = grade(grid);
    simple_print(std::cout, grid);
    std::cout << g.score << std::endl;
    ASSERT_GT(g.score, min_s);
}

TEST(test_gen, gen_puzzle_min_score_500)
{
    uint min_s = 500;
    uint max_iter = 10000;
    Grid grid = gen_puzzle(min_s, max_iter);
    auto g = grade(grid);
    simple_print(std::cout, grid);
    std::cout << g.score << std::endl;
    ASSERT_GT(g.score, min_s);
}

TEST(test_gen, gen_puzzle_min_score_1000)
{
    uint min_s = 1000;
    uint max_iter = 10000;
    Grid grid = gen_puzzle(min_s, max_iter);
    auto g = grade(grid);
    simple_print(std::cout, grid);
    std::cout << g.score << std::endl;
    ASSERT_GT(g.score, min_s);
}

TEST(test_gen, gen_puzzle_min_score_3000)
{
    uint min_s = 3000;
    uint max_iter = 10000;
    Grid grid = gen_puzzle(min_s, max_iter);
    auto g = grade(grid);
    simple_print(std::cout, grid);
    std::cout << g.score << std::endl;
    ASSERT_GT(g.score, min_s);
}

TEST(test_gen, bighead1)
{
    Grid grid({
        0, 0, 0, 2, 5, 1, 0, 0, 0,  //
        0, 2, 0, 0, 7, 0, 0, 5, 0,  //
        0, 0, 7, 0, 0, 0, 9, 0, 0,  //

        4, 0, 0, 1, 0, 3, 0, 0, 6,  //
        2, 1, 0, 0, 0, 0, 0, 4, 5,  //
        7, 0, 0, 5, 0, 9, 0, 0, 2,  //

        0, 0, 6, 0, 0, 0, 2, 0, 0,  //
        0, 3, 0, 0, 9, 0, 0, 8, 0,  //
        0, 0, 0, 6, 1, 4, 0, 0, 0,  //
    });
    auto g = grade(grid);
    simple_print(std::cout, grid);
    std::cout << g.score << std::endl;
}
