#include <curses.h>

#include "bitmap.h"
#include "draw_board.h"

// draws a bitmap on a mini board
void draw_test_bitmap(int y_pos, int x_pos, int *bitmap) { 
        int i;
        int j;
        int init_x_pos = x_pos;
        draw_board(y_pos, x_pos, 1, 8);
        y_pos += 15;
        x_pos++;
        for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                        mvprintw(y_pos, x_pos, "%d", *bitmap);
                        x_pos += 3;
                        bitmap++;
                }
                y_pos -= 2;
                x_pos = init_x_pos + 1;
        }
}

