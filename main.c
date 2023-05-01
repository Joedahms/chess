// board matrix
// each tile can have a pointer a piece struct
// matrix of piece pointers 

// FEN code:
// rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
// 1. piece positions. lowercase is black, uppercase is white
// 2. active color
// 3. castling rights
// 4. possible en passant targets
// 5. half move clock. reset upon capture or pawn move
// 6. full move clock. starts at one. increases when a player moves
//
// Bitboards. 64 bit binary number. each bit is a position on the board.
// lsb is bottom left. msb is top right. increases from left to right, top 
// to bottom
//
// all white pieces
// all black pieces
// black pawns
// white pawns
// black rooks
// white rooks
// black knights
// white knights
// black bishops
// white bishops
// black queen
// white queen
// black king
// white king

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>
#include <math.h>

#include "setup.h"
#include "utility.h"
#include "tile.h"
#include "draw_board.h"

#include "pawn.h"

int running = 1;
struct aiocb cntrl_blk;

struct tile board[8][8]; // array of tiles

int num = 0b101;
int num2 = 0b110;
int bin_num[64] = {1,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,1};


void shutdown();
void setup_cntrl_blk();
void on_input(int);
void init_tiles();
void int_to_bin(int);
void int_to_bin64(unsigned long);
void draw_bitmap(int, int, int *);

int main(void) {
	setup();
	unsigned long input = (unsigned long)pow(2,63);
	//int_to_bin64(input);


	init_tiles();

	setup_cntrl_blk();
	signal(SIGIO, on_input); 
	aio_read(&cntrl_blk);

/*
	bin_num = {1,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0}
		   */
	draw_bitmap(0, 150, &bin_num[0]);

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
void draw_bitmap(int y_pos, int x_pos, int* bitmap) {
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

void int_to_bin64(unsigned long integer) {
	int i;
	int index = 0; // start point in array
	int power = 63;
	unsigned long rem; // remainder

	bin_num[index] = integer / (unsigned long)pow(2, power); // msb
	index++; // index = 1
	
	rem = integer % (unsigned long)pow(2, power); 
	power--;

	while (power >= 0) { // 2^n, n >= 0
		bin_num[index] = rem / (unsigned long)pow(2, power); // bit 
		rem = rem % (unsigned long)pow(2, power); // remainder
		power--;
		index++;
	}

}

// take a decimal number and convert it to binary
void int_to_bin(int integer) {
	int i;
	int index = 0; // start point in array
	int power = floor(log2f(integer)); // power of bit under msb
	int rem; // remainder

	bin_num[index] = integer / (int)pow(2, power); // msb
	index++; // index = 1
	
	rem = integer % (int)pow(2, power); 
	power--;

	while (power >= 0) { // 2^n, n >= 0
		bin_num[index] = rem / pow(2, power); // bit 
		rem = rem % (int)pow(2, power); // remainder
		power--;
		index++;
	}
}
