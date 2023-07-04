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
// Bitmaps. 64 bit binary number. each bit is a position on the board.
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

// starting off assuming that the side of the board facing the player is the white side
// will need to implement logic to flip the board for a two player game

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
#include "bitmap.h"
#include "pieces.h"

int running = 1;
struct aiocb cntrl_blk;

struct tile board[8][8]; // array of tiles

int all_white_bitmap[64] = {0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    1,1,1,1,1,1,1,1,
			    1,1,1,1,1,1,1,1};

int all_black_bitmap[64] = {1,1,1,1,1,1,1,1,
  			    1,1,1,1,1,1,1,1,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0};

int white_pawns_bitmap[64] = {0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      1,1,1,1,1,1,1,1,
			      0,0,0,0,0,0,0,0};

int black_pawns_bitmap[64] = {0,0,0,0,0,0,0,0,
			      1,1,1,1,1,1,1,1,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0}; 

int white_rooks_bitmap[64] = {0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      1,0,0,0,0,0,0,1};

int black_rooks_bitmap[64] = {1,0,0,0,0,0,0,1,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0};

int white_knights_bitmap[64] = {0,0,0,0,0,0,0,0,
			        0,0,0,0,0,0,0,0,
			        0,0,0,0,0,0,0,0,
			        0,0,0,0,0,0,0,0,
			        0,0,0,0,0,0,0,0,
			        0,0,0,0,0,0,0,0,
			        0,0,0,0,0,0,0,0,
			        0,1,0,0,0,0,1,0};

int black_knights_bitmap[64] = {0,1,0,0,0,0,1,0,
			        0,0,0,0,0,0,0,0,
			        0,0,0,0,0,0,0,0,
			        0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0};

int white_bishops_bitmap[64] = {0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,1,0,0,1,0,0};

int black_bishops_bitmap[64] = {0,0,1,0,0,1,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0,
			      	0,0,0,0,0,0,0,0};

int white_queen_bitmap[64] = {0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,1,0,0,0,0};

int black_queen_bitmap[64] = {0,0,0,0,1,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0,
			      0,0,0,0,0,0,0,0};

int white_king_bitmap[64] = {0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,1,0,0,0};

int black_king_bitmap[64] = {0,0,0,1,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0,
			     0,0,0,0,0,0,0,0};

int bin_num[64] = {1,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,1};

int *all_piece_bitmaps[12] = {white_pawns_bitmap,	
			     black_pawns_bitmap,
			     white_rooks_bitmap,
			     black_rooks_bitmap,
			     white_knights_bitmap,
			     black_knights_bitmap,
			     white_bishops_bitmap,
			     black_bishops_bitmap,
			     white_queen_bitmap,
			     black_queen_bitmap,
			     white_king_bitmap,
			     black_king_bitmap};

int y_coords[64];
int x_coords[64];

void shutdown();
void setup_cntrl_blk();
void on_input(int);
void init_tiles();
void draw_pawns(int *, int *, int *);
void draw_all_pieces(int *y_coords, int *x_coords); 

int main(void) {
	setup();
	unsigned long input = (unsigned long)pow(2,63);

	init_tiles();

	setup_cntrl_blk();
	signal(SIGIO, on_input); 
	aio_read(&cntrl_blk);

	draw_test_bitmap(0, 150, &all_white_bitmap[0]);
	
//	draw_pawns(&y_coords[0], &x_coords[0], &white_pawns[0]);

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

void on_input(int phony) {	// handles user input
	int c;
	char *cp = (char *) cntrl_blk.aio_buf;

	if (aio_error(&cntrl_blk) != 0) {
		perror("io failed");
	}
	else {
		if (aio_return(&cntrl_blk) == 1) {
			c = *cp;
			switch(c) {
				case 'Q':		// quit
					running = 0;
					break;
				case 'p':
					// draw_pawns(&y_coords[0], &x_coords[0], &white_pawns_bitmap[0]);
					draw_all_pieces(y_coords, x_coords);
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

	// put tile coords into 2d arrays
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

	// put tile coords into 1d arrays
	int index = 0;
	for (i = 7; i >= 0; i--) {
		for (j = 0; j < 8; j++) {
			y_coords[index] = board[i][j].y_pos;
			x_coords[index] = board[i][j].x_pos;
			index++;
		}
	}
	refresh();
}

// test for drawing from a bitmap
void draw_pawns(int *y_coords, int *x_coords, int *bitmap) { 
	int i;
	int test_arr[64] = {};
	for (i = 0; i < 64; i++) {
		if (*bitmap == 1) {
			draw_pawn(*y_coords, *x_coords);
			test_arr[i] = 1;	
		}
		y_coords++;
		x_coords++;
		bitmap++;
	}
}

/*
 * random thought
 * piece bitmaps could have a leading value that tells what kind of piece it is
 * might make things more efficient in some places but idk right now
 */


// test for drawing from a bitmap
void draw_all_pieces(int *y_coords, int *x_coords) 
{ 
	int i;
	int j;
	int test_arr[64] = {};
	int *temp_y_coords = y_coords;
	int *temp_x_coords = x_coords;
	int *curr_bitmap = *all_piece_bitmaps;
	//int *curr_bitmap = white_pawns_bitmap;

	for (i = 0; i < 12; i++) 
	{
		for (j = 0; j < 64; j++) 
		{
			if (*curr_bitmap == 1)
			{
				draw_piece(*temp_y_coords, *temp_x_coords, i);
			}
			temp_y_coords++;
			temp_x_coords++;
			curr_bitmap++;
		}
		temp_y_coords = y_coords;
		temp_x_coords = x_coords;
	}
}

