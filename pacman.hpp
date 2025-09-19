#pragma once
#include "point.hpp"
#include "direction.hpp"

class Pacman {
    Point _position;
    Direction _direction;
    int _lives;
    int _score;
public:
    Pacman();
    Pacman(const Point& startPos);
    void Move(Direction direction);
    Point GetPosition() const;
    int GetScore() const;
    int GetLives() const;
    void EatDot();
    void LoseLife();
};
