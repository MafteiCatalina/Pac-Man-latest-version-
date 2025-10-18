#pragma once
#include <iostream>

enum class Direction {
    Up, Down, Left, Right
};

std::ostream& operator<<(std::ostream& out, const Direction& direction);
