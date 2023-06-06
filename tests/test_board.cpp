#include <sstream>
#include "catch.hpp"
#include "../board.hpp"


TEST_CASE("Board")
{
    SECTION("3×2 (invalid)")
    {
        REQUIRE_THROWS_AS((Board{3, 2}), std::invalid_argument);
    }

    SECTION("5×4")
    {
        Board board{5, 4};

        REQUIRE(board.width == 5);
        REQUIRE(board.height == 4);

        SECTION("tiles initial state")
        {
            for (unsigned int x = 0; x < 3; x++) {
                for (unsigned int y = 0; y < 2; y++) {
                    Tile& tile = board.get_tile(x, y);
                    REQUIRE(tile.x == x);
                    REQUIRE(tile.y == y);
                    REQUIRE(!tile.is_bomb);
                    REQUIRE(tile.is_covered);
                    REQUIRE(!tile.is_flagged);
                    REQUIRE(tile.num_adjacent_bombs == 0);
                }
            }
        }

        SECTION("get_tile")
        {
            SECTION("valid coordinates")
            {
                board.get_tile(1, 1).is_bomb = true;
                REQUIRE(board.get_tile(1, 1).is_bomb);
            }

            SECTION("invalid coordinates")
            {
                REQUIRE_THROWS_AS(board.get_tile(10, 20), std::invalid_argument);
                REQUIRE_THROWS_AS(board.get_tile(1, 4), std::invalid_argument);
                REQUIRE_THROWS_AS(board.get_tile(5, 1), std::invalid_argument);
            }
        }

        SECTION("random_tile")
        {
            REQUIRE(!board.random_tile().is_bomb);
        }

        SECTION("tile_neighbours")
        {
            SECTION("left top corner")
            {
                std::vector<Position> neighbours = board.tile_neighbours(0, 0);
                std::vector<Position> expected = {{1, 0},
                                                  {0, 1},
                                                  {1, 1}};
                REQUIRE(neighbours.size() == 3);
                REQUIRE(neighbours == expected);
            }

            SECTION("top")
            {
                std::vector<Position> neighbours = board.tile_neighbours(1, 0);
                std::vector<Position> expected = {{0, 0},
                                                  {2, 0},
                                                  {0, 1},
                                                  {1, 1},
                                                  {2, 1}};
                REQUIRE(neighbours.size() == 5);
                REQUIRE(neighbours == expected);
            }

            SECTION("middle")
            {
                std::vector<Position> neighbours = board.tile_neighbours(1, 1);
                std::vector<Position> expected = {{0, 0},
                                                  {1, 0},
                                                  {2, 0},
                                                  {0, 1},
                                                  {2, 1},
                                                  {0, 2},
                                                  {1, 2},
                                                  {2, 2}};
                REQUIRE(neighbours.size() == 8);
                REQUIRE(neighbours == expected);
            }

            SECTION("bottom right corner")
            {
                std::vector<Position> neighbours = board.tile_neighbours(4, 3);
                std::vector<Position> expected = {{3, 2},
                                                  {4, 2},
                                                  {3, 3}};
                REQUIRE(neighbours.size() == 3);
                REQUIRE(neighbours == expected);
            }
        }

        SECTION("generate_bombs")
        {
            SECTION("valid number of bombs")
            {
                board.generate_bombs(7);
                unsigned int count = 0;
                for (unsigned int x = 0; x < 5; x++) {
                    for (unsigned int y = 0; y < 4; y++) {
                        if (board.get_tile(x, y).is_bomb) {
                            count++;
                        }
                    }
                }
                REQUIRE(count == 7);
            }

            SECTION("too many bombs")
            {
                REQUIRE_NOTHROW(board.generate_bombs(10));
                REQUIRE_THROWS_AS(board.generate_bombs(11), std::invalid_argument);
            }
        }

        SECTION("clear_bombs")
        {
            board.generate_bombs(2);
            board.clear_bombs();
            unsigned int count = 0;
            for (unsigned int x = 0; x < 5; x++) {
                for (unsigned int y = 0; y < 4; y++) {
                    if (board.get_tile(x, y).is_bomb) {
                        count++;
                    }
                }
            }
            REQUIRE(count == 0);
        }

        SECTION("count_adjacent_bombs")
        {
            board.set_seed(21);
            board.generate_bombs(7);
            board.count_adjacent_bombs();

            // board.print_board();
            // 0 0 0 1 1
            // 1 1 0 2 B
            // B 3 3 5 B
            // 2 B B B B

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

        SECTION("uncover_tile")
        {
            board.set_seed(21);
            board.generate_bombs(7);
            board.count_adjacent_bombs();
            board.uncover_tile(0, 0);

            // board.print_board();
            // 0 0 0 1 1
            // 1 1 0 2 B
            // B 3 3 5 B
            // 2 B B B B

            REQUIRE(!board.get_tile(0, 0).is_covered);
            REQUIRE(!board.get_tile(1, 0).is_covered);
            REQUIRE(!board.get_tile(2, 0).is_covered);
            REQUIRE(!board.get_tile(3, 0).is_covered);
            REQUIRE(board.get_tile(4, 0).is_covered);

            REQUIRE(!board.get_tile(0, 1).is_covered);
            REQUIRE(!board.get_tile(1, 1).is_covered);
            REQUIRE(!board.get_tile(2, 1).is_covered);
            REQUIRE(!board.get_tile(3, 1).is_covered);
            REQUIRE(board.get_tile(4, 1).is_covered);

            REQUIRE(board.get_tile(0, 2).is_covered);
            REQUIRE(!board.get_tile(1, 2).is_covered);
            REQUIRE(!board.get_tile(2, 2).is_covered);
            REQUIRE(!board.get_tile(3, 2).is_covered);
            REQUIRE(board.get_tile(4, 2).is_covered);

            REQUIRE(board.get_tile(0, 3).is_covered);
            REQUIRE(board.get_tile(1, 3).is_covered);
            REQUIRE(board.get_tile(2, 3).is_covered);
            REQUIRE(board.get_tile(3, 3).is_covered);
            REQUIRE(board.get_tile(4, 3).is_covered);
        }

        SECTION("uncover_bombs")
        {
            board.set_seed(21);
            board.generate_bombs(7);
            board.count_adjacent_bombs();
            board.uncover_bombs();

            // board.print_board();
            // 0 0 0 1 1
            // 1 1 0 2 B
            // B 3 3 5 B
            // 2 B B B B

            REQUIRE(board.get_tile(0, 0).is_covered);
            REQUIRE(board.get_tile(1, 0).is_covered);
            REQUIRE(board.get_tile(2, 0).is_covered);
            REQUIRE(board.get_tile(3, 0).is_covered);
            REQUIRE(board.get_tile(4, 0).is_covered);

            REQUIRE(board.get_tile(0, 1).is_covered);
            REQUIRE(board.get_tile(1, 1).is_covered);
            REQUIRE(board.get_tile(2, 1).is_covered);
            REQUIRE(board.get_tile(3, 1).is_covered);
            REQUIRE(!board.get_tile(4, 1).is_covered);

            REQUIRE(!board.get_tile(0, 2).is_covered);
            REQUIRE(board.get_tile(1, 2).is_covered);
            REQUIRE(board.get_tile(2, 2).is_covered);
            REQUIRE(board.get_tile(3, 2).is_covered);
            REQUIRE(!board.get_tile(4, 2).is_covered);

            REQUIRE(board.get_tile(0, 3).is_covered);
            REQUIRE(!board.get_tile(1, 3).is_covered);
            REQUIRE(!board.get_tile(2, 3).is_covered);
            REQUIRE(!board.get_tile(3, 3).is_covered);
            REQUIRE(!board.get_tile(4, 3).is_covered);
        }

        SECTION("flag_or_unflag_tile")
        {

            REQUIRE(!board.get_tile(0, 0).is_flagged);
            board.flag_or_unflag_tile(0, 0);
            REQUIRE(board.get_tile(0, 0).is_flagged);
            board.flag_or_unflag_tile(0, 0);
            REQUIRE(!board.get_tile(0, 0).is_flagged);
        }

        SECTION("print_board")
        {
            board.set_seed(21);
            board.generate_bombs(7);
            board.count_adjacent_bombs();
            board.get_tile(1, 0).flag();

            std::ostringstream oss;
            auto old_cout = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());

            board.print_board();

            std::cout.rdbuf(old_cout);

            std::string expectedOutput = "0 f 0 1 1 \n"
                                         "1 1 0 2 B \n"
                                         "B 3 3 5 B \n"
                                         "2 B B B B \n";

            REQUIRE(oss.str() == expectedOutput);
        }
    }

    SECTION("41×20 (invalid)")
    {
        REQUIRE_THROWS_AS((Board{41, 20}), std::invalid_argument);
    }

    SECTION("40×21 (invalid)")
    {
        REQUIRE_THROWS_AS((Board{40, 21}), std::invalid_argument);
    }
}
