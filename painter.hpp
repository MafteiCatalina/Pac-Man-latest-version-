#pragma once
#include "abstract_painter.hpp"
#include <string>
#include <vector>

/**
 * @file painter.hpp
 * @brief Implementare simplă a interfeței AbstractPainter.
 * Proiect: Pac-Man — Autor: Maftei Cătălina — An: 2025
 */
class Painter: public AbstractPainter {
public:
    void DrawImage(Point topLeft, Point bottomRight, const std::vector<std::string>& image) override;
    void WriteText(Point position, const std::string& text) override;
};
