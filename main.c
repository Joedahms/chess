// board matrix
// each tile can have a pointer a piece struct
// matrix of piece pointers 

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>

#include "setup.h"
#include "utility.h"
#include "tile.h"

#include "pawn.h"

int running = 1;
struct aiocb cntrl_blk;

struct tile board[8][8]; // array of tiles

void shutdown();
void setup_cntrl_blk();
void on_input(int);
void init_tiles();

int main(void) {
	setup();


	init_tiles();

	setup_cntrl_blk();
	signal(SIGIO, on_input); 
	aio_read(&cntrl_blk);

	while (running) {
		pause();	
		refresh();
	}


	shutdown();

	return 0;
}


void shutdown() {
	endwin();
}

void setup_cntrl_blk() {
	char aio_buffer[1];

	cntrl_blk.aio_fildes = 0;
	cntrl_blk.aio_offset = 0;
	cntrl_blk.aio_buf = aio_buffer;
	cntrl_blk.aio_nbytes = 1;
	cntrl_blk.aio_sigevent.sigev_notify = SIGEV_SIGNAL; 
	cntrl_blk.aio_sigevent.sigev_signo = SIGIO;
}

void on_input(int phony) {
	int c;
	char *cp = (char *) cntrl_blk.aio_buf;

	if (aio_error(&cntrl_blk) != 0) {
		perror("io failed");
	}
	else {
		if (aio_return(&cntrl_blk) == 1) {
			c = *cp;
			switch(c) {
				case 'Q':
					running = 0;
					break;
				case 'p':
					draw_pawn(0,0);
					//see_color_content(20, 200, 1);
					break;
				default:
					break;
			}
		}
	aio_read(&cntrl_blk);
	}

}

void init_tiles() {
	int i;
	int j;

	int curr_y_pos = 0;
	int curr_x_pos = 0;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			board[i][j].y_pos = curr_y_pos;
			board[i][j].x_pos = curr_x_pos;
			curr_x_pos = curr_x_pos + 11;
		}
		curr_x_pos = 0;
		curr_y_pos = curr_y_pos + 6;
	}

	// prints tile coords
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			mvprintw(board[i][j].y_pos, board[i][j].x_pos, "%d", board[i][j].y_pos);
			mvprintw(board[i][j].y_pos + 1, board[i][j].x_pos, "%d", board[i][j].x_pos);
		}
	}

	
}
