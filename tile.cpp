#include "tile.hpp"
#include "emoji.hpp"

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

void Tile::cover()
{
    is_covered = true;
    if (with_gui)
    {
        button->setStyleSheet(stylesheet_covered);
        button->setChecked(false);
        button->setText("");
    }
}

void Tile::uncover()
{
    if (!is_flagged)
    {
        is_covered = false;
        if (with_gui)
        {
            button->setStyleSheet(stylesheet_uncovered.arg(get_color()));
            button->setChecked(true);

            if (!is_bomb)
            {
                if (num_adjacent_bombs)
                {
                    button->setText(QString::number(num_adjacent_bombs));
                }
            }
            else
            {
                button->setText(Emoji::Bomb);
            }
        }
    }
}

QString Tile::get_color() const
{
    if (tile_colors.contains(num_adjacent_bombs))
    {
        return tile_colors.at(num_adjacent_bombs);
    }
    else
    {
        return ""; // no color
    }
}

void Tile::flag()
{
    if (is_covered)
    {
        is_flagged = true;
        if (with_gui)
        {
            button->setText(Emoji::Flag);
        }
    }
}

void Tile::unflag()
{
    is_flagged = false;
    if (with_gui)
    {
        button->setText("");
    }
}

void Tile::create_button()
{
    with_gui = true;
    button = std::make_unique<QPushButton>();
    button->setFixedSize(30, 30);
    button->setStyleSheet(stylesheet_covered);
}
