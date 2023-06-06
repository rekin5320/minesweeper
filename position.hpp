#pragma once

struct Position
{
    unsigned int x;
    unsigned int y;

    bool operator==(const Position &other) const;
};

std::ostream &operator<<(std::ostream &os, const Position &position);
