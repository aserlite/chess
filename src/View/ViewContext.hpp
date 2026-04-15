#pragma once
#include "../Logic/Game.hpp"

struct ViewContext {
    Position selectedPos = {-1, -1};
    Position lastPOVPos  = {-1, -1}; // Tracks the last piece selected for POV fallback
};
