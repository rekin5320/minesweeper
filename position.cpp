#include <iostream>
#include "position.hpp"

bool Position::operator==(const Position& other) const
{
    return x == other.x && y == other.y;
}

std::ostream &operator<<(std::ostream &os, const Position &position)
{
    os << "(" << position.x << ", " << position.y << ")";
    return
    os;
}
