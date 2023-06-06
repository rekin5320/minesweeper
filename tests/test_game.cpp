#include "catch.hpp"
#include "../game.hpp"

TEST_CASE("Game")
{
    SECTION("BEGINNER")
    {
        Game game;
        game.set_difficulty(Difficulty::BEGINNER);

        REQUIRE(game.get_board().width == 9);
        REQUIRE(game.get_board().height == 9);
        REQUIRE(game.get_num_bombs() == 10);
    }

    SECTION("INTERMEDIATE")
    {
        Game game;
        game.set_difficulty(Difficulty::INTERMEDIATE);

        REQUIRE(game.get_board().width == 16);
        REQUIRE(game.get_board().height == 16);
        REQUIRE(game.get_num_bombs() == 40);
    }

    SECTION("EXPERT")
    {
        Game game;
        game.set_difficulty(Difficulty::EXPERT);

        REQUIRE(game.get_board().width == 30);
        REQUIRE(game.get_board().height == 16);
        REQUIRE(game.get_num_bombs() == 99);
    }

    SECTION("CUSTOM")
    {
        Game game;
        game.set_difficulty(Difficulty::CUSTOM, 5, 4, 7);

        REQUIRE(game.get_board().width == 5);
        REQUIRE(game.get_board().height == 4);
        REQUIRE(game.get_num_bombs() == 7);
    }

    SECTION("CUSTOM_MISSING_ARGS")
    {
        Game game1;
        Game game2;
        REQUIRE_THROWS_AS(game1.set_difficulty(CUSTOM, 6, 7), std::invalid_argument);
        REQUIRE_THROWS_AS(game2.set_difficulty(CUSTOM), std::invalid_argument);
    }

    SECTION("start()")
    {
        Game game;
        game.set_difficulty(Difficulty::INTERMEDIATE);

        REQUIRE(!game.get_has_started());
        game.start();

        REQUIRE(game.get_has_started());
        REQUIRE(!game.get_has_ended());
        REQUIRE(game.get_first_click());

        unsigned int count = 0;
        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                if (game.get_board().get_tile(x, y).is_bomb)
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
        game.set_difficulty(Difficulty::INTERMEDIATE);
        game.start();

        REQUIRE(game.left_bombs() == 40);

        int count = 0;
        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                if (game.get_board().get_tile(x, y).is_bomb)
                {
                    game.get_board().get_tile(x, y).flag();
                    REQUIRE(game.left_bombs() == 40 - ++count);
                }
            }
        }

        REQUIRE(game.left_bombs() == 0);

        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                if (game.get_board().get_tile(x, y).is_flagged)
                {
                    game.get_board().get_tile(x, y).unflag();
                    REQUIRE(game.left_bombs() == 40 - --count);
                }
            }
        }
    }

    SECTION("is_game_over()")
    {
        Game game;
        game.set_difficulty(Difficulty::INTERMEDIATE);
        game.start();

        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                if (game.get_board().get_tile(x, y).is_bomb)
                {
                    REQUIRE(game.get_board().get_tile(x, y).is_covered);
                }
            }
        }

        REQUIRE_FALSE(game.is_game_over());

        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                if (game.get_board().get_tile(x, y).is_bomb)
                {
                    game.get_board().get_tile(x, y).uncover();
                    break;
                }
            }
        }
        REQUIRE(game.is_game_over());

        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                if (game.get_board().get_tile(x, y).is_bomb)
                {
                    REQUIRE_FALSE(game.get_board().get_tile(x, y).is_covered);
                }
            }
        }
    }

    SECTION("is_game_won()")
    {
        Game game;
        game.set_difficulty(Difficulty::INTERMEDIATE);
        game.start();

        REQUIRE_FALSE(game.is_game_won());

        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                if (!game.get_board().get_tile(x, y).is_bomb)
                {
                    game.get_board().get_tile(x, y).uncover();
                }
            }
        }
        REQUIRE(game.is_game_won());
    }

    SECTION("play_again()")
    {
        Game game;
        game.set_difficulty(Difficulty::INTERMEDIATE);
        game.start();

        game.get_board().get_tile(0, 0).flag();

        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                game.uncover_tile(x, y);
            }
        }

        REQUIRE(game.get_has_started());
        REQUIRE(game.is_game_over());
        REQUIRE(game.get_has_ended());
        REQUIRE_FALSE(game.get_first_click());

        game.play_again();
        REQUIRE(game.get_has_started());

        for (unsigned int x = 0; x < game.get_board().height; x++)
        {
            for (unsigned int y = 0; y < game.get_board().width; y++)
            {
                REQUIRE(game.get_board().get_tile(x, y).is_covered);
                REQUIRE(!game.get_board().get_tile(x, y).is_flagged);
            }
        }

        REQUIRE_FALSE(game.get_has_ended());
        REQUIRE(game.get_first_click());
    }
}