#pragma once
#include "pacman.hpp"
#include "ghost.hpp"
#include "board.hpp"
#include <array>
#include <vector>
#include <string>
#include <memory>

class GameEngine {
    std::unique_ptr<Board> _board;
    Pacman _pacman;
    std::array<Ghost, 4> _ghosts;
    std::vector<std::string> _map;

    Point _pacmanStart;
    std::array<Point, 4> _ghostStarts;

public:
    GameEngine();
    void Init();
    void Run();

private:
    bool IsWall(const Point& p) const;
    bool HasPellets() const;
    std::vector<Point> GetNeighbors(const Point& p) const;

    void MoveGhosts();
    void ResetPositions();
};
