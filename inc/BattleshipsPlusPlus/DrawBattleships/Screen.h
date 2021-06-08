#pragma once

#include <memory>

#include "BattleshipsLogic/Board.h"
#include "BattleshipsLogic/GameState.h"

#define START_X    4
#define START_Y    4
#define WIN_HEIGHT 24
#define WIN_WIDTH  47
#define SPACING    2

class Screen {
public:
    Screen();
    ~Screen() = default;

    GameState state;

    void placePlayerShip(Ship::ShipType type);
    void placeAiShips();

    static std::wstring drawShipOnBoard(Board board, const Ship& ship);
    WINDOW*   cmdDisp;
private:
    void drawBoards();
};
