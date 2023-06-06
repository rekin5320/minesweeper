#include "catch.hpp"
#include "../tile.hpp"


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
