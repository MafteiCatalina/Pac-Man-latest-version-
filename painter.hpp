#pragma once
#include "abstract_painter.hpp" 

class Painter: public AbstractPainter {
public:
    void DrawImage(Point topLeft, Point bottomRight, char** image) override;
    void WriteText(Point position, char* text) override;
};
