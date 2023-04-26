#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>

#include "setup.h"
#include "piece.h"
#include "pawn.h"

int running = 1;
struct aiocb cntrl_blk;

pawn test_pawn;

void shutdown();
void setup_cntrl_blk();
void on_input(int);

int main(void) {
	setup();
	
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
					test_pawn.draw_piece();
					break;
				default:
					break;
			}
		}
	aio_read(&cntrl_blk);
	}

}
