#ifndef TILE_H
#define TILE_H

struct tile {
	void *piece_ptr; // ptr to piece in tile
	int x_pos;
	int y_pos;
};

#endif
