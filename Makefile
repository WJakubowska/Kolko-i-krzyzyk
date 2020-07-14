#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++17


game: main.o game.o

	g++  -g -Wall -pedantic -std=c++17 -o game main.o game.o\

game.o:  game.hh game.cpp
	g++ -c ${CXXFLAGS} -o game.o game.cpp

main.o: main.cpp game.hh
	g++ -c ${CXXFLAGS} -o main.o main.cpp

clean:
	rm -f *.o game 
