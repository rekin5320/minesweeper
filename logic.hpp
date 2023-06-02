// TODO split to header and source files; temporarily for convenience it's together
#include <iostream>
#include <stdexcept>
#include <vector>
#include <QRandomGenerator>


class Tile
{
public:
    const unsigned int x;
    const unsigned int y;
    bool is_bomb;
    bool is_covered;
    bool is_flagged;
    unsigned int num_adjacent_bombs;

    Tile(unsigned int x, unsigned y) : x(x), y(y), is_bomb(false), is_covered(true), is_flagged(false), num_adjacent_bombs(0) {};

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
};


class Board
{
public:
    const unsigned int WIDTH, HEIGHT;
    std::vector<std::vector<Tile>> Tiles;

    Board(unsigned int width, unsigned int height) : WIDTH(width), HEIGHT(height)
    {
        // Tiles.reserve()  // reserve space to avoid unnecessary relocations
        for (unsigned int y = 0; y < height; y++)
        {
            std::vector<Tile> row;
            for (unsigned int x = 0; x < width; x++)
            {
                row.push_back(Tile(x, y));
            }
            Tiles.push_back(row); // std::move(row) ?
        }
    }

    Tile& get_tile(unsigned int x, unsigned int y)
    {
        if (x >= WIDTH || y >= HEIGHT) {
            throw std::invalid_argument("Invalid coordinates");
        }
        return Tiles[y][x];
    }

    QRandomGenerator random{};
    Tile& random_tile()
    {
        unsigned int rand_x = random.bounded(WIDTH);
        unsigned int rand_y = random.bounded(HEIGHT);
        return get_tile(rand_x, rand_y);
    }

    void generate_bombs(unsigned int num_bombs)
    {
        if (num_bombs > WIDTH * HEIGHT)
        {
            throw std::invalid_argument("Too many bombs");
        }

        while (num_bombs > 0)
        {
            Tile& rand_tile = random_tile();
            if (!rand_tile.is_bomb)
            {
                rand_tile.is_bomb = true;
                num_bombs--;
            }
        }
    }

    void count_adjacent_bombs() {
        for (auto& row : Tiles) {
            for (auto& tile : row) {
                if (!tile.is_bomb) {
                    unsigned int count = 0;
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (!(dx == 0 && dy == 0)) {  // don't count self
                                if ((!(tile.x == 0 && dx == -1)) && !(tile.y == 0 && dy == -1)) {  // left and top border
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
        }
    };

    void print_board() {
        for (auto& row : Tiles) {
            for (auto& tile : row) {
                if (tile.is_flagged) {
                    std::cout << (tile.is_bomb ? "F" : "f");
                }
                else if (tile.is_bomb) {
                    std::cout << "X";
                }
                else {
                    std::cout << tile.num_adjacent_bombs;
                }
            }
            std::cout << "\n";
        }
    }
};
