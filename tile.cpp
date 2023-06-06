#include "tile.hpp"


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
    QString color;
    switch (num_adjacent_bombs)
    {
        case 1:
            color = "blue";
            break;
        case 2:
            color = "green";
            break;
        case 3:
            color = "red";
            break;
        case 4:
            color = "midnightblue";
            break;
        case 5:
            color = "maroon";
            break;
        case 6:
            color = "darkcyan";
            break;
        case 7:
            color = "black";
            break;
        case 8:
            color = "grey";
            break;
        default:
            break;
    }
    return color;
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
