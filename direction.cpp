#include "direction.hpp"

std::ostream& operator<<(std::ostream& out, const Direction& direction){
    switch (direction)
    {
    case Direction::Up:
        out << "Up";
        break;
    case Direction::Down:
        out << "Down";
        break;
    case Direction::Left:
        out << "Left";
        break;
    case Direction::Right:
        out << "Right";
        break;
    }
    return out;
}
