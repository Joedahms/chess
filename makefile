all: chess

chess: main.o draw_board.o setup.o utility.o pieces.o bitmap.o
	gcc main.o draw_board.o setup.o utility.o pieces.o bitmap.o -o chess -lncurses -lm

main.o: main.c setup.h utility.h pieces.h tile.h draw_board.h bitmap.h
	gcc -c main.c

draw_board.o: draw_board.c draw_board.h
	gcc -c draw_board.c

setup.o: setup.c setup.h draw_board.h
	gcc -c setup.c

utility.o: utility.c utility.h
	gcc -c utility.c

pieces.o: pieces.c pieces.h
	gcc -c pieces.c

bitmap.o: bitmap.c bitmap.h
	gcc -c bitmap.c

clean: 
	rm chess
	rm *.o
