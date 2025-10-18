#pragma once
#include "pacman.hpp"
#include "ghost.hpp"
#include "board.hpp"
#include "painter.hpp" 

class GameEngine {
    Pacman _pacman;
    Ghost _ghosts[4]; 
    Board _board;
    Painter _painter; 
public:
    GameEngine();
    void Init();
    void Run();
};
