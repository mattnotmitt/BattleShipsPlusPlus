#include "Board.h"

#include <sstream>
#include <iostream>
#include <algorithm>

Board::Board()
{
    ships.reserve(5);
    misses.reserve(100);
}

bool Board::isPosInShip(Pos pos) {
    for (auto const &ship : ships) {
        if (std::find(ship.coords.begin(), ship.coords.end(), pos) != ship.coords.end()) {
            return true;
        }
    }
    return false;
}

void Board::placeShip(Ship::ShipType type, Ship::Bearing bearing, Pos pos) {
    ships.push_back(Ship(type, bearing, pos));
}

int Board::posToTxtPos(Pos pos)
{
    const auto baseRowInt = 1;
    int rowRoot = 90 * (pos.second + 1);
    return rowRoot + baseRowInt + (4 * (pos.first + 1));
}

Pos Board::coordToPos(char* coord)
{
    int xCoord = coord[0] - 'A';
    if (xCoord < 0 || xCoord > 9) {
        xCoord = coord[0] - 'a';
        if (xCoord < 0 || xCoord > 9) {
            xCoord = -1;
        }
    }
    int yCoord = coord[1] - '0';
    if (yCoord < 0 || yCoord > 9) {
        yCoord = -1;
    }
    return Pos(xCoord, yCoord);
}
