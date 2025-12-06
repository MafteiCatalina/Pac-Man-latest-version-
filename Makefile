LIB_OBJS = point.o direction.o board.o ghost.o pacman.o
LIB_NAME = libdata.a

APP_OBJS = painter.o game-engine.o main.o

TEST_OBJ = tests/test_data.o
TEST_EXE = tests.exe

all: $(LIB_NAME) Pacman.exe

$(LIB_NAME): $(LIB_OBJS)
	ar rcs lib/$(LIB_NAME) $(LIB_OBJS)

Pacman.exe: $(APP_OBJS) $(LIB_NAME)
	g++ -o Pacman.exe $(APP_OBJS) -Llib -ldata \
	-Lexternal/raylib/lib -lraylib \
	-lopengl32 -lgdi32 -lwinmm -std=c++17

point.o: point.cpp point.hpp
	g++ point.cpp -c -std=c++17

direction.o: direction.cpp direction.hpp
	g++ direction.cpp -c -std=c++17

board.o: board.cpp board.hpp
	g++ board.cpp -c -std=c++17

ghost.o: ghost.cpp ghost.hpp direction.hpp point.hpp
	g++ ghost.cpp -c -std=c++17

pacman.o: pacman.cpp pacman.hpp direction.hpp point.hpp
	g++ pacman.cpp -c -std=c++17

painter.o: painter.cpp painter.hpp abstract_painter.hpp
	g++ painter.cpp -c -std=c++17

game-engine.o: game-engine.cpp game-engine.hpp board.hpp pacman.hpp ghost.hpp
	g++ -Iexternal -Iexternal/raylib/include game-engine.cpp -c -std=c++17

main.o: main.cpp
	g++ main.cpp -c -std=c++17

tests/test_data.o: tests/test_data.cpp point.hpp board.hpp pacman.hpp ghost.hpp direction.hpp
	g++ tests/test_data.cpp -c -std=c++17 -o tests/test_data.o

test: $(LIB_NAME) $(TEST_OBJ)
	g++ -o $(TEST_EXE) $(TEST_OBJ) -Llib -ldata -std=c++17
	./$(TEST_EXE)

clean:
	del *.o
	del lib\libdata.a
	del Pacman.exe
	-del $(TEST_EXE)
