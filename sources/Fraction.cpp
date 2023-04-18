#include "Fraction.hpp"

using namespace ariel;
using namespace std;

// fraction constructor
Fraction::Fraction(int num, int den)
{
    if (den == 0)
    {
        throw invalid_argument("Error: Division by zero!");
    }

    this->numerator = num;
    this->denominator = den;
    // do I need to reduce every fraction when it is created?
}

// getters and setters

void Fraction::setNumerator(int num)
{
    this->numerator = num;
}

void Fraction::setDenominator(int den)
{
    this->denominator = den;
}

const int &Fraction::getNumerator()
{
    return this->numerator;
}

const int &Fraction::getDenominator()
{
    return this->denominator;
}

Fraction Fraction::operator+(const Fraction &other) const
{
    // using corss-multipication
    int num = (this->numerator * other.denominator) + (other.numerator * this->denominator);
    int den = this->denominator * other.denominator;
    return Fraction(num, den).reduce();
}

Fraction Fraction::operator-(const Fraction &other) const
{
    int num = (this->numerator * other.denominator) - (other.numerator * this->denominator);
    int den = this->denominator * other.denominator;
    return Fraction(num, den).reduce();
}

Fraction Fraction::operator*(const Fraction &other) const
{
    // normal multiplication
    int num = this->numerator * other.numerator;
    int den = this->denominator * other.denominator;
    return Fraction(num, den).reduce();
}

Fraction Fraction::operator/(const Fraction &other) const
{
    // Division is cross multiplication
    int num = this->numerator * other.denominator;
    int den = this->denominator * other.numerator;
    if (den == 0)
    {
        throw invalid_argument("Error: Division by zero!");
    }
    return Fraction(num, den).reduce();
}

bool Fraction::operator==(const Fraction &other) const
{
    // compare numerator with numerator and denom with denom
    return (numerator == other.numerator) && (denominator == other.denominator);
}

bool Fraction::operator>(const Fraction &other) const
{
    // comparting numerator after cross-multiplication
    return (numerator * other.denominator) > (other.numerator * denominator);
}

bool Fraction::operator<(const Fraction &other) const
{
    // comparting numerator after cross-multiplication
    return (numerator * other.denominator) < (other.numerator * denominator);
}

bool Fraction::operator>=(const Fraction &other) const
{
    // comparting numerator after cross-multiplication or comapring equals
    return ((numerator * other.denominator) > (other.numerator * denominator)) || (numerator == other.numerator && denominator == other.denominator);
}

bool Fraction::operator<=(const Fraction &other) const
{
    // comparting numerator after cross-multiplication or comparing equals
    return ((numerator * other.denominator) < (other.numerator * denominator)) || (numerator == other.numerator && denominator == other.denominator);
}

Fraction &Fraction::operator++()
{
    // reduce the fraction first (maybe remove this since it might get reduced in constructor)
    this->reduce();

    // by adding the denomiator to the numerator we are adding 1
    numerator += denominator;

    // return reference to the updates object so you can carry on working with it updated
    return *this;
}

Fraction Fraction::operator++(int)
{

    // reduce the fraction first (maybe remove this since it might get reduced in constructor)
    this->reduce();

    // Create a copy of the original object
    Fraction orginal = *this;

    // Increment the value of the object by one
    numerator += denominator;

    // Return the original object before increment
    return orginal;
}

Fraction &Fraction::operator--()
{
    // reduce the fraction first (maybe remove this since it might get reduced in constructor)
    this->reduce();

    // Decrement the value by 1
    numerator -= denominator;

    // return reference to the updates object so you can carry on working with it updated
    return *this;
}

Fraction Fraction::operator--(int)
{
    // reduce the fraction first (maybe remove this since it might get reduced in constructor)
    this->reduce();

    // Create a copy of the original object
    Fraction orginal = *this;

    // Decrement the value of the object by one
    numerator -= denominator;

    // Return the original object before increment
    return orginal;
}

// Helper function to reduce a fraction to its simplest form
Fraction Fraction::reduce() const
{
    int gcdVal = gcd(numerator, denominator); // Find the greatest common divisor (GCD) of the numerator and denominator
    int num = numerator / gcdVal;             // Divide numerator by GCD to get the reduced numerator
    int den = denominator / gcdVal;           // Divide denominator by GCD to get the reduced denominator
    return Fraction(num, den);                // Return the reduced fraction as a new Fraction object
}

// Helper function to calculate the greatest common divisor (GCD) of two integers
int Fraction::gcd(int a, int b) const
{
    // Euclidean algorithm for finding the GCD
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}
