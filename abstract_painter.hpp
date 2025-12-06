#pragma once
#include "point.hpp"
#include <string>
#include <vector>

/**
 * @file abstract_painter.hpp
 * @brief Interfață abstractă pentru desenarea imaginilor și textului.
 * Proiect: Pac-Man — Autor: Maftei Cătălina — An: 2025
 */
struct AbstractPainter {
    virtual void DrawImage(Point topLeft, Point bottomRight, const std::vector<std::string>& image) = 0;
    virtual void WriteText(Point position, const std::string& text) = 0;
    virtual ~AbstractPainter() {}
};
