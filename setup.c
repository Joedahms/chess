#include <curses.h>

#include "setup.h"
#include "draw_board.h"

void setup() {
	initscr();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE); // white_pieces
	crmode();
	noecho();
	clear();

	

	draw_board(0, 0, 5, 8);
	refresh();
}

