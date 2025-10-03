#include "pacman.hpp"

Pacman::Pacman() : _position({1, 1}), _direction(Direction::Right), _lives(3), _score(0) {  }
Pacman::Pacman(const Point& startPos) : _position(startPos), _direction(Direction::Right), _lives(3), _score(0) {  }
void Pacman::Move(Direction direction) {  }
Point Pacman::GetPosition() const { 
    return _position; 
}

int Pacman::GetScore() const { 
    return _score; 
}

int Pacman::GetLives() const { 
    return _lives; 
}

void Pacman::EatDot() {  }
void Pacman::LoseLife() {  }