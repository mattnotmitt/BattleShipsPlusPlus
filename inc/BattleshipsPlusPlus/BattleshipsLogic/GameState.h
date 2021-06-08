#pragma once

#include "Board.h"

class GameState {
private:
    int   currentPlayer = 0;
public:
    GameState() {};
    ~GameState() = default;

    Board playerBoard;
    Board aiBoard;
};
