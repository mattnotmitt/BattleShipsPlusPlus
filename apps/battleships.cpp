#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "DrawBattleships/Screen.h"
#include "BattleshipsLogic/Board.h"

#define START_X 2
#define START_Y 2

/**
 * 
 */
void ncursesInit();

/**
 * draw grid starting at position in args
 */
void drawGrid(int x = START_X, int y = START_Y);

int main(int, char**) {
    ncursesInit();

    WINDOW *player_win;

	player_win = newwin(24, 47, START_Y, START_X);
	auto grid = std::string(GRID);
    grid.replace(Board::posToTxtPos(Pos(9,9)), 1, "*");
    wprintw(player_win, grid.c_str());
    mvwprintw(player_win, 23, 20, "PLAYER");
	wrefresh(player_win);		/* Show that box 		*/    

    WINDOW *enemy_win;

	enemy_win = newwin(24, 47, START_Y, START_X + 49);
	auto egrid = std::string(GRID);
    egrid.replace(Board::posToTxtPos(Pos(1,1)), 1, "*");
    wprintw(enemy_win, egrid.c_str());
    mvwprintw(enemy_win, 23, 21, "ENEMY");
	wrefresh(enemy_win);		/* Show that box 		*/    

    getch();

    endwin();
	return 0;
}

void ncursesInit() {
    initscr();
    clear();
    noecho();
    refresh();
}
