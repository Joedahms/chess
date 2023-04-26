#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class pawn : piece {
	public:
		int* x_pos;
		int* y_pos;

		pawn();
		~pawn();	
		void draw_piece();
};

#endif
