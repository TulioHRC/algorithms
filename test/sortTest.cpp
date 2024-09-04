#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdint>

uint32_t factorial(uint32_t number) {
    return number <= 1 ? number : factorial(number-1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 3);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}
