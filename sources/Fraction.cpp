#include "Fraction.hpp"

using namespace ariel;
using namespace std;

// fraction constructor
Fraction::Fraction(int num, int den)
{
    if (den == 0)
    {
        throw runtime_error("Can't create fraction: Denominator cannot be 0");
    }

    this->numerator = num;
    this->denominator = den;
    // do I need to reduce every fraction when it is created?
}
