#include "ghost.hpp"

Ghost::Ghost() : _position({0, 0}), _direction(Direction::Up) {}

Ghost::Ghost(const Point& startPos) : _position(startPos), _direction(Direction::Up) {}

Ghost::Ghost(const Ghost& other) : 
    _position(other._position), 
    _direction(other._direction) {}

void Ghost::Move() {  }
Point Ghost::GetPosition() const { return _position; }

Ghost Ghost::operator=(const Ghost &other)
{
    if (this != &other)
    {
        _position = other._position;
        _direction = other._direction;
    }
    return *this;
}

bool Ghost::operator==(const Ghost &other) const
{
    return _position == other._position && _direction == other._direction;
}

std::istream& operator >> (std::istream& in, Ghost& ghost){
    Point pos;
    if (in >> pos) {
        ghost = Ghost(pos);
    }
    return in;
}

std::ostream& operator << (std::ostream& out, const Ghost& ghost){
    out << ghost.GetPosition() << " " << ghost._direction;
    return out;
}
