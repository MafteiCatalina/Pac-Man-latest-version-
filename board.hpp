#pragma once

class Board {
    int _width;
    int _height;
public:
    Board(int width = 28, int height = 31);
    int GetHeight() const;
};
