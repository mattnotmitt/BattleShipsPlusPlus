#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "DrawBattleships/Screen.h"
#include "BattleshipsLogic/Board.h"
#include "BattleshipsBot.h"


int main(int, char**) {
    auto screen = Screen();

    screen.placePlayerShip(Ship::ShipType::CARRIER);
    screen.placePlayerShip(Ship::ShipType::BATTLESHIP);
    screen.placePlayerShip(Ship::ShipType::CRUISER);
    screen.placePlayerShip(Ship::ShipType::SUBMARINE);
    screen.placePlayerShip(Ship::ShipType::DESTROYER);

    wclear(screen.cmdDisp);
    std::string msg("Enemy AI is arranging their fleet...");
    mvwprintw(screen.cmdDisp, 0, 0, msg.c_str());
    wrefresh(screen.cmdDisp);

    botPlaceShips(screen.state.aiBoard, false);
    usleep(15 * 100000UL);

    getch();
    endwin(); 
	return 0;
}
