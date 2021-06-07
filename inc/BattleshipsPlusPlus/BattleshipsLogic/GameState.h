#pragma once

#include "Board.h"

class GameState {
private:
    Board playerBoard;
    Board aiBoard;
    int   currentPlayer = 0;
public:
    GameState()  : playerBoard(), aiBoard() {};
    ~GameState() = default;
};
