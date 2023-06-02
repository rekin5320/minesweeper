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
