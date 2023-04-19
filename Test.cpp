#include "doctest.h"
#include "sources/Fraction.hpp"

namespace ariel
{
    TEST_CASE("bad input")
    {
        CHECK_THROWS_AS(Fraction(0, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, 1), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(-1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, -1), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, 1), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(-1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, -1), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, 1), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(-1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, -1), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, 1), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(-1, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction(0, -1), std::invalid_argument);
    }

}