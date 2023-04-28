all: chess

chess: main.o draw_board.o setup.o utility.o
	gcc main.o draw_board.o setup.o utility.o -o chess -lncurses -lrt

main.o: main.c setup.h utility.h
	gcc -c main.c -lncurses -lrt

draw_board.o: draw_board.c draw_board.h
	gcc -c draw_board.c -lncurses

setup.o: setup.c setup.h draw_board.h
	gcc -c setup.c -lncurses

utility.o: utility.c utility.h
	gcc -c utility.c -lncurses

clean: 
	rm chess
	rm *.o
