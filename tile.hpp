#pragma once
#include <memory>
#include <QPushButton>
#include <QString>

extern const QString stylesheet_covered;

extern const QString stylesheet_uncovered;

const std::map<unsigned int, QString> tile_colors{
    {1, "blue"},
    {2, "green"},
    {3, "red"},
    {4, "midnightblue"},
    {5, "maroon"},
    {6, "darkcyan"},
    {7, "black"},
    {8, "grey"}};

class Tile
{
private:
    bool with_gui;

public:
    const unsigned int x;
    const unsigned int y;
    bool is_bomb;
    bool is_covered;
    bool is_flagged;
    unsigned int num_adjacent_bombs;
    std::unique_ptr<QPushButton> button;

    Tile(unsigned int x, unsigned y) : with_gui(false), x(x), y(y), is_bomb(false), is_covered(true), is_flagged(false), num_adjacent_bombs(0){};

    void cover();

    void uncover();

    QString get_color() const;

    void flag();

    void unflag();

    void create_button();
};
