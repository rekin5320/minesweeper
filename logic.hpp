// TODO split to header and source files; temporarily for convenience it's together
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <QPushButton>
#include <QRandomGenerator>
#include <QTimer>
#include "minesweeper_ui.hpp"

struct Position
{
    unsigned int x;
    unsigned int y;

    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }
};

std::ostream &operator<<(std::ostream &os, const Position &position)
{
    os << "(" << position.x << ", " << position.y << ")";
    return os;
}

class Tile
{
public:
    const unsigned int x;
    const unsigned int y;
    bool is_bomb;
    bool is_covered;
    bool is_flagged;
    unsigned int num_adjacent_bombs;
    bool with_gui;
    std::unique_ptr<QPushButton> button;
    const QString stylesheet_covered = R"(
QPushButton {
	border: 1px solid darkgray;
	border-radius: 1px;
	background: qradialgradient(cx : 0.4, cy : -0.1, fx : 0.4, fy : -0.1, radius : 1.35, stop : 0 #fff, stop: 1 #c5c5c5);
}

QPushButton::hover {
    background-color: qradialgradient(cx : 0.4, cy : -0.1, fx : 0.4, fy : -0.1, radius : 1.35, stop : 0 #dddddd, stop: 1 #b8b8b8);
}
)";
    const QString stylesheet_uncovered = R"(
QPushButton {
	color: %1;
    font-size: 18px;
	font-weight: bold;
	border: 1px solid lightgray;
};
)";

    Tile(unsigned int x, unsigned y) : x(x), y(y), is_bomb(false), is_covered(true), is_flagged(false), num_adjacent_bombs(0), with_gui(false){};

    void cover()
    {
        is_covered = true;
        if (with_gui)
        {
            button->setStyleSheet(stylesheet_covered);
            button->setChecked(false);
            button->setText("");
        }
    }

    void uncover()
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
                    button->setText("💣");
                }
            }
        }
    }

    QString get_color() const
    {
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

    void flag()
    {
        if (is_covered)
        {
            is_flagged = true;
            if (with_gui)
            {
                button->setText("🚩");
            }
        }
    }

    void unflag()
    {
        is_flagged = false;
        if (with_gui)
        {
            button->setText("");
        }
    }

    void create_button()
    {
        with_gui = true;
        button = std::make_unique<QPushButton>();
        button->setFixedSize(30, 30);
        button->setStyleSheet(stylesheet_covered);
    }
};

class Board
{
private:
    QRandomGenerator random{};

public:
    unsigned int WIDTH, HEIGHT;
    std::vector<Tile> Tiles;
    Board() : WIDTH(0), HEIGHT(0){};

    Board(unsigned int width, unsigned int height) : WIDTH(width), HEIGHT(height)
    {
        Tiles.reserve(WIDTH * HEIGHT);
        for (unsigned int i = 0; i < WIDTH * HEIGHT; i++)
        {
            Tiles.emplace_back(i % WIDTH, i / WIDTH);
        }
        set_seed(std::random_device()());
    }

    void set_seed(quint32 seed)
    {
        random.seed(seed);
    }

    Tile &get_tile(unsigned int x, unsigned int y)
    {
        if (x >= WIDTH || y >= HEIGHT)
        {
            throw std::invalid_argument("Invalid coordinates");
        }
        return Tiles[y * WIDTH + x];
    }

    Tile &get_tile(Position position)
    {
        return get_tile(position.x, position.y);
    }

    Tile &random_tile()
    {
        unsigned int rand_x = random.bounded(WIDTH);
        unsigned int rand_y = random.bounded(HEIGHT);
        return get_tile(rand_x, rand_y);
    }

