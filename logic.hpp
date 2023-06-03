// TODO split to header and source files; temporarily for convenience it's together
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <QPushButton>
#include <QRandomGenerator>


class Tile {
public:
    const unsigned int x;
    const unsigned int y;
    bool is_bomb;
    bool is_covered;
    bool is_flagged;
    unsigned int num_adjacent_bombs;
    std::shared_ptr<QPushButton> button;

    Tile(unsigned int x, unsigned y): x(x), y(y), is_bomb(false), is_covered(true), is_flagged(false), num_adjacent_bombs(0) {};

    void uncover() {
        if (!is_covered) {
            throw std::invalid_argument("Tile is already uncovered");
        }
        is_covered = false;
    }

    void flag() {
        if (is_flagged) {
            throw std::invalid_argument("Tile is already flagged");
        }
        is_flagged = true;
    }

    void unflag() {
        if (!is_flagged) {
            throw std::invalid_argument("Tile is already unflagged");
        }
        is_flagged = false;
    }

    void create_button() {
        button = std::make_shared<QPushButton>();
    }

    void click_button() {
        std::cout << x << " " << y << "\n";
        button->setText("C");
    }
};


class Board {
public:
    unsigned int WIDTH, HEIGHT;
    std::vector<Tile> Tiles;

    Board(): WIDTH(0), HEIGHT(0) {} // default constructor

    Board(unsigned int width, unsigned int height) : WIDTH(width), HEIGHT(height) {
        Tiles.reserve(WIDTH * HEIGHT);
        for (unsigned int i = 0; i < WIDTH * HEIGHT; i++) {
            Tiles.emplace_back(i % WIDTH, i / WIDTH);
        }
    }

    Tile& get_tile(unsigned int x, unsigned int y) {
        if (x >= WIDTH || y >= HEIGHT) {
            throw std::invalid_argument("Invalid coordinates");
        }
        return Tiles[y * WIDTH + x];
    }

    QRandomGenerator random{};
    Tile& random_tile() {
        unsigned int rand_x = random.bounded(WIDTH);
        unsigned int rand_y = random.bounded(HEIGHT);
        return get_tile(rand_x, rand_y);
    }

    void generate_bombs(unsigned int num_bombs) {
        if (num_bombs > WIDTH * HEIGHT) {
            throw std::invalid_argument("Too many bombs");
        }

        while (num_bombs > 0) {
            Tile& rand_tile = random_tile();
            if (!rand_tile.is_bomb) {
                rand_tile.is_bomb = true;
                num_bombs--;
            }
        }
    }

    void count_adjacent_bombs() {
        for (auto& tile: Tiles) {
            if (!tile.is_bomb) {
                unsigned int count = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (!(dx == 0 && dy == 0)) {  // don't count self
                            if ((!(tile.x == 0 && dx == -1)) &&
                                !(tile.y == 0 && dy == -1)) {  // left and top border
                                unsigned int x = tile.x + dx;
                                unsigned int y = tile.y + dy;
                                if (x < WIDTH && y < HEIGHT) {  // right and bottom border
                                    if (get_tile(x, y).is_bomb) {
                                        count++;
                                    }
                                }
                            }
                        }
                    }
                }
                tile.num_adjacent_bombs = count;
            }
        }
    };

    void print_board() {
        for (auto& tile: Tiles) {
            if (tile.is_flagged) {
                std::cout << (tile.is_bomb ? "F " : "f ");
            }
            else if (tile.is_bomb) {
                std::cout << "X ";
            }
            else {
                std::cout << tile.num_adjacent_bombs << " ";
            }
            if (tile.x == WIDTH - 1) {
                std::cout << "\n";
            }
        }
    }
};


enum Difficulty {
    BEGINNER,
    INTERMEDIATE,
    EXPERT,
    CUSTOM
};


class Game {
public:
    Board board;
    unsigned int num_bombs;

    Game(Difficulty difficulty) {
        switch (difficulty) {
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
                unsigned int width, height;
                std::cout << "Enter width: ";
                std::cin >> width;
                std::cout << "Enter height: ";
                std::cin >> height;
                std::cout << "Enter number of bombs: ";
                std::cin >> num_bombs;
                board = Board(width, height);
                break;
            default:
                throw std::invalid_argument("Invalid difficulty");
        }
    }

    void start() {
        board.generate_bombs(num_bombs);
        board.count_adjacent_bombs();
    }

    bool is_game_over() {
        for (auto& tile: board.Tiles) {
            if (tile.is_bomb && !tile.is_covered) {
                return true;
            }
        }
        return false;
    }

    bool is_game_won() {
        for (auto& tile: board.Tiles) {
            if (!tile.is_bomb && tile.is_covered) {
                return false;
            }
        }
        return true;
    }
};
