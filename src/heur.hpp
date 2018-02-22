#pragma once
#include "grid.hpp"

typedef void (*HeurFunc)(const Grid& grid, uint id, uint jd, GridNote& note);
using HeurList = std::vector<HeurFunc>;
void heur_exclu(const Grid& grid, uint id, uint jd, GridNote& note);
void heur_single_choice(const Grid& grid, uint id, uint jd, GridNote& note);
