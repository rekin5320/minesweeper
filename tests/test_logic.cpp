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
    REQUIRE(tile.num_adjacent_bombs == 0);

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
    SECTION("3×2") {
        Board board{3, 2};

        REQUIRE(board.WIDTH == 3);
        REQUIRE(board.HEIGHT == 2);

        for (unsigned int x = 0; x < 3; x++) {
            for (unsigned int y = 0; y < 2; y++) {
                Tile &tile = board.get_tile(x, y);
                REQUIRE(tile.x == x);
                REQUIRE(tile.y == y);
                REQUIRE(!tile.is_bomb);
                REQUIRE(tile.is_covered);
                REQUIRE(!tile.is_flagged);
                REQUIRE(tile.num_adjacent_bombs == 0);
            }
        }

        SECTION("get_tile") {
            SECTION("valid coordinates") {
                board.get_tile(1, 1).is_bomb = true;
                REQUIRE(board.get_tile(1, 1).is_bomb);
            }

            SECTION("invalid coordinates") {
                REQUIRE_THROWS_AS(board.get_tile(10, 20), std::invalid_argument);
                REQUIRE_THROWS_AS(board.get_tile(1, 2), std::invalid_argument);
                REQUIRE_THROWS_AS(board.get_tile(3, 1), std::invalid_argument);
            }
        }

        SECTION("random_tile") {
            REQUIRE(!board.random_tile().is_bomb);
        }

        SECTION("generate_bombs") {
            board.generate_bombs(4);
            unsigned int count = 0;
            for (unsigned int x = 0; x < 3; x++) {
                for (unsigned int y = 0; y < 2; y++) {
                    if (board.get_tile(x, y).is_bomb) {
                        count++;
                    }
                }
            }
            REQUIRE(count == 4);
        }

        SECTION("count_adjacent_bombs") {
            board.random.seed(37);
            board.generate_bombs(2);
            board.count_adjacent_bombs();

            // board.print_board();
            // 122
            // 1XX

            REQUIRE(board.get_tile(0, 0).num_adjacent_bombs == 1);
            REQUIRE(board.get_tile(1, 0).num_adjacent_bombs == 2);
            REQUIRE(board.get_tile(2, 0).num_adjacent_bombs == 2);
            REQUIRE(board.get_tile(0, 1).num_adjacent_bombs == 1);
            REQUIRE(board.get_tile(1, 1).is_bomb);
            REQUIRE(board.get_tile(2, 1).is_bomb);
        }
    }

    SECTION("5×4") {
        Board board{5, 4};

        REQUIRE(board.WIDTH == 5);
        REQUIRE(board.HEIGHT == 4);

        SECTION("count_adjacent_bombs") {
            board.random.seed(21);
            board.generate_bombs(7);
            board.count_adjacent_bombs();

            // board.print_board();
            // 00011
            // 1102X
            // X335X
            // 2XXXX

            REQUIRE(board.get_tile(0, 0).num_adjacent_bombs == 0);
            REQUIRE(board.get_tile(1, 0).num_adjacent_bombs == 0);
            REQUIRE(board.get_tile(2, 0).num_adjacent_bombs == 0);
            REQUIRE(board.get_tile(3, 0).num_adjacent_bombs == 1);
            REQUIRE(board.get_tile(4, 0).num_adjacent_bombs == 1);

            REQUIRE(board.get_tile(0, 1).num_adjacent_bombs == 1);
            REQUIRE(board.get_tile(1, 1).num_adjacent_bombs == 1);
            REQUIRE(board.get_tile(2, 1).num_adjacent_bombs == 0);
            REQUIRE(board.get_tile(3, 1).num_adjacent_bombs == 2);
            REQUIRE(board.get_tile(4, 1).is_bomb);

            REQUIRE(board.get_tile(0, 2).is_bomb);
            REQUIRE(board.get_tile(1, 2).num_adjacent_bombs == 3);
            REQUIRE(board.get_tile(2, 2).num_adjacent_bombs == 3);
            REQUIRE(board.get_tile(3, 2).num_adjacent_bombs == 5);
            REQUIRE(board.get_tile(4, 2).is_bomb);

            REQUIRE(board.get_tile(0, 3).num_adjacent_bombs == 2);
            REQUIRE(board.get_tile(1, 3).is_bomb);
            REQUIRE(board.get_tile(2, 3).is_bomb);
            REQUIRE(board.get_tile(3, 3).is_bomb);
            REQUIRE(board.get_tile(4, 3).is_bomb);
        }
    }
}
