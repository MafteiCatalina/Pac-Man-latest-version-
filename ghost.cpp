#include "ghost.hpp"

Ghost::Ghost() : _position({0, 0}), _direction(Direction::Up), _vulnerable(false) {}

Ghost::Ghost(const Point& startPos) : _position(startPos), _direction(Direction::Up), _vulnerable(false) {}

Ghost::Ghost(const Ghost& other) :
    _position(other._position),
    _direction(other._direction),
    _vulnerable(other._vulnerable) {}

void Ghost::Move() {}

Point Ghost::GetPosition() const {
    return _position;
}

Direction Ghost::GetDirection() const {
    return _direction;
}

bool Ghost::IsVulnerable() const {
    return _vulnerable;
}

void Ghost::SetVulnerable(bool vulnerable) {
    _vulnerable = vulnerable;
}

void Ghost::SetDirection(Direction direction) {
    _direction = direction;
}

void Ghost::SetPosition(Point position) {
    _position = position;
}

Ghost Ghost::operator=(const Ghost& other) {
    if (this != &other) {
        _position = other._position;
        _direction = other._direction;
        _vulnerable = other._vulnerable;
    }
    return *this;
}

bool Ghost::operator==(const Ghost& other) const {
    return _position == other._position && _direction == other._direction && _vulnerable == other._vulnerable;
}

std::istream& operator >> (std::istream& in, Ghost& ghost) {
    Point pos;
    if (in >> pos) {
        ghost = Ghost(pos);
    }
    return in;
}

std::ostream& operator << (std::ostream& out, const Ghost& ghost) {
    out << ghost.GetPosition() << " " << ghost.GetDirection() << " " << (ghost.IsVulnerable() ? "Vulnerable" : "Normal");
    return out;
}
