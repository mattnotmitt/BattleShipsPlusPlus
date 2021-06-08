#include "DrawBattleships/Screen.h"

#include <iostream>
#include <sstream>
#include <unistd.h>

void ncursesInit() {
    initscr();
    int xDim, yDim;
    getmaxyx(stdscr, yDim, xDim);
    if (xDim < 100 || yDim < 30) {
        endwin();
        std::cout << "Your terminal must have a minimum dimension of 100 cols, 28 lines." << std::endl;
        exit(0);
    }
    noecho();
    setlocale(LC_CTYPE, "");
    cbreak();
    refresh();
    keypad(stdscr, TRUE);
    start_color();
    // define colour pairs
    use_default_colors(); // modern terminals are wacky
    init_pair(1, COLOR_RED, -1);
}

Screen::Screen() : state()
{
    ncursesInit();

    state.playerBoard.display = newwin(WIN_HEIGHT, WIN_WIDTH, START_Y, START_X);
    state.aiBoard.display     = newwin(WIN_HEIGHT, WIN_WIDTH, START_Y, START_X + WIN_WIDTH + SPACING);

    cmdDisp = newwin(3, 100, 29, 2);

    mvprintw(0, 46, "BATTLESHIP");
    mvaddwstr(2, 30, L"LEGEND: SHIP - " SHIP_TILE " | HIT - " SHIP_DEST " | MISS - *");
    refresh();

    drawBoards();
}

void Screen::placePlayerShip(Ship::ShipType type) {  
    // Setup command prompt 
    nocbreak();
    // Init variables
    char coordInput[2];
    Pos pos;
    
    bool shipPlaced = false;

    std::wstring tempBoard;
    Ship tempShip;
    
    std::stringstream instruction;
    instruction << "Enter grid coordinates to place your " << Ship::ShipTypeToName[type] << " in the form A0,B1 etc: ";
    do {
        wclear(state.playerBoard.display);
        waddwstr(state.playerBoard.display, state.playerBoard.txt.c_str());
        wrefresh(state.playerBoard.display);
        bool first = true;
        do {
            if (!first) {
                std::string errorMsg("> ERR: Your coordinate input must be two characters in the form `[A-J][0-9]`. Please try again.");
                wmove(cmdDisp, 0, 0);
                wclrtoeol(cmdDisp);
                // Print message
                wattron(cmdDisp, A_NORMAL | COLOR_PAIR(1));
                mvwprintw(cmdDisp, 0, 0, errorMsg.c_str());
                wattrset(cmdDisp, A_NORMAL);
            }
            first = false;
            // Clear prompt line
            wmove(cmdDisp, 1, 0);
            wclrtoeol(cmdDisp);
            // Print message
            mvwprintw(cmdDisp, 1, 0, instruction.str().c_str());
            
            echo();
            wrefresh(cmdDisp);
            // Wait & process response
            wgetnstr(cmdDisp, coordInput, 2);
            noecho();

            pos = Board::coordToPos(coordInput);
        } while (pos.first == -1 || pos.second == -1);
        
        // Clear command display
        wclear(cmdDisp);
        // Draw preview of ship
        bool userChoosingBearing = true;
        bool error = false;
        auto bearing = Ship::Bearing::POS_X;
        do {
            bool determiningBearing = true;
            Ship::Bearing originalBearing = bearing;
            do {
                tempShip = Ship(type, bearing, pos);
                try {
                    tempBoard = drawShipOnBoard(state.playerBoard, tempShip);
                    determiningBearing = false;
                } catch (std::runtime_error &msg) {
                    bearing = Ship::incBearing(bearing);
                    if (bearing == originalBearing) {
                        std::string errorMsg("There are no valid bearings for ships with this origin point.");
                        std::string prompt("Press any key to return to the coordinate selection. ");
                        wattron(cmdDisp, A_NORMAL | COLOR_PAIR(1));
                        mvwprintw(cmdDisp, 0, 0, errorMsg.c_str());
                        wattrset(cmdDisp, A_NORMAL);
                        mvwprintw(cmdDisp, 1, 0, prompt.c_str());
                        cbreak();
                        wgetch(cmdDisp);
                        flushinp();
                        nocbreak();

                        wclear(cmdDisp);
                        error = true;
                        break;
                    }
                }
            } while (determiningBearing);
            if (error) {
                break;
            }
            do {
                mvwaddwstr(state.playerBoard.display, 0, 0, tempBoard.c_str());
                std::string prompt("Are you happy with this placement? ");
                std::string errorDesc("Please choose a valid option.");
                std::string options("y to confirm, r to rotate clockwise, c to change position: ");
                mvwprintw(cmdDisp, 0, 0, prompt.c_str());
                if (error) {
                    wattron(cmdDisp, A_NORMAL | COLOR_PAIR(1));
                    wprintw(cmdDisp, errorDesc.c_str());
                    wattrset(cmdDisp, A_NORMAL);
                }
                mvwprintw(cmdDisp, 1, 0, options.c_str());
                echo();
                wrefresh(state.playerBoard.display); // Show the grid
                error = false;
                char userConf = wgetch(cmdDisp);
                flushinp();
                noecho();
                
                if (userConf == 'y') {
                    userChoosingBearing = false;
                    shipPlaced          = true;
                } else if (userConf == 'c') {
                    userChoosingBearing = false;
                } else if (userConf == 'r') {
                    bearing = Ship::incBearing(bearing);
                } else {
                    error = true;               
                }

                wclear(cmdDisp);
            } while(error);
        } while (userChoosingBearing);
    } while (!shipPlaced);

    state.playerBoard.placeShip(tempShip.type, tempShip.bearing, tempShip.pos);
    state.playerBoard.txt = tempBoard;

    // Cleanup command prompt
    cbreak();
    noecho();
}

void Screen::drawBoards() {
    // Draw Player Board
    waddwstr(state.playerBoard.display, state.playerBoard.txt.c_str());
    mvwprintw(state.playerBoard.display, 23, 20, "PLAYER");
	wrefresh(state.playerBoard.display); // Show the grid
    // Draw AI Board
    waddwstr(state.aiBoard.display, state.aiBoard.txt.c_str());
    mvwprintw(state.aiBoard.display, 23, 21, "ENEMY");
	wrefresh(state.aiBoard.display); // Show the grid
}

std::wstring Screen::drawShipOnBoard(Board board, const Ship& ship) {
    auto size      = Ship::ShipTypeToSize[ship.type];
    auto pos       = ship.pos;
    auto txtBoard  = board.txt;
    
    for (int i=0; i<size; ++i) {
        if ( 0 > pos.first || pos.first > 9 || 0 > pos.second || pos.second > 9) {
            throw std::runtime_error("Ship does not fit in current position. Change the bearing.");
        } 
        if (board.isPosInShip(pos)) {
            throw std::runtime_error("Ship overlaps existing ship. Change the bearing.");
        } 
        txtBoard.replace(Board::posToTxtPos(pos), 1, SHIP_TILE);
        pos = Ship::nextPosFromBearing(ship.bearing, pos);
    }
    return txtBoard;
}