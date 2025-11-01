#pragma once
#include "abstract_painter.hpp" 
#include <string>
#include <vector>

class Painter: public AbstractPainter {
public:
    void DrawImage(Point topLeft, Point bottomRight, const std::vector<std::string>& image) override;
    void WriteText(Point position, const std::string& text) override;
};