    std::vector<Position> tile_neighbours(unsigned int x, unsigned int y) const
    {
        std::vector<Position> neighbours;
        if (x > 0 && y > 0)
        {
            neighbours.push_back({x - 1, y - 1});
        }
        if (y > 0)
        {
            neighbours.push_back({x, y - 1});
        }
        if (y > 0 && x < WIDTH - 1)
        {
            neighbours.push_back({x + 1, y - 1});
        }
        if (x > 0)
        {
            neighbours.push_back({x - 1, y});
        }
        if (x < WIDTH - 1)
        {
            neighbours.push_back({x + 1, y});
        }
        if (x > 0 && y < HEIGHT - 1)
        {
            neighbours.push_back({x - 1, y + 1});
        }
        if (y < HEIGHT - 1)
        {
            neighbours.push_back({x, y + 1});
        }
        if (x < WIDTH - 1 && y < HEIGHT - 1)
        {
            neighbours.push_back({x + 1, y + 1});
        }
        return neighbours;
    }

    std::vector<Position> tile_neighbours(const Tile &tile) const
    {
        return tile_neighbours(tile.x, tile.y);
    }

    void generate_bombs(unsigned int num_bombs)
    {
        // to make sure that there is a least one empty tile
        if (num_bombs > WIDTH * HEIGHT - 9)
        {
            throw std::invalid_argument("Too many bombs");
        }

        while (num_bombs > 0)
        {
            Tile &rand_tile = random_tile();
            if (!rand_tile.is_bomb)
            {
                rand_tile.is_bomb = true;
                num_bombs--;
            }
        }
    }

    void clear_bombs()
    {
        for (auto &tile : Tiles)
        {
            tile.is_bomb = false;
        }
    }

    void count_adjacent_bombs()
    {
        for (auto &tile : Tiles)
        {
            if (!tile.is_bomb)
            {
                unsigned int count = 0;
                for (auto &position : tile_neighbours(tile))
                {
                    if (get_tile(position).is_bomb)
                    {
                        count++;
                    }
                }
                tile.num_adjacent_bombs = count;
            }
            else
            {
                tile.num_adjacent_bombs = 0;
            }
        }
    };

    void uncover_tile(unsigned int x, unsigned int y)
    {
        Tile &tile = get_tile(x, y);
        if (tile.is_covered)
        {
            tile.uncover();
            if (tile.num_adjacent_bombs == 0 && !tile.is_bomb)
            { // uncover empty surround
                for (auto &position : tile_neighbours(tile))
                {
                    Tile &neighbour = get_tile(position);
                    if (neighbour.is_covered)
                    {
                        uncover_tile(position.x, position.y);
                    }
                }
            }
        }
    }

    void uncover_bombs()
    {
        for (auto &tile : Tiles)
        {
            if (tile.is_covered && tile.is_bomb)
            {
                tile.uncover();
            }
        }
    }

    void cover_all()
    {
        for (auto &tile : Tiles)
        {
            if (!tile.is_covered)
            {
                tile.cover();
            }
        }
    }

    void flag_or_unflag_tile(unsigned int x, unsigned int y)
    {
        Tile &tile = get_tile(x, y);
        if (!tile.is_flagged)
        {
            tile.flag();
        }
        else
        {
            tile.unflag();
        }
    }

    void unflag_all()
    {
        for (auto &tile : Tiles)
        {
            if (tile.is_flagged)
            {
                tile.unflag();
            }
        }
    }

    void print_board() const
    {
        for (auto &tile : Tiles)
        {
            if (tile.is_flagged)
            {
                std::cout << (tile.is_bomb ? "F " : "f ");
            }
            else if (tile.is_bomb)
            {
                std::cout << "B ";
            }
            else
            {
                std::cout << tile.num_adjacent_bombs << " ";
            }
            if (tile.x == WIDTH - 1)
            {
                std::cout << "\n";
            }
        }
    }
};

enum Difficulty
{
    BEGINNER,
    INTERMEDIATE,
    EXPERT,
    CUSTOM
};

class Game
{
public:
    Board board;
    unsigned int num_bombs;
    bool with_gui;
    bool has_ended;
    bool first_click;
    Ui::MainWindow ui;
    int game_time_seconds;
    QTimer timer{};

