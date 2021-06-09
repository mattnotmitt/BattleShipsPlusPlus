#include "BattleshipsBot.h"

#include <random>
#include <stdexcept>
#include <unistd.h>

bool isValidPos(const Board& board, const Ship& ship, std::wstring& boardTxt);

int randInt(int min, int max) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

    return uni(rng);
}

void botPlaceShips(Board& board, bool isPlayerBoard = true) {
    Ship::ShipType types[5] = {Ship::ShipType::CARRIER, Ship::ShipType::BATTLESHIP, Ship::ShipType::CRUISER, Ship::ShipType::SUBMARINE, Ship::ShipType::DESTROYER};
    std::wstring tempBoardTxt;
    for (auto const& type : types) {
        Ship::Bearing bearing = static_cast<Ship::Bearing>(randInt(1,4));
        bool valid = false;
        do {
            bool determiningBearing = true;
            auto initBearing = bearing;
            Pos  rPos(randInt(0,9), randInt(0,9));
            Ship rShip(type, bearing, rPos);
            do {
                tempBoardTxt = board.txt;
                if (isValidPos(board, rShip, tempBoardTxt)) {
                    mvwaddwstr(board.display, 0, 0, tempBoardTxt.c_str());
                    wrefresh(board.display);
                    usleep(500000);
                    board.placeShip(type, bearing, rPos);
                    determiningBearing = false;
                    valid = true;
                } else {
                    bearing = Ship::incBearing(bearing);
                    if (bearing == initBearing) {
                        // No valid orientations, regen the position coords
                        determiningBearing = false;
                    }
                }
            } while (determiningBearing);
        } while(!valid);
        board.txt = tempBoardTxt;
    }
}

/**
 * Yes I am aware this is almost functionally equivalent to
 * Screen::drawShipOnBoard but you have to pay me to do refactors
 */
bool isValidPos(const Board& board, const Ship& ship, std::wstring& boardTxt) {
    auto size      = Ship::ShipTypeToSize[ship.type];
    auto pos       = ship.pos;
    
    for (int i=0; i<size; ++i) {
        if ( 0 > pos.first || pos.first > 9 || 0 > pos.second || pos.second > 9) {
            return false;
        } 
        if (board.isPosInShip(pos)) {
            return false;
        } 
        // Debug line, obvs we don't want to have this in game
        boardTxt.replace(Board::posToTxtPos(pos), 1, SHIP_TILE);
        pos = Ship::nextPosFromBearing(ship.bearing, pos);
    }
    return true;
}