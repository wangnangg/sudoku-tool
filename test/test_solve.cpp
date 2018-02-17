#include <gtest/gtest.h>
#include "board.hpp"

TEST(test_solve, print_board)
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
    std::cout << board << std::endl;
}

TEST(test_solve, print_board_heur)
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
    std::cout << board << std::endl;

    auto note = init_note(board, {heur_exclu});
    std::cout << note << std::endl;

    note = init_note(board, {heur_exclu, heur_single_choice});
    std::cout << note << std::endl;
}

TEST(test_solve, simple_solve1)
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
    std::cout << board << std::endl;
    auto note = init_note(board, {heur_exclu});
    std::cout << note << std::endl;
    ASSERT_TRUE(solve_one(board, note, {heur_exclu}));
    std::cout << board << std::endl;
}

TEST(test_solve, simple_solve2)
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
    std::cout << board << std::endl;
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(board, hlist);
    std::cout << note << std::endl;
    ASSERT_TRUE(solve_one(board, note, hlist));
    std::cout << board << std::endl;
}

TEST(test_solve, complex_solve1)
{
    Board board({
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
    std::cout << board << std::endl;
    auto note = init_note(board, {heur_exclu});
    std::cout << note << std::endl;
    ASSERT_TRUE(solve_one(board, note, {heur_exclu}));
    std::cout << board << std::endl;
}

TEST(test_solve, complex_solve2)
{
    Board board({
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
    std::cout << board << std::endl;
    HeurList hlist = {heur_exclu, heur_single_choice};
    auto note = init_note(board, hlist);
    std::cout << note << std::endl;
    ASSERT_TRUE(solve_one(board, note, hlist));
    std::cout << board << std::endl;
}
