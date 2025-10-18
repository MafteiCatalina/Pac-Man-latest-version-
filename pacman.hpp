#pragma once
#include <iostream>
#include "point.hpp"
#include "direction.hpp"

class Pacman {
private:
    Point _position;
    Direction _direction;
    int _lives;
    int _score;
public:
    friend std::istream& operator >> (std::istream& in, Pacman& pacman);
    friend std::ostream& operator << (std::ostream& out, const Pacman& pacman);

    Pacman();
    Pacman(const Point& startPos);
    Pacman(const Pacman& other); 

    void Move(Direction direction);
    void EatDot();
    void LoseLife();

    Point GetPosition() const;
    int GetScore() const;
    int GetLives() const;
    Direction GetDirection() const { return _direction; }

    Pacman operator = (const Pacman& other); 
    bool operator == (const Pacman& other) const; 
};

std::istream& operator >> (std::istream& in, Pacman& pacman);
std::ostream& operator << (std::ostream& out, const Pacman& pacman);