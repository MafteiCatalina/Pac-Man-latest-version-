#pragma once
#include "pacman.hpp"
#include "ghost.hpp"
#include "board.hpp"
#include "abstract_painter.hpp" 
#include <array>
#include <memory> 

class GameEngine {
    Pacman _pacman;
    std::array<Ghost, 4> _ghosts; 
    Board _board;
    std::unique_ptr<AbstractPainter> _painter; 
public:
    GameEngine();
    void Init();
    void Run();
};