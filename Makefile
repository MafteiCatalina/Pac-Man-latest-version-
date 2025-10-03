all: Pacman.exe

Pacman.exe: board.o direction.o game-engine.o ghost.o pacman.o painter.o point.o main.o
	g++ -o Pacman.exe board.o direction.o game-engine.o ghost.o pacman.o painter.o point.o main.o

board.o: board.cpp
	g++ board.cpp -o board.o -c

direction.o: direction.cpp
	g++ direction.cpp -o direction.o -c

game-engine.o: game-engine.cpp
	g++ game-engine.cpp -o game-engine.o -c

ghost.o: ghost.cpp
	g++ ghost.cpp -o ghost.o -c

pacman.o: pacman.cpp
	g++ pacman.cpp -o pacman.o -c

painter.o: painter.cpp
	g++ painter.cpp -o painter.o -c

point.o: point.cpp
	g++ point.cpp -o point.o -c

main.o: main.cpp
	g++ main.cpp -o main.o -c

clean:
	DEL *.o Pacman.exe