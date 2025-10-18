#pragma once
#include "point.hpp"

struct AbstractPainter {\
    virtual void DrawImage(Point topLeft, Point bottomRight, char** image) = 0;
    virtual void WriteText(Point position, char* text) = 0;
    
    virtual ~AbstractPainter() {} 
};
