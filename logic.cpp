#include <stdexcept>
#include <vector>
#include <QRandomGenerator>


class Tile {
public:
    unsigned int x;
    unsigned int y;
    bool is_bomb;
    bool is_covered;
    bool is_flagged;

    Tile(unsigned int x, unsigned y): x(x), y(y), is_bomb(false), is_covered(false), is_flagged(false) {};
};


class Board {
public:
    unsigned int width, height;
    std::vector<std::vector<Tile>> Tiles;

    Board(unsigned int width, unsigned int height): width(width), height(height) {
        // Tiles.reserve()  // reserve space to avoid unnecessary relocations
        for(unsigned int y = 0; y < height; y++) {
            std::vector<Tile> row;
            for(unsigned int x = 0; x < width; x++) {
                row.push_back(Tile(x, y));
            }
            Tiles.push_back(row);  // std::move(row) ?
        }
    }

    Tile get_tile(unsigned int x, unsigned int y) {
        Tile tile = Tiles[y][x];
        return tile;
    }

    QRandomGenerator random{};
    Tile random_tile() {
        unsigned int rand_x = random.bounded(width + 1);
        unsigned int rand_y = random.bounded(height + 1);
        Tile rand_tile = get_tile(rand_x, rand_y);
        return rand_tile;
    }

    void generate_bombs(unsigned int num_bombs) {
        if(num_bombs > width * height) {
            throw std::invalid_argument("Too many bombs");
        }

        while(num_bombs > 0) {
            Tile rand_tile = random_tile();
            if(!rand_tile.is_bomb) {
                rand_tile.is_bomb = true;
                num_bombs--;
            }
        }
    }
};
