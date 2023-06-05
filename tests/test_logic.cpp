#include <stdexcept>
#include <sstream>

#include "catch.hpp"
#include "../logic.hpp"

TEST_CASE("Tile")
{
    Tile tile(1, 3);
    REQUIRE(tile.x == 1);
    REQUIRE(tile.y == 3);
    REQUIRE(!tile.is_bomb);
    REQUIRE(tile.is_covered);
    REQUIRE(!tile.is_flagged);
    REQUIRE(tile.num_adjacent_bombs == 0);

    SECTION("uncover()")
    {
        tile.uncover();
        REQUIRE(!tile.is_covered);
    }

    SECTION("flag() & unflag()")
    {
        tile.flag();
        REQUIRE(tile.is_flagged);
        tile.unflag();
        REQUIRE(!tile.is_flagged);
    }
}

TEST_CASE("Board")
{
    SECTION("3×2")
    {
        Board board{3, 2};

        REQUIRE(board.WIDTH == 3);
        REQUIRE(board.HEIGHT == 2);

        for (unsigned int x = 0; x < 3; x++)
        {
            for (unsigned int y = 0; y < 2; y++)
            {
                Tile &tile = board.get_tile(x, y);
                REQUIRE(tile.x == x);
                REQUIRE(tile.y == y);
                REQUIRE(!tile.is_bomb);
                REQUIRE(tile.is_covered);
                REQUIRE(!tile.is_flagged);
                REQUIRE(tile.num_adjacent_bombs == 0);
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
                REQUIRE_THROWS_AS(board.get_tile(1, 2), std::invalid_argument);
                REQUIRE_THROWS_AS(board.get_tile(3, 1), std::invalid_argument);
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
                std::vector<Position> expected = {{1, 0}, {0, 1}, {1, 1}};
                REQUIRE(neighbours.size() == 3);
                REQUIRE(neighbours == expected);
            }
            SECTION("top")
            {
                std::vector<Position> neighbours = board.tile_neighbours(1, 0);
                std::vector<Position> expected = {{0, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}};
                REQUIRE(neighbours.size() == 5);
                REQUIRE(neighbours == expected);
            }
        }

        SECTION("generate_bombs")
        {
            board.generate_bombs(4);
            unsigned int count = 0;
            for (unsigned int x = 0; x < 3; x++)
            {
                for (unsigned int y = 0; y < 2; y++)
                {
                    if (board.get_tile(x, y).is_bomb)
                    {
                        count++;
                    }
                }
            }
            REQUIRE(count == 4);
        }

        SECTION("clear_bombs")
        {
            board.generate_bombs(4);
            board.clear_bombs();
            unsigned int count = 0;
            for (unsigned int x = 0; x < 3; x++)
            {
                for (unsigned int y = 0; y < 2; y++)
                {
                    if (board.get_tile(x, y).is_bomb)
                    {
                        count++;
                    }
                }
            }
            REQUIRE(count == 0);
        }

        SECTION("count_adjacent_bombs")
        {
            board.set_seed(37);
            board.generate_bombs(2);
            board.count_adjacent_bombs();

            // board.print_board();
            // 1 2 2
            // 1 B B

            REQUIRE(board.get_tile(0, 0).num_adjacent_bombs == 1);
            REQUIRE(board.get_tile(1, 0).num_adjacent_bombs == 2);
            REQUIRE(board.get_tile(2, 0).num_adjacent_bombs == 2);
            REQUIRE(board.get_tile(0, 1).num_adjacent_bombs == 1);
            REQUIRE(board.get_tile(1, 1).is_bomb);
            REQUIRE(board.get_tile(2, 1).is_bomb);
        }
    }

    SECTION("5×4")
    {
        Board board{5, 4};

        REQUIRE(board.WIDTH == 5);
        REQUIRE(board.HEIGHT == 4);

        SECTION("tile_neighbours")
        {
            SECTION("middle")
            {
                std::vector<Position> neighbours = board.tile_neighbours(1, 1);
                std::vector<Position> expected = {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2}};
                REQUIRE(neighbours.size() == 8);
                REQUIRE(neighbours == expected);
            }
            SECTION("bottom right corner")
            {
                std::vector<Position> neighbours = board.tile_neighbours(4, 3);
                std::vector<Position> expected = {{3, 2}, {4, 2}, {3, 3}};
                REQUIRE(neighbours.size() == 3);
                REQUIRE(neighbours == expected);
            }
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
}

TEST_CASE("Game")
{
    SECTION("BEGINNER")
    {
        Game game;
        game.set_level(Difficulty::BEGINNER);

        REQUIRE(game.board.WIDTH == 9);
        REQUIRE(game.board.HEIGHT == 9);
        REQUIRE(game.num_bombs == 10);
    }

    SECTION("INTERMEDIATE")
    {
        Game game;
        game.set_level(Difficulty::INTERMEDIATE);

        REQUIRE(game.board.WIDTH == 16);
        REQUIRE(game.board.HEIGHT == 16);
        REQUIRE(game.num_bombs == 40);
    }

    SECTION("EXPERT")
    {
        Game game;
        game.set_level(Difficulty::EXPERT);

        REQUIRE(game.board.WIDTH == 30);
        REQUIRE(game.board.HEIGHT == 16);
        REQUIRE(game.num_bombs == 99);
    }

    SECTION("CUSTOM")
    {
        Game game;
        game.set_level(Difficulty::CUSTOM, 5, 4, 7);

        REQUIRE(game.board.WIDTH == 5);
        REQUIRE(game.board.HEIGHT == 4);
        REQUIRE(game.num_bombs == 7);
    }

    SECTION("CUSTOM_MISSING_ARGS")
    {
        Game game1;
        Game game2;
        REQUIRE_THROWS_AS(game1.set_level(CUSTOM, 6, 7), std::invalid_argument);
        REQUIRE_THROWS_AS(game2.set_level(CUSTOM), std::invalid_argument);
    }

    SECTION("start()")
    {
        Game game;
        game.set_level(Difficulty::INTERMEDIATE);
        game.start();

        REQUIRE(!game.has_ended);
        REQUIRE(game.first_click);

        unsigned int count = 0;
        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                if (game.board.get_tile(x, y).is_bomb)
                {
                    count++;
                }
            }
        }
        REQUIRE(count == 40);
    }

    SECTION("left_bombs()")
    {
        Game game;
        game.set_level(Difficulty::INTERMEDIATE);
        game.start();

        REQUIRE(game.left_bombs() == 40);

        int count = 0;
        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                if (game.board.get_tile(x, y).is_bomb)
                {
                    game.board.get_tile(x, y).flag();
                    REQUIRE(game.left_bombs() == 40 - ++count);
                }
            }
        }

        REQUIRE(game.left_bombs() == 0);

        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                if (game.board.get_tile(x, y).is_flagged)
                {
                    game.board.get_tile(x, y).unflag();
                    REQUIRE(game.left_bombs() == 40 - --count);
                }
            }
        }
    }

    SECTION("is_game_over()")
    {
        Game game;
        game.set_level(Difficulty::INTERMEDIATE);
        game.start();

        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                if (game.board.get_tile(x, y).is_bomb)
                {
                    REQUIRE(game.board.get_tile(x, y).is_covered);
                }
            }
        }

        REQUIRE_FALSE(game.is_game_over());

        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                if (game.board.get_tile(x, y).is_bomb)
                {
                    game.board.get_tile(x, y).uncover();
                    break;
                }
            }
        }
        REQUIRE(game.is_game_over());

        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                if (game.board.get_tile(x, y).is_bomb)
                {
                    REQUIRE_FALSE(game.board.get_tile(x, y).is_covered);
                }
            }
        }
    }

    SECTION("is_game_won()")
    {
        Game game;
        game.set_level(Difficulty::INTERMEDIATE);
        game.start();

        REQUIRE_FALSE(game.is_game_won());

        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                if (!game.board.get_tile(x, y).is_bomb)
                {
                    game.board.get_tile(x, y).uncover();
                }
            }
        }
        REQUIRE(game.is_game_won());
    }

    SECTION("play_again()")
    {
        Game game;
        game.set_level(Difficulty::INTERMEDIATE);
        game.start();

        game.board.get_tile(0, 0).flag();

        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                game.uncover_tile(x, y);
            }
        }

        REQUIRE(game.is_game_over());
        REQUIRE(game.has_ended);
        REQUIRE_FALSE(game.first_click);

        game.play_again();

        for (unsigned int x = 0; x < game.board.HEIGHT; x++)
        {
            for (unsigned int y = 0; y < game.board.WIDTH; y++)
            {
                REQUIRE(game.board.get_tile(x, y).is_covered);
                REQUIRE(!game.board.get_tile(x, y).is_flagged);
            }
        }

        REQUIRE_FALSE(game.has_ended);
        REQUIRE(game.first_click);
    }
}