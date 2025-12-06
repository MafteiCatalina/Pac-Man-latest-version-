#pragma once
#include <iostream>

/**
 * @file direction.hpp
 * @brief Enum pentru direcțiile posibile de mișcare.
 * Proiect: Pac-Man — Autor: Maftei Cătălina — An: 2025
 */
enum class Direction {
    Up, Down, Left, Right
};

std::ostream& operator<<(std::ostream& out, const Direction& direction);
