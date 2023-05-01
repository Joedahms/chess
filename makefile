all: chess

chess: main.o draw_board.o setup.o utility.o pawn.o
	gcc main.o draw_board.o setup.o utility.o pawn.o -o chess -lncurses -lm

main.o: main.c setup.h utility.h pawn.h tile.h draw_board.h
	gcc -c main.c

draw_board.o: draw_board.c draw_board.h
	gcc -c draw_board.c

setup.o: setup.c setup.h draw_board.h
	gcc -c setup.c

utility.o: utility.c utility.h
	gcc -c utility.c

pawn.o: pawn.c pawn.h
	gcc -c pawn.c

clean: 
	rm chess
	rm *.o
