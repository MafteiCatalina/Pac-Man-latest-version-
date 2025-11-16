LIB_OBJS = point.o direction.o board.o ghost.o pacman.o
LIB_NAME = libdata.a

APP_OBJS = painter.o game-engine.o main.o

all: $(LIB_NAME) Pacman.exe

$(LIB_NAME): $(LIB_OBJS)
	ar rcs lib/$(LIB_NAME) $(LIB_OBJS)

Pacman.exe: $(APP_OBJS) $(LIB_NAME)
	g++ -o Pacman.exe $(APP_OBJS) -Llib -ldata -std=c++17

point.o: point.cpp point.hpp
	g++ point.cpp -c -std=c++17

direction.o: direction.cpp direction.hpp
	g++ direction.cpp -c -std=c++17

board.o: board.cpp board.hpp
	g++ board.cpp -c -std=c++17

ghost.o: ghost.cpp ghost.hpp
	g++ ghost.cpp -c -std=c++17

pacman.o: pacman.cpp pacman.hpp
	g++ pacman.cpp -c -std=c++17

painter.o: painter.cpp painter.hpp abstract_painter.hpp
	g++ painter.cpp -c -std=c++17

game-engine.o: game-engine.cpp game-engine.hpp
	g++ game-engine.cpp -c -std=c++17

main.o: main.cpp
	g++ main.cpp -c -std=c++17

clean:
	del *.o
	del lib\libdata.a
	del Pacman.exe
