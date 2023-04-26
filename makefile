all: chess

chess: main.o draw_board.o setup.o piece.o pawn.o utility.o
	g++ main.o draw_board.o setup.o piece.o pawn.o utility.o -o chess -lncurses -lrt

main.o: main.cpp setup.h pawn.h piece.h pawn.h utility.h
	g++ -c main.cpp -lncurses -lrt

draw_board.o: draw_board.cpp draw_board.h
	g++ -c draw_board.cpp -lncurses

setup.o: setup.cpp setup.h draw_board.h
	g++ -c setup.cpp -lncurses

piece.o: piece.cpp piece.h
	g++ -c piece.cpp 

pawn.o: pawn.cpp pawn.h piece.h
	g++ -c pawn.cpp

utility.o: utility.cpp utility.h
	g++ -c utility.cpp -lncurses

clean: 
	rm chess
	rm *.o
