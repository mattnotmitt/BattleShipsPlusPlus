#pragma once

#include <vector>

#include "Ship.h"

typedef std::pair<int,int> Pos;

class Board {
private:
    std::vector<Ship> ships  = std::vector<Ship>(5);
    std::vector<Pos>  misses = std::vector<Pos>(100);
public:
    void placeShip(int size);
}   