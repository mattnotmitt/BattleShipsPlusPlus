#pragma once

#include <vector>
#include "Ship.h"
#include "Board.h"

class BattleshipsBot {
    std::vector<Pos> moves;
    struct lastMove {
        bool wasHit;
        bool wasDestroy;
    };
    Pos lastHit;
    enum Mode {
        SEEK,
        HUNT
    } mode;
};

void botPlaceShips(Board& board, bool isPlayerBoard);