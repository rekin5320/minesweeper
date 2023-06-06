#pragma once
#include <memory>
#include <QPushButton>
#include <QString>


const QString stylesheet_covered = R"(
QPushButton {
    border: 1px solid darkgray;
    border-radius: 1px;
    background: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, radius: 1.35, stop: 0 rgba(255, 255, 255, 0.8), stop: 1 rgba(197, 197, 197, 0.8));
}

QPushButton:hover {
    background-color: qradialgradient(cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1, radius: 1.35, stop: 0 rgba(221, 221, 221, 0.8), stop: 1 rgba(184, 184, 184, 0.8));
}
)";

const QString stylesheet_uncovered = R"(
QPushButton {
	color: %1;
    font-size: 18px;
	font-weight: bold;
	border: 1px solid lightgray;
    background-color: rgba(150, 150, 150, 0.65);
};
)";

const std::map<unsigned int, QString> tile_colors {
    {1, "blue"},
    {2, "green"},
    {3, "red"},
    {4, "midnightblue"},
    {5, "maroon"},
    {6, "darkcyan"},
    {7, "black"},
    {8, "grey"}
};


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

    Tile(unsigned int x, unsigned y) : with_gui(false), x(x), y(y), is_bomb(false), is_covered(true), is_flagged(false), num_adjacent_bombs(0) {};

    void cover();

    void uncover();

    QString get_color() const;

    void flag();

    void unflag();

    void create_button();
};
