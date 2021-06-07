#include "Board.h"

int Board::posToTxtPos(Pos pos) {
    const auto baseRowInt = 1;
    int rowRoot = 90 * (pos.first + 1);
    return rowRoot + baseRowInt + (4 * (pos.second + 1));
}