    Game(Difficulty difficulty, unsigned int width = 0, unsigned int height = 0, unsigned int bombs = 0) : with_gui(false)
    {
        switch (difficulty)
        {
        case BEGINNER:
            board = Board(9, 9);
            num_bombs = 10;
            break;
        case INTERMEDIATE:
            board = Board(16, 16);
            num_bombs = 40;
            break;
        case EXPERT:
            board = Board(30, 16);
            num_bombs = 99;
            break;
        case CUSTOM:
            if (width == 0 || height == 0 || bombs == 0)
            {
                throw std::invalid_argument("Missing parameters for custom level");
            }
            board = Board(width, height);
            num_bombs = bombs;
            break;
        default:
            throw std::invalid_argument("Invalid difficulty");
        }
    }

    void start()
    {
        has_ended = false;
        first_click = true;
        board.generate_bombs(num_bombs);
        board.count_adjacent_bombs();
        game_time_seconds = 0;
        timer.start(1000);  // update every 1000 milliseconds (1 second)
        if (with_gui)
        {
            update_bombs_left();
            ui.lcdNumber_right->display(0);
        }
    }

    void play_again()
    {
        board.clear_bombs();
        board.unflag_all();
        board.cover_all();
        start();
        if (with_gui)
        {
            ui.mainbutton->setText("🙂");
        }
    }

    void setupUi(QMainWindow &MainWindow)
    {
        ui.setupUi(&MainWindow);
        QObject::connect(ui.mainbutton, &QPushButton::released, [this](){play_again();});
        QObject::connect(&timer, &QTimer::timeout, [this](){update_timer();});
        with_gui = true;
    }

    void create_tiles()
    {
        for (auto &tile : board.Tiles)
        {
            unsigned int x = tile.x, y = tile.y;
            tile.create_button();
            ui.gridLayout->addWidget(tile.button.get(), y, x);
            tile.button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            QObject::connect(tile.button.get(), &QPushButton::released, [this, x, y]()
                             { uncover_tile(x, y); });
        }
    };

    void update_bombs_left()
    {
        ui.lcdNumber_left->display(static_cast<int>(left_bombs()));
    }

    void update_timer() {
        if (!has_ended)
        {
            ui.lcdNumber_right->display(++game_time_seconds);
        }
    }

    void uncover_tile(unsigned int x, unsigned int y)
    {
        if (first_click)
        {
            while ((board.get_tile(x, y).is_bomb || board.get_tile(x, y).num_adjacent_bombs > 0))
            {
                board.clear_bombs();
                board.generate_bombs(num_bombs);
                board.count_adjacent_bombs();
            }
            first_click = false;
        }

        if (!has_ended)
        {
            board.uncover_tile(x, y);
            if (is_game_over())
            {
                has_ended = true;
                std::cout << "Game over! You lost the game in: " << get_formatted_elapsed_time() << "!\n";
                if (with_gui)
                {
                    ui.mainbutton->setText("🙁");
                }
            }
            else if (is_game_won())
            {
                has_ended = true;
                std::cout << "Congratulations! You won the game in: " << get_formatted_elapsed_time() << "!\n";
                if (with_gui)
                {
                    ui.mainbutton->setText("😎");
                }
            }
        }
    }

    void flag_or_unflag_tile(unsigned int x, unsigned int y)
    {
        board.flag_or_unflag_tile(x, y);
        update_bombs_left();
    }

    unsigned int left_bombs()
    {
        unsigned int count = 0;
        for (auto &tile : board.Tiles)
        {
            if (tile.is_flagged)
            {
                count++;
            }
        }
        return num_bombs - count;
    }

    bool is_game_over()
    {
        for (auto &tile : board.Tiles)
        {
            if (tile.is_bomb && !tile.is_covered)
            {
                board.uncover_bombs();
                return true;
            }
        }
        return false;
    }

    bool is_game_won()
    {
        for (auto &tile : board.Tiles)
        {
            if (!tile.is_bomb && tile.is_covered)
            {
                return false;
            }
        }
        return true;
    }

    std::string get_formatted_elapsed_time() const
    {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << game_time_seconds / 60 << ":";
        oss << std::setfill('0') << std::setw(2) << game_time_seconds % 60;
        return oss.str();
    }
};
