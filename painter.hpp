#pragma once
#include "point.hpp"

class Painter {
public:
    void DrawImage(Point topLeft, Point bottomRight, char** image);
    void WriteText(Point position, char* text);
};
