#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

typedef std::pair<int,int>      Pos;

class Ship {
public:
    enum class Bearing : int {
        NEG_X = 1,
        POS_X = 2,
        NEG_Y = 3,
        POS_Y = 4
    };

    static Bearing incBearing(Bearing bearing) {
        switch (bearing) {
            case Ship::Bearing::POS_X: 
                bearing = Ship::Bearing::POS_Y;
                break;
            case Ship::Bearing::NEG_X:
                bearing = Ship::Bearing::NEG_Y;
                break;
            case Ship::Bearing::POS_Y:
                bearing = Ship::Bearing::NEG_X;
                break;
            case Ship::Bearing::NEG_Y:
                bearing = Ship::Bearing::POS_X;
                break;
        }
        return bearing;
    }

    static Pos nextPosFromBearing(Bearing bearing, Pos pos) {
        switch (bearing) {
            case Ship::Bearing::POS_X: 
                pos.first++;
                break;
            case Ship::Bearing::NEG_X:
                pos.first--;
                break;
            case Ship::Bearing::POS_Y:
                pos.second++;
                break;
            case Ship::Bearing::NEG_Y:
                pos.second--;
                break;
        }
        return pos;
    }

    enum ShipType {
        DESTROYER = 1,
        SUBMARINE = 2,
        CRUISER = 3,
        BATTLESHIP = 4,
        CARRIER = 5
    };

    static std::map<ShipType, std::string> ShipTypeToName;
    static std::map<ShipType, int> ShipTypeToSize;

    ShipType type;
    Bearing bearing;
    Pos pos;
    std::vector<bool> hits;
    std::vector<Pos>  coords;
    bool destroyed = false;

    Ship() = default;
    Ship(ShipType _type, Bearing _bearing, std::pair<int, int> _pos);
    ~Ship() = default;

    void isHit();

private:
    void destroyShip();
};
