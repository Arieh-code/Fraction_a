#include "doctest.h"
#include "sources/Fraction.hpp"

namespace ariel
{
    TEST_CASE("Constructor getters and setters tests")
    {
        CHECK_THROWS_AS(Fraction(0, 0), std::invalid_argument);
        CHECK_NOTHROW(Fraction(0, 1));
        Fraction test = Fraction(1, 1);
        CHECK_EQ(test.getNumerator(), 1);
        CHECK_EQ(test.getDenominator(), 1);
        test.setNumerator(2);
        test.setDenominator(2);
        CHECK_EQ(test.getNumerator(), 2);
        CHECK_EQ(test.getDenominator(), 2);
        Fraction test2 = Fraction(4, 8);
        // testing the reduce
        CHECK_EQ(test2.getDenominator(), 2);
        CHECK_EQ(test2.getNumerator(), 1);
    }

    TEST_CASE("Operator tests")
    {
        Fraction testA = Fraction(1, 1);
        Fraction testB = Fraction(1, 2);
        Fraction testC = testA + testB;
        Fraction testD = testA - testB;
        Fraction testE = testA * testB;
        Fraction testF = testA / testB;
        CHECK_EQ(testC.getDenominator(), 2);
        CHECK_EQ(testC.getNumerator(), 3);
        CHECK_EQ(testD.getDenominator(), 2);
        CHECK_EQ(testD.getNumerator(), 1);
        CHECK_EQ(testE.getDenominator(), 2);
        CHECK_EQ(testE.getNumerator(), 1);
        CHECK_EQ(testF.getDenominator(), 1);
        CHECK_EQ(testF.getNumerator(), 2);
        CHECK_FALSE(testC == testD);
        CHECK_GT(testA, testB);
        CHECK_LT(testE, testA);
    }

    TEST_CASE("Arithmetic float tests")
    {
        Fraction testA = Fraction(5, 3);
        float numA = 2.4215;
        CHECK_NOTHROW(numA + testA);
        CHECK_NOTHROW(testA * numA);
        Fraction res1 = Fraction(6133, 1500);
        CHECK_EQ((testA + numA), res1);
        Fraction res2 = Fraction(1211, 300);
        CHECK_EQ((testA * numA), res2);
        Fraction res3 = Fraction(-1133, 1500);
        CHECK_EQ((testA - numA), res3);
        CHECK_EQ((numA + testA), res1);
        CHECK_EQ((numA * testA), res2);
    }

}