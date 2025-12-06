#pragma once
#include <iostream>
#include "point.hpp"
#include "direction.hpp"

/**
 * @file ghost.hpp
 * @brief Reprezintă o fantomă din joc.
 * Proiect: Pac-Man — Autor: Maftei Cătălina — An: 2025
 */
class Ghost {
private:
    Point _position;
    Direction _direction;
    bool _vulnerable;
public:
    friend std::istream& operator >> (std::istream& in, Ghost& ghost);
    friend std::ostream& operator << (std::ostream& out, const Ghost& ghost);

    Ghost();
    Ghost(const Point& startPos);
    Ghost(const Ghost& other);

    void Move();
    Point GetPosition() const;
    Direction GetDirection() const;
    bool IsVulnerable() const;

    void SetVulnerable(bool vulnerable);
    void SetDirection(Direction direction);
    void SetPosition(Point position);

    Ghost operator = (const Ghost& other);
    bool operator == (const Ghost& other) const;
};
