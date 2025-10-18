#include "board.hpp"

Board::Board(int width, int height) : _width(width), _height(height) {}

Board::Board(const Board &other) : _width(other._width), _height(other._height) {}

int Board::GetHeight() const { 
    return _height;
}

Board Board::operator=(const Board &other)
{
    if (this != &other)
    {
        _width = other._width;
        _height = other._height;
    }
    return *this;
}

bool Board::operator==(const Board &other) const
{
    return _width == other._width && _height == other._height;
}

std::istream &operator>>(std::istream &in, Board &board)
{
    int width, height;
    if (in >> width >> height) {
        board = Board(width, height); 
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Board &board)
{
    out << board.GetWidth() << " " << board.GetHeight();
    return out;
}
