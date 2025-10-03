#include "ghost.hpp"

Ghost::Ghost() : _position({0, 0}), _direction(Direction::Up) { /* ... */ }

Ghost::Ghost(const Point& startPos) : _position(startPos), _direction(Direction::Up) { /* ... */ }

void Ghost::Move() {  }

Point Ghost::GetPosition() const { 
    return _position; 
}