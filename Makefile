all: Pacman.exe

Pacman.exe: board.o direction.o game-engine.o ghost.o pacman.o painter.o point.o main.o
	g++ -o Pacman.exe board.o direction.o game-engine.o ghost.o pacman.o painter.o point.o main.o -std=c++17

board.o: board.cpp board.hpp direction.hpp point.hpp
	g++ board.cpp -o board.o -c -std=c++17

direction.o: direction.cpp direction.hpp
	g++ direction.cpp -o direction.o -c -std=c++17

game-engine.o: game-engine.cpp game-engine.hpp board.hpp pacman.hpp ghost.hpp abstract_painter.hpp
	g++ game-engine.cpp -o game-engine.o -c -std=c++17

ghost.o: ghost.cpp ghost.hpp direction.hpp point.hpp
	g++ ghost.cpp -o ghost.o -c -std=c++17

pacman.o: pacman.cpp pacman.hpp direction.hpp point.hpp
	g++ pacman.cpp -o pacman.o -c -std=c++17

painter.o: painter.cpp painter.hpp abstract_painter.hpp
	g++ painter.cpp -o painter.o -c -std=c++17

point.o: point.cpp point.hpp
	g++ point.cpp -o point.o -c -std=c++17

main.o: main.cpp
	g++ main.cpp -o main.o -c -std=c++17

clean:
	del *.o
	del Pacman.exe
