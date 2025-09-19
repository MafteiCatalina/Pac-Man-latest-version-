#pragma once

class Board {
    int _width;
    int _height;
public:
    Board(int width = 20, int height = 20);
    int GetHeight() const;
};
