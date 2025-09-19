#pragma once
#include "point.hpp"
#include "direction.hpp"

class Ghost {
    Point _position;
    Direction _direction;
public:
    Ghost(const Point& startPos);
    void Move();
    Point GetPosition() const;
};
