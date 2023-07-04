#include <curses.h>

#include "pieces.h"

void draw_piece(int y_pos, int x_pos, int type) {
	// pawn: 0 1
	// rook: 2 3
	// knight 4 5 
	// bishop 6 7
	// queen 8 9
	// king 10 11
	switch(type) {
		case 0: // white pawn
			draw_pawn(y_pos, x_pos);	
			break;
		case 1: // black pawn
			attron(COLOR_PAIR(1));
			draw_pawn(y_pos, x_pos);	
			attroff(COLOR_PAIR(1));
			break;
		case 2: // white rook
			attron(COLOR_PAIR(1));
			draw_rook(y_pos, x_pos);
			attroff(COLOR_PAIR(1));
			break;
		case 3: // black rook
			draw_rook(y_pos, x_pos);
			break;
		case 4: // white knight
			attron(COLOR_PAIR(1));
			draw_knight(y_pos, x_pos);
			attroff(COLOR_PAIR(1));
			break;
		case 5: // black knight
			draw_knight(y_pos, x_pos);
			break;
		case 6: // white bishop
			attron(COLOR_PAIR(1));
			draw_bishop(y_pos, x_pos);
			attroff(COLOR_PAIR(1));
			break;
		case 7: // black bishop
			draw_bishop(y_pos, x_pos);
			break;
		case 8: // white queen
			attron(COLOR_PAIR(1));
			draw_queen(y_pos, x_pos);
			attroff(COLOR_PAIR(1));
			break;
		case 9: // black queen
			draw_queen(y_pos, x_pos);
			break;
		case 10: // white king
			attron(COLOR_PAIR(1));
			draw_king(y_pos, x_pos);	
			attroff(COLOR_PAIR(1));
			break;
		case 11: // black king
			draw_king(y_pos, x_pos);	
			break;
		default:
			;
	}			
}


void draw_pawn(int y_pos, int x_pos) {
	int i;
	int curr_y_pos;
	int curr_x_pos;

	curr_y_pos = y_pos + 5;
	curr_x_pos = x_pos + 3;

	for (i = 0; i < 6; i++) { // draw base
		mvaddch(curr_y_pos, curr_x_pos, '-');
		curr_x_pos++;
	}
	
	curr_y_pos = y_pos + 4;
	curr_x_pos = x_pos + 5;
		
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '*');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '*');
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '*');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '*');

	refresh();
}

void draw_rook(int y_pos, int x_pos) {
	int i;
	int curr_y_pos;
	int curr_x_pos;

	curr_y_pos = y_pos + 5;
	curr_x_pos = x_pos + 3;

	for (i = 0; i < 6; i++) { // draw base
		mvaddch(curr_y_pos, curr_x_pos, '-');
		curr_x_pos++;
	}
	
	curr_y_pos = y_pos + 4;
	curr_x_pos = x_pos + 5;
		
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_y_pos--;
	
	curr_x_pos -= 2;
	
	for (i = 0; i < 6; i++) {
		mvaddch(curr_y_pos, curr_x_pos, '-');
		curr_x_pos++;
	}	
	curr_x_pos -= 6;
	curr_y_pos--;

	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos += 3;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '|');

	curr_x_pos -= 5;
	curr_y_pos--;
	
	mvaddch(curr_y_pos, curr_x_pos, '-');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '-');
	curr_x_pos += 3;
	mvaddch(curr_y_pos, curr_x_pos, '-');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '-');

	refresh();

}

void draw_knight(int y_pos, int x_pos) {
	int i;
	int curr_y_pos;
	int curr_x_pos;

	curr_y_pos = y_pos + 5;
	curr_x_pos = x_pos + 3;

	for (i = 0; i < 6; i++) { // draw base
		mvaddch(curr_y_pos, curr_x_pos, '-');
		curr_x_pos++;
	}
	
	curr_y_pos = y_pos + 4;
	curr_x_pos = x_pos + 5;
		
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '~');
	curr_x_pos--;
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_y_pos--;
	
	curr_x_pos -= 2;
	
	for (i = 0; i < 2; i++) {
		mvaddch(curr_y_pos, curr_x_pos, '-');
		curr_x_pos++;
	}	
	curr_x_pos -= 2;
	curr_y_pos--;

	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '*');
	curr_x_pos += 2;
	mvaddch(curr_y_pos, curr_x_pos, '|');

	curr_y_pos--;
	
	mvaddch(curr_y_pos, curr_x_pos, '-');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '-');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '-');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '-');

	refresh();

}

void draw_bishop(int y_pos, int x_pos) {
	int i;
	int curr_y_pos;
	int curr_x_pos;

	curr_y_pos = y_pos + 5;
	curr_x_pos = x_pos + 3;

	for (i = 0; i < 6; i++) { // draw base
		mvaddch(curr_y_pos, curr_x_pos, '-');
		curr_x_pos++;
	}

	curr_y_pos = y_pos + 4;
	curr_x_pos = x_pos + 5;
		
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '_');
	curr_x_pos -= 2;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '_');
	curr_x_pos++;
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '`');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '/');
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '\\');
	curr_x_pos--; 
	mvaddch(curr_y_pos, curr_x_pos, '/');
	
	refresh();


}

void draw_queen(int y_pos, int x_pos) {
	int i;
	int curr_y_pos;
	int curr_x_pos;

	curr_y_pos = y_pos + 5;
	curr_x_pos = x_pos + 3;

	for (i = 0; i < 6; i++) { // draw base
		mvaddch(curr_y_pos, curr_x_pos, '-');
		curr_x_pos++;
	}
	
	curr_y_pos = y_pos + 4;
	curr_x_pos = x_pos + 5;
		
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_y_pos--;
	
	curr_x_pos -= 2;
	
	for (i = 0; i < 6; i++) {
		mvaddch(curr_y_pos, curr_x_pos, '|');
		curr_x_pos++;
	}	
	curr_x_pos -= 6;

	curr_y_pos--;
	for (i = 0; i < 6; i++) {
		mvaddch(curr_y_pos, curr_x_pos, '^');
		curr_x_pos++;
	}	

	refresh();
}

void draw_king(int y_pos, int x_pos) {
	int i;
	int curr_y_pos;
	int curr_x_pos;

	curr_y_pos = y_pos + 5;
	curr_x_pos = x_pos + 3;

	for (i = 0; i < 6; i++) { // draw base
		mvaddch(curr_y_pos, curr_x_pos, '-');
		curr_x_pos++;
	}
	
	curr_y_pos = y_pos + 4;
	curr_x_pos = x_pos + 5;
		
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '|');

	

	
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');

	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '_');
	curr_x_pos--;



	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '|');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '_');
	curr_x_pos++;
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '+');
	curr_x_pos++;
	mvaddch(curr_y_pos, curr_x_pos, '+');
	curr_y_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '+');
	curr_x_pos--;
	mvaddch(curr_y_pos, curr_x_pos, '+');
}


