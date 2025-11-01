#pragma once
#include "point.hpp"
#include <string>
#include <vector>

struct AbstractPainter {
    virtual void DrawImage(Point topLeft, Point bottomRight, const std::vector<std::string>& image) = 0;
    virtual void WriteText(Point position, const std::string& text) = 0;
    
    virtual ~AbstractPainter() {} 
};