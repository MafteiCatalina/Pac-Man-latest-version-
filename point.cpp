#include "point.hpp"

Point::Point(int _x, int _y) : x(_x), y(_y) {}

Point::Point(const Point &other) : x(other.x), y(other.y) {}

Point Point::operator=(const Point &other)
{
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

bool Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}

std::istream& operator >> (std::istream& in, Point& point){
    int x_val, y_val;
    if (in >> x_val >> y_val) {
        point = Point(x_val, y_val);
    }
    return in;
}

std::ostream& operator << (std::ostream& out, const Point& point){
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}
