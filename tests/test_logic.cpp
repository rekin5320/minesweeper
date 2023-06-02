#include <stdexcept>

#include "catch.hpp"
#include "../logic.hpp"


TEST_CASE("Tile") {
    Tile tile(1, 3);
    REQUIRE(tile.x == 1);
    REQUIRE(tile.y == 3);
    REQUIRE(!tile.is_bomb);
    REQUIRE(tile.is_covered);
    REQUIRE(!tile.is_flagged);

    SECTION("uncover()") {
        tile.uncover();
        REQUIRE(!tile.is_covered);
        REQUIRE_THROWS_AS(tile.uncover(), std::invalid_argument);
    }

    SECTION("flag() & unflag()") {
        REQUIRE_THROWS_AS(tile.unflag(), std::invalid_argument);
        tile.flag();
        REQUIRE(tile.is_flagged);
        REQUIRE_THROWS_AS(tile.flag(), std::invalid_argument);
        tile.unflag();
        REQUIRE(!tile.is_flagged);
        REQUIRE_THROWS_AS(tile.unflag(), std::invalid_argument);
    }
}

TEST_CASE("Board") {
    Board board(10, 10);
    REQUIRE(board.WIDTH == 10);
    REQUIRE(board.HEIGHT == 10);
    REQUIRE(board.Tiles.size() == 10);
    REQUIRE(board.Tiles[0].size() == 10);



    SECTION("generate_bombs()") {
        board.generate_bombs(10);
        unsigned int num_bombs = 0;
        for (unsigned int y = 0; y < board.HEIGHT; y++) {
            for (unsigned int x = 0; x < board.WIDTH; x++) {
                if (board.Tiles[y][x].is_bomb) {
                    num_bombs++;
                }
            }
        }
        REQUIRE(num_bombs == 10);
    }

    SECTION("generate_bombs() but error") {
        REQUIRE_THROWS_AS(board.generate_bombs(1000), std::invalid_argument);
    }
    board.count_adjacent_bombs( );
    board.print_board();

}

