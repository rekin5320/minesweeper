#include "board.hpp"

Board::Board(unsigned int width, unsigned int height) : width(width), height(height)
{
    if (width < 4 || height < 4)
    {
        throw std::invalid_argument("Board dimensions must be at least 4×4.");
    }

    if (width > 40 || height > 20)
    {
        throw std::invalid_argument("Board dimensions can be at most 40×20.");
    }

    Tiles.reserve(width * height);
    for (unsigned int i = 0; i < width * height; i++)
    {
        Tiles.emplace_back(i % width, i / width);
    }
    set_seed(std::random_device()());
}

void Board::set_seed(quint32 seed)
{
    random.seed(seed);
}

Tile &Board::get_tile(unsigned int x, unsigned int y)
{
    if (x >= width || y >= height)
    {
        throw std::invalid_argument("Invalid coordinates");
    }
    return Tiles[y * width + x];
}

Tile &Board::get_tile(Position position)
{
    return get_tile(position.x, position.y);
}

Tile &Board::random_tile()
{
    unsigned int rand_x = random.bounded(width);
    unsigned int rand_y = random.bounded(height);
    return get_tile(rand_x, rand_y);
}

std::vector<Position> Board::tile_neighbours(unsigned int x, unsigned int y) const
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
    if (y > 0 && x < width - 1)
    {
        neighbours.push_back({x + 1, y - 1});
    }
    if (x > 0)
    {
        neighbours.push_back({x - 1, y});
    }
    if (x < width - 1)
    {
        neighbours.push_back({x + 1, y});
    }
    if (x > 0 && y < height - 1)
    {
        neighbours.push_back({x - 1, y + 1});
    }
    if (y < height - 1)
    {
        neighbours.push_back({x, y + 1});
    }
    if (x < width - 1 && y < height - 1)
    {
        neighbours.push_back({x + 1, y + 1});
    }
    return neighbours;
}

std::vector<Position> Board::tile_neighbours(const Tile &tile) const
{
    return tile_neighbours(tile.x, tile.y);
}

void Board::generate_bombs(unsigned int num_bombs)
{
    if (num_bombs > width * height / 2)
    { // to make sure that there are enough empty tiles
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

void Board::clear_bombs()
{
    for (auto &tile : Tiles)
    {
        tile.is_bomb = false;
    }
}

void Board::count_adjacent_bombs()
{
    for (auto &tile : Tiles)
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
}

void Board::uncover_tile(unsigned int x, unsigned int y)
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

void Board::uncover_bombs()
{
    for (auto &tile : Tiles)
    {
        if (tile.is_covered && tile.is_bomb)
        {
            tile.uncover();
        }
    }
}

void Board::cover_all()
{
    for (auto &tile : Tiles)
    {
        if (!tile.is_covered)
        {
            tile.cover();
        }
    }
}

void Board::flag_or_unflag_tile(unsigned int x, unsigned int y)
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

void Board::unflag_all()
{
    for (auto &tile : Tiles)
    {
        if (tile.is_flagged)
        {
            tile.unflag();
        }
    }
}

void Board::print_board() const
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
        if (tile.x == width - 1)
        {
            std::cout << "\n";
        }
    }
}
