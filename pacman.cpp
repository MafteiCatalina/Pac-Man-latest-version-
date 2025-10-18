#include "pacman.hpp"

Pacman::Pacman() : 
    _position({1, 1}), 
    _direction(Direction::Right), 
    _lives(3), 
    _score(0) {}

Pacman::Pacman(const Point& startPos) : 
    _position(startPos), 
    _direction(Direction::Right), 
    _lives(3), 
    _score(0) {}

Pacman::Pacman(const Pacman& other) :
    _position(other._position),
    _direction(other._direction),
    _lives(other._lives),
    _score(other._score) {}

void Pacman::Move(Direction direction) { 
    _direction = direction;
}
Point Pacman::GetPosition() const { return _position; }
int Pacman::GetScore() const { return _score; }
int Pacman::GetLives() const { return _lives; }
void Pacman::EatDot() { _score += 10; } 
void Pacman::LoseLife() { _lives -= 1; } 

Pacman Pacman::operator=(const Pacman &other)
{
    if (this != &other)
    {
        _position = other._position;
        _direction = other._direction;
        _lives = other._lives;
        _score = other._score;
    }
    return *this;
}

bool Pacman::operator==(const Pacman &other) const
{
    return _position == other._position && 
           _direction == other._direction &&
           _lives == other._lives && 
           _score == other._score;
}

std::istream& operator >> (std::istream& in, Pacman& pacman){
    if (in >> pacman._position >> pacman._lives >> pacman._score) {
    }
    return in;
}

std::ostream& operator << (std::ostream& out, const Pacman& pacman){
    out << pacman.GetPosition() << " " << pacman.GetLives() << " " << pacman.GetScore();
    return out;
}