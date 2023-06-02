#include <stdexcept>
#include <vector>
#include <QRandomGenerator>

class Tile
{
public:
    unsigned int x;
    unsigned int y;
    bool is_bomb;
    bool is_covered;
    bool is_flagged;
    unsigned int num_adjacent_bombs;

    Tile(unsigned int x, unsigned y) : x(x), y(y), is_bomb(false), is_covered(false), is_flagged(false){};
};

class Board
{
public:
    unsigned int width, height;
    std::vector<std::vector<Tile>> Tiles;

    Board(unsigned int width, unsigned int height) : width(width), height(height)
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

    Tile get_tile(unsigned int x, unsigned int y)
    {
        Tile tile = Tiles[y][x];
        return tile;
    }

    QRandomGenerator random{};
    Tile random_tile()
    {
        unsigned int rand_x = random.bounded(width + 1);
        unsigned int rand_y = random.bounded(height + 1);
        Tile rand_tile = get_tile(rand_x, rand_y);
        return rand_tile;
    }

    void generate_bombs(unsigned int num_bombs)
    {
        if (num_bombs > width * height)
        {
            throw std::invalid_argument("Too many bombs");
        }

        while (num_bombs > 0)
        {
            Tile rand_tile = random_tile();
            if (!rand_tile.is_bomb)
            {
                rand_tile.is_bomb = true;
                num_bombs--;
            }
        }
    }

    void count_adjacent_bombs(Tiles &board)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Tile tile = board[i][j];
                if (!tile.is_bomb)
                {
                    int count = 0;
                    for (int ii = -1; ii <= 1; ii++)
                    {
                        for (int jj = -1; jj <= 1; jj++)
                        {
                            // to make sure we don't count the bombs that are out of bounds
                            // current tile wont be counted
                            if (i + ii >= 0 && i + ii < height && j + jj >= 0 && j + jj < width)
                            {
                                if (board[i + ii][j + jj].is_bomb)
                                {
                                    count++;
                                }
                            }
                        }
                    }
                    tile.num_adjacent_bombs = count;
                }
            }
        }
    };

    void uncover_tile(unsigned int x, unsigned int y)
    {
        if (!get_tile(x, y).is_covered)
        {
            throw std::invalid_argument("Tile is already uncovered");
        }
        Tile tile = get_tile(x, y);
        tile.is_covered = false;
    }

    void flag_tile(unsigned int x, unsigned int y)
    {
        if (!get_tile(x, y).is_covered)
        {
            throw std::invalid_argument("Tile is already uncovered");
        }
        Tile tile = get_tile(x, y);
        tile.is_flagged = true;
    }

    void unflag_tile(unsigned int x, unsigned int y)
    {
        if (!get_tile(x, y).is_covered)
        {
            throw std::invalid_argument("Tile is already uncovered");
        }
        Tile tile = get_tile(x, y);
        tile.is_flagged = false;
    }


}

