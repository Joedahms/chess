#include <curses.h>

#include "pawn.h"

pawn::pawn() {
	pawn::x_pos = new int(80);
	pawn::y_pos = new int(18);
}

pawn::~pawn() {
	delete x_pos;
	delete y_pos;
}

void pawn::draw_piece() {
	mvaddch(20, 200, '-');
	mvaddch(20, 201, '-');
	mvaddch(20, 202, '-');

	mvaddch(19, 201, '|');

	mvaddch(18, 201, '*');

//	mvaddch(*pawn::y_pos, *pawn::x_pos, 'h');	
	refresh();
}
