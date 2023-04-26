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
	mvaddch(*pawn::y_pos, *pawn::x_pos, 'h');	
}
