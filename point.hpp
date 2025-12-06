#pragma once
#include <iostream>

/**
 * @file point.hpp
 * @brief Structură pentru coordonate 2D.
 * Proiect: Pac-Man — Autor: Maftei Cătălina — An: 2025
 */
struct Point {
    int x;
    int y;

    Point(int _x = 0, int _y = 0);
    Point(const Point& other);

    Point operator = (const Point& other);
    bool operator == (const Point& other) const;
};

std::istream& operator >> (std::istream& in, Point& point);
std::ostream& operator << (std::ostream& out, const Point& point);
