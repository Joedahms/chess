#include <curses.h>

#include "setup.h"
#include "draw_board.h"

void setup() {
	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_YELLOW);
	attron(COLOR_PAIR(1));
	crmode();
	noecho();
	clear();

	draw_board(0, 0, 5, 8);
	refresh();
}
