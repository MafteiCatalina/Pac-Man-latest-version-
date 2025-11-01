#include "painter.hpp"
#include <iostream>
#include <vector>

void Painter::DrawImage(Point topLeft, Point bottomRight, const std::vector<std::string>& image) { 
    std::cout << "Painter: Drawing image from " << topLeft << " to " << bottomRight << std::endl;
}

void Painter::WriteText(Point position, const std::string& text) { 
    std::cout << "Painter: Writing text '" << text << "' at " << position << std::endl;
}