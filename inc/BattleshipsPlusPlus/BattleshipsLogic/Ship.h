#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

class Ship {
public:
    enum Bearing {
        NEG_X = 1,
        POS_X = 2,
        NEG_Y = 3,
        POS_Y = 4
    };

    enum ShipType {
        DESTROYER = 1,
        SUBMARINE = 2,
        CRUISER = 3,
        BATTLESHIP = 4,
        CARRIER = 5
    };

    const std::map<ShipType, std::string> ShipTypeToName {
        { ShipType::DESTROYER, "Destroyer" },
        { ShipType::SUBMARINE, "Submarine" },
        { ShipType::CRUISER, "Cruiser" },
        { ShipType::BATTLESHIP, "Battleship" },
        { ShipType::CARRIER, "Carrier" },
    };

    const std::map<ShipType, uint8_t> ShipTypeToSize {
        { ShipType::DESTROYER, 2 },
        { ShipType::SUBMARINE, 3 },
        { ShipType::CRUISER, 3 },
        { ShipType::BATTLESHIP, 4 },
        { ShipType::CARRIER, 5 },
    };

private:
    ShipType type;
    Bearing bearing;
    std::pair<int, int> pos;
    std::vector<bool> hits;
    bool destroyed = false;

public:
    Ship(ShipType _type, Bearing _bearing, std::pair<int, int> _pos);
    void isHit();
    ~Ship();

private:
    void destroyShip();
};
