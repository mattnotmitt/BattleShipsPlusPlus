#include "Ship.h"

std::map<Ship::ShipType, std::string> 
Ship::ShipTypeToName = std::map<ShipType, std::string>({
    { ShipType::DESTROYER, "Destroyer" },
    { ShipType::SUBMARINE, "Submarine" },
    { ShipType::CRUISER, "Cruiser" },
    { ShipType::BATTLESHIP, "Battleship" },
    { ShipType::CARRIER, "Carrier" }
});


std::map<Ship::ShipType, int> 
Ship::ShipTypeToSize = std::map<ShipType, int>({
    { ShipType::DESTROYER, 2 },
    { ShipType::SUBMARINE, 3 },
    { ShipType::CRUISER, 3 },
    { ShipType::BATTLESHIP, 4 },
    { ShipType::CARRIER, 5 }
});

Ship::Ship(ShipType _type, Bearing _bearing, std::pair<int, int> _pos) 
    :   type(_type), 
        bearing(_bearing), 
        pos(_pos),
        hits(std::vector<bool>(5, false))
{
    auto size = ShipTypeToSize[type];
    auto tPos = pos;

    for (int i=0; i<size; ++i) {
        coords.push_back(tPos);
        tPos = nextPosFromBearing(bearing, tPos);
    }
};