#pragma once
#include <iostream>

/**
 * @file board.hpp
 * @brief Reprezintă dimensiunile tablei de joc.
 * Proiect: Pac-Man — Autor: Maftei Cătălina — An: 2025
 */
class Board {
private:
    int _width;
    int _height;
public:
    Board(int width = 20, int height = 20);
    Board(const Board& other);

    int GetWidth() const { return _width; }
    int GetHeight() const;

    Board operator = (const Board& other);
    bool operator == (const Board& other) const;
};

std::istream& operator >> (std::istream& in, Board& board);
std::ostream& operator << (std::ostream& out, const Board& board);
