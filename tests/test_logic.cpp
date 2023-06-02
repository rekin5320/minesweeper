#include "catch.hpp"


TEST_CASE("Test Fail") {
    REQUIRE(1 == 3);
}

TEST_CASE("Test Pass") {
    REQUIRE(1 == 1);
}
