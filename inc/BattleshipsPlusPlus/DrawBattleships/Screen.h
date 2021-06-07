#pragma once

#include <memory>

#include "BattleshipsLogic/Board.h"
#include "BattleshipsLogic/GameState.h"

class Screen {
private:
    GameState gameState;
public:
    Screen();
    ~Screen() = default;

    void placeShip();
private:
    void draw();
    void drawBoards();
};
