#include <curses.h>

#include "setup.h"
#include "draw_board.h"

void setup() {
	initscr();
	crmode();
	noecho();
	clear();

	draw_board(0, 0, 5, 8);
	refresh();
}
