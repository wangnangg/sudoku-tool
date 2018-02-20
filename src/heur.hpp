#pragma once
#include "board.hpp"

typedef void (*HeurFunc)(const Board& board, uint id, uint jd, BoardNote& note);
using HeurList = std::vector<HeurFunc>;
void heur_exclu(const Board& board, uint id, uint jd, BoardNote& note);
void heur_single_choice(const Board& board, uint id, uint jd, BoardNote& note);
