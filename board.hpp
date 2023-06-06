#pragma once
#include <iostream>
#include <QRandomGenerator>
#include "position.hpp"
#include "tile.hpp"

class Board
{
private:
    QRandomGenerator random{};

public:
    unsigned int width, height;
    std::vector<Tile> Tiles;
    Board() : width(0), height(0){};

    Board(unsigned int width, unsigned int height);

    void set_seed(quint32 seed);

    Tile &get_tile(unsigned int x, unsigned int y);

    Tile &get_tile(Position position);

    Tile &random_tile();

    std::vector<Position> tile_neighbours(unsigned int x, unsigned int y) const;

    std::vector<Position> tile_neighbours(const Tile &tile) const;

    void generate_bombs(unsigned int num_bombs);

    void clear_bombs();

    void count_adjacent_bombs();

    void uncover_tile(unsigned int x, unsigned int y);

    void uncover_bombs();

    void cover_all();

    void flag_or_unflag_tile(unsigned int x, unsigned int y);

    void unflag_all();

    void print_board() const;
};
