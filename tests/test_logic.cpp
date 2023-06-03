#include <stdexcept>

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
        REQUIRE_THROWS_AS(tile.uncover(), std::invalid_argument);
    }

    SECTION("flag() & unflag()")
    {
        REQUIRE_THROWS_AS(tile.unflag(), std::invalid_argument);
        tile.flag();
        REQUIRE(tile.is_flagged);
        REQUIRE_THROWS_AS(tile.flag(), std::invalid_argument);
        tile.unflag();
        REQUIRE(!tile.is_flagged);
        REQUIRE_THROWS_AS(tile.unflag(), std::invalid_argument);
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

        SECTION("count_adjacent_bombs")
        {
            board.random.seed(37);
            board.generate_bombs(2);
            board.count_adjacent_bombs();

            // board.print_board();
            // 1 2 2
            // 1 X X

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

        SECTION("count_adjacent_bombs")
        {
            board.random.seed(21);
            board.generate_bombs(7);
            board.count_adjacent_bombs();

            // board.print_board();
            // 0 0 0 1 1
            // 1 1 0 2 X
            // X 3 3 5 X
            // 2 X X X X

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

TEST_CASE("Game")
{
    SECTION("BEGINNER")
    {
        Game game = Game(Difficulty::BEGINNER);

        REQUIRE(game.board.WIDTH == 9);
        REQUIRE(game.board.HEIGHT == 9);
        REQUIRE(game.num_bombs == 10);
    }

    SECTION("INTERMEDIATE")
    {
        Game game = Game(Difficulty::INTERMEDIATE);

        REQUIRE(game.board.WIDTH == 16);
        REQUIRE(game.board.HEIGHT == 16);
        REQUIRE(game.num_bombs == 40);
    }

    SECTION("EXPERT")
    {
        Game game = Game(Difficulty::EXPERT);

        REQUIRE(game.board.WIDTH == 30);
        REQUIRE(game.board.HEIGHT == 16);
        REQUIRE(game.num_bombs == 99);
    }

    SECTION("CUSTOM")
    {
        Game game = Game(Difficulty::CUSTOM, 5, 4, 7);

        REQUIRE(game.board.WIDTH == 5);
        REQUIRE(game.board.HEIGHT == 4);
        REQUIRE(game.num_bombs == 7);
    }

    SECTION("CUSTOM_MISSING_ARGS")
    {
        REQUIRE_THROWS_AS(Game(Difficulty::CUSTOM, 5, 4), std::invalid_argument);
        REQUIRE_THROWS_AS(Game(Difficulty::CUSTOM), std::invalid_argument);
    }

    SECTION("start()")
    {
        Game game = Game(Difficulty::INTERMEDIATE);
        game.start();

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

    SECTION("is_game_over()")
    {
        Game game = Game(Difficulty::INTERMEDIATE);
        game.start();

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
    }

    SECTION("is_game_won()")
    {
        Game game = Game(Difficulty::INTERMEDIATE);
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
}