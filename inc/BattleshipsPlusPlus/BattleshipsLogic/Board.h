#pragma once

#include <ncurses.h>

#include <vector>
#include <string>
#include <memory>

#include "Ship.h"

#define GRID    L"   | A | B | C | D | E | F | G | H | I | J |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 0 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 1 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 2 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 3 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 4 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 5 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 6 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 7 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 8 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" \
                L" 9 |   |   |   |   |   |   |   |   |   |   |\n" \
                L"---+---+---+---+---+---+---+---+---+---+---+\n" 

#define MISS      L"*"
#define SHIP_TILE L"\u2588"
#define SHIP_DEST L"\u259A"

class Board {
private:
    std::vector<Ship> ships;
public:
    WINDOW*          display;
    std::vector<Pos> misses;
    std::wstring     txt     = std::wstring(GRID);
    Board();
    ~Board() = default;

    bool isPosInShip(Pos pos);
    void placeShip(Ship::ShipType type, Ship::Bearing bearing, Pos pos);
    static int posToTxtPos(Pos pos);
    static Pos coordToPos(char* coord);
};  