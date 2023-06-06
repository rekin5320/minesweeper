#include "tile.hpp"

#include <QDebug>

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

void Tile::uncover() {
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
                button->setText("💣");
            }
        }
    }
}

QString Tile::get_color() const {
    if (tile_colors.contains(num_adjacent_bombs))
    {
        return tile_colors.at(num_adjacent_bombs);
    }
    else
    {
        return "";  // no color
    }
}

void Tile::flag() {
    if (is_covered)
    {
        is_flagged = true;
        if (with_gui)
        {
            button->setText("🚩");
        }
    }
}

void Tile::unflag() {
    is_flagged = false;
    if (with_gui)
    {
        button->setText("");
    }
}

void Tile::create_button() {
    with_gui = true;
    button = std::make_unique<QPushButton>();
    button->setFixedSize(30, 30);
    button->setStyleSheet(stylesheet_covered);
}
