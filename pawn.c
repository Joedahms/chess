#include <curses.h>

#include "pawn.h"

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


	



/*
	mvaddch(20, 200, '-');
	mvaddch(20, 201, '-');
	mvaddch(20, 202, '-'); 
	mvaddch(20, 203, '-');
	mvaddch(20, 204, '-');
	mvaddch(20, 205, '-');

	mvaddch(19, 202, '|');
	mvaddch(19, 203, '|');
	mvaddch(18, 202, '|');
	mvaddch(18, 203, '|');

	mvaddch(17, 202, '*');
	mvaddch(17, 203, '*');
	mvaddch(16, 202, '*');
	mvaddch(16, 203, '*');
*/
	

	refresh();
}

