
main: main.o rummy.o table.o hand.o board.o
	g++ -std=gnu++17 -o main main.o rummy.o table.o hand.o board.o

main.o: main.cpp hand.h rummy.h table.h board.h
	g++ -std=gnu++17 -c main.cpp

rummy.o: rummy.cpp rummy.h
	g++ -std=gnu++17 -c rummy.cpp

table.o: table.cpp table.h
	g++ -std=gnu++17 -c table.cpp

board.o: board.cpp board.h
	g++ -std=gnu++17 -c board.cpp

hand.o: hand.cpp hand.h
	g++ -std=gnu++17 -c hand.cpp

clean:
	rm -rf *.o main
