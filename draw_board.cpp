#include <curses.h> 
#include <string.h> 
#include "draw_board.h"

void draw_board(int y_pos, int x_pos, int tile_size, int tile_num) {
	int i;
	int j;
	int k;
	int tile_hztl;		// horizontal chars in a tile
	int curr_y_pos;	
	int curr_x_pos;
	char intersec;		// what to draw in the intersection
	int intersec_count;	// how many intersections to draw

	tile_hztl = 2 * tile_size; // 2 * because '-'
	
	curr_y_pos = y_pos;
	curr_x_pos = x_pos;
	
	intersec = '+';
	intersec_count = tile_num + 1;
		
	// intersections
	for (i = 0; i < intersec_count; i++) { // vertical
		for (j = 0; j < intersec_count; j++) { // horizontal
			mvaddch(curr_y_pos, curr_x_pos, intersec);
			curr_x_pos += tile_hztl + 1;	
		}
		curr_y_pos += tile_size + 1;  
		curr_x_pos = x_pos;
	}

	// horizontal lines
	curr_y_pos = y_pos;
	for (i = 0; i < intersec_count; i++) { // moving down
		curr_x_pos = x_pos + 1;
		for (j = 0; j < tile_num; j++) { // moving across
			for (k = 0; k < tile_hztl; k++) { // drawing tops
				mvaddch(curr_y_pos, curr_x_pos, '-');
				curr_x_pos++;
			}
			curr_x_pos++;
		}
		curr_y_pos += tile_size + 1;
	}
	
	// vertical lines
	curr_y_pos = y_pos;
	curr_x_pos = x_pos;
	for (i = 0; i < intersec_count; i++) { // moving down
		curr_y_pos = y_pos + 1;
		for (j = 0; j < tile_num; j++) { // moving across
			for (k = 0; k < tile_size; k++) { // drawing tops
				mvaddch(curr_y_pos, curr_x_pos, '|');
				curr_y_pos++;
			}
			curr_y_pos++;
		}
		curr_x_pos += tile_hztl + 1;
	}

//	refresh();

}

