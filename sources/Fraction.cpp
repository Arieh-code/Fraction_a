#include "Fraction.hpp"
#include <cmath> // for round()
#include <typeinfo>
#include <limits> // to check that there is no overflow

using namespace ariel;
using namespace std;

int MAX_INT = numeric_limits<int>::max();
int MIN_INT = numeric_limits<int>::min();

// fraction constructor
Fraction::Fraction(int num, int den)
{
    if (den == 0)
    {
        throw invalid_argument("Error: Division by zero!");
    }
    if ((typeid(num)) != typeid(int) || (typeid(den)) != typeid(int))
    {
        throw invalid_argument("Error: Numbers must be integers!");
    }
    // if number has two negative numbers change to positive
    if (num < 0 && den < 0)
    {

        num *= -1;
        den *= -1;
    }

    // if den is negative and num is positive switch between the signs
    if (num > 0 && den < 0)
    {
        num *= -1;
        den *= -1;
    }

    if (num != 0)
    {
        this->numerator = num;
        this->denominator = den;
        int BNum = gcd(numerator, denominator);
        numerator /= BNum;
        denominator /= BNum;
    }
    else
    {
        // numerator is zero so whole number is zero
        this->numerator = 0;
        this->denominator = den;
    }
}

Fraction::Fraction(float frac)
{
    if (frac == 0.0)
    {
        throw invalid_argument("Error: 0 isn't a valid fraction!");
    }
    if (typeid(frac) != typeid(float))
    {
        throw invalid_argument("Error: frac must be a float");
    }

    // turn float frac into fraction
    int intF = static_cast<int>(frac * 1000 + 0.5);

    int den = 1000;

    this->numerator = intF;
    this->denominator = den;

    int BNum = gcd(numerator, denominator);
    numerator /= BNum;
    denominator /= BNum;
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

const int &Fraction::getNumerator() const
{
    return this->numerator;
}

const int &Fraction::getDenominator() const
{
    return this->denominator;
}

Fraction Fraction::operator+(const Fraction &other) const
{
    // using cross-multiplication
    if (other.numerator == 0 && other.denominator == 0)
    {
        return (*this);
    }
    long int num = (static_cast<long int>(this->numerator) * other.denominator) + (static_cast<long int>(other.numerator) * this->denominator);
    long int den = static_cast<long int>(this->denominator) * other.denominator;
    if (num > MAX_INT || den > MAX_INT || num < MIN_INT || den < MIN_INT)
    {
        throw overflow_error("The value of the numerator or denominator has exceeded the limit");
    }
    return Fraction(num, den).reduce();
}

Fraction Fraction::operator-(const Fraction &other) const
{
    long int num = (static_cast<long int>(this->numerator) * other.denominator) - (static_cast<long int>(other.numerator) * this->denominator);
    long int den = static_cast<long int>(this->denominator) * other.denominator;
    if (num > MAX_INT || den > MAX_INT || num < MIN_INT || den < MIN_INT)
    {
        throw overflow_error("The value of the numerator or denominator has exceeded the limit");
    }
    return Fraction(num, den).reduce();
}

Fraction Fraction::operator*(const Fraction &other) const
{
    // normal multiplication
    long int num = static_cast<long int>(this->numerator) * other.numerator;
    long int den = static_cast<long int>(this->denominator) * other.denominator;
    if (num > MAX_INT || den > MAX_INT || num < MIN_INT || den < MIN_INT)
    {
        throw overflow_error("The value of the numerator or denominator has exceeded the limit");
    }
    return Fraction(num, den).reduce();
}

Fraction Fraction::operator/(const Fraction &other) const
{
    // Division is cross multiplication
    long int num = static_cast<long int>(this->numerator) * other.denominator;
    long int den = static_cast<long int>(this->denominator) * other.numerator;
    if (den == 0)
    {
        throw runtime_error("Error: Division by zero!");
    }
    if (num > MAX_INT || den > MAX_INT || num < MIN_INT || den < MIN_INT)
    {
        throw overflow_error("The value of the numerator or denominator has exceeded the limit");
    }
    return Fraction(num, den).reduce();
}

bool Fraction::operator==(const Fraction &other) const
{
    // compare numerator with numerator and denom with denom
    if (numerator == 0 && other.numerator == 0)
    {
        return true;
    }
    float frac = (numerator + 0.0) / (denominator + 0.0);
    float otherF = (other.numerator + 0.0) / (other.denominator + 0.0);

    return ((numerator == other.numerator) && (denominator == other.denominator)) || (round(frac * 1000.0) / 1000.0) == (round(otherF * 1000.0) / 1000.0);
}

bool Fraction::operator>(const Fraction &other) const
{
    // comparing numerator after cross-multiplication
    return (numerator * other.denominator) > (other.numerator * denominator);
}

bool Fraction::operator<(const Fraction &other) const
{
    // comparing numerator after cross-multiplication
    return (numerator * other.denominator) < (other.numerator * denominator);
}

bool Fraction::operator>=(const Fraction &other) const
{
    // comparing numerator after cross-multiplication or comparing equals
    return ((numerator * other.denominator) > (other.numerator * denominator)) || (numerator == other.numerator && denominator == other.denominator);
}

bool Fraction::operator<=(const Fraction &other) const
{
    // comparing numerator after cross-multiplication or comparing equals
    return ((numerator * other.denominator) < (other.numerator * denominator)) || (numerator == other.numerator && denominator == other.denominator);
}

Fraction &Fraction::operator++()
{
    // by adding the denominator to the numerator we are adding 1
    numerator += denominator;

    // return reference to the updates object so you can carry on working with it updated
    return *this;
}

Fraction Fraction::operator++(int)
{
    // Create a copy of the original object
    Fraction original = *this;

    // Increment the value of the object by one
    numerator += denominator;

    // Return the original object before increment may need to reduce original value
    return original;
}

Fraction &Fraction::operator--()
{
    // Decrement the value by 1
    numerator -= denominator;

    // return reference to the updates object so you can carry on working with it updated
    return *this;
}

Fraction Fraction::operator--(int)
{

    // Create a copy of the original object
    Fraction original = *this;

    // Decrement the value of the object by one
    numerator -= denominator;

    // Return the original object before increment may need to reduce original value
    return original;
}

Fraction Fraction::operator+(const float frac)
{
    // Turn float into fraction then used already implemented operator +
    Fraction fracF = floatToFraction(frac);
    return (*this) + fracF;
}

Fraction Fraction::operator-(const float frac)
{
    // Turn float into fraction then used already implemented operator -
    Fraction fracF = floatToFraction(frac);
    return (*this) - fracF;
}

Fraction Fraction::operator*(const float frac)
{
    // Turn float into fraction then used already implemented operator *
    Fraction fracF = floatToFraction(frac);
    return (*this) * fracF;
}

Fraction Fraction::operator/(const float frac)
{
    // Turn float into fraction then used already implemented operator /
    if (frac == 0)
    {
        throw runtime_error("Can't divide by zero");
    }
    Fraction fracF = floatToFraction(frac);
    return (*this) / fracF;
}

bool Fraction::operator==(const float frac)
{
    // // Turn float into fraction then used already implemented operator ==
    // Fraction fracF = floatToFraction(frac);
    // // float otherF = (this->numerator + 0.0) / (this->denominator + 0.0);
    // return (*this) == fracF;
    // // return (frac == (round(otherF * 1000.0) / 1000.0));
    return (round(((numerator + 0.0) / (denominator + 0.0)) * 1000.0) / 1000.0) == round(frac * 1000.0) / 1000.0;
}

bool Fraction::operator>(const float frac)
{
    // Turn float into fraction then used already implemented operator >
    Fraction fracF = floatToFraction(frac);
    return (*this) > fracF;
}

bool Fraction::operator<(const float frac)
{
    // Turn float into fraction then used already implemented operator <
    Fraction fracF = floatToFraction(frac);
    return (*this) < fracF;
}

bool Fraction::operator>=(const float frac)
{
    // Turn float into fraction then used already implemented operator >=
    Fraction fracF = floatToFraction(frac);
    return (*this) >= fracF;
}

bool Fraction::operator<=(const float frac)
{
    // Turn float into fraction then used already implemented operator <=
    Fraction fracF = floatToFraction(frac);
    return (*this) <= fracF;
}

ostream &ariel::operator<<(std::ostream &outs, const Fraction &f)
{
    outs << f.numerator << "/" << f.denominator;
    return outs;
}

istream &ariel::operator>>(std::istream &ins, Fraction &f)
{
    int num, den;
    if (ins >> num >> den)
    {
        if (den == 0)
        {
            throw runtime_error("Denominator can't be zero!");
        }
        if (num < 0 && den < 0)
        {

            num *= -1;
            den *= -1;
        }

        // if den is negative and num is positive switch between the signs
        if (num > 0 && den < 0)
        {
            num *= -1;
            den *= -1;
        }

        if (num != 0)
        {
            f.numerator = num;
            f.denominator = den;
        }

        else
        {
            // numerator is zero so whole number is zero
            f.numerator = 0;
            f.denominator = den;
        }
    }
    else
    {
        throw runtime_error("Not enough arguments: ins needs to have num and den");
    }

    return ins;
}

// // Helper function to reduce a fraction to its simplest form
Fraction Fraction::reduce() const
{
    int gcdVal = gcd(numerator, denominator); // Find the greatest common divisor (GCD) of the numerator and denominator
    int num = numerator / gcdVal;             // Divide numerator by GCD to get the reduced numerator
    int den = denominator / gcdVal;           // Divide denominator by GCD to get the reduced denominator
    return Fraction(num, den);                // Return the reduced fraction as a new Fraction object
}

Fraction Fraction::floatToFraction(const float frac)
{

    if (frac < 0)
    {
        int intF = static_cast<int>(frac * 1000 - 0.5);
        int den = 1000;
        return Fraction(intF, den).reduce();
    }
    else
    {
        int intF = static_cast<int>(frac * 1000 + 0.5);
        int den = 1000;
        return Fraction(intF, den).reduce();
    }
}

Fraction floatToFraction(const float frac)
{
    if (frac < 0)
    {
        int intF = static_cast<int>(frac * 1000 - 0.5);
        int den = 1000;
        return Fraction(intF, den).reduce();
    }
    else
    {
        int intF = static_cast<int>(frac * 1000 + 0.5);
        int den = 1000;
        return Fraction(intF, den).reduce();
    }
}

// Helper function to calculate the greatest common divisor (GCD) of two integers
int Fraction::gcd(int num1, int num2) const
{
    num1 = abs(num1);
    num2 = abs(num2);
    // Euclidean algorithm for finding the GCD
    if (num2 == 0)
    {
        return num1;
    }
    else
    {
        return gcd(num2, (num1 % num2));
    }
}

Fraction ariel::operator+(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    // return Fraction1 + frac;
    // int num = (this->numerator * other.denominator) + (other.numerator * this->denominator);
    int num = (Fraction1.getNumerator() * frac.getDenominator()) + (frac.getNumerator() * Fraction1.getDenominator());
    // int den = this->denominator * other.denominator;
    int den = Fraction1.getDenominator() * frac.getDenominator();
    return Fraction(num, den).reduce();
}

Fraction ariel::operator-(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    return Fraction1 - frac;
}

Fraction ariel::operator*(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    return Fraction1 * frac;
}

Fraction ariel::operator/(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    return Fraction1 / frac;
}

bool ariel::operator==(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    // return Fraction1 == frac;
    float fNum1 = round(fNum * 1000.0) / 1000.0;
    float fractionD = round(((frac.getNumerator() + 0.0) / (frac.getDenominator() + 0.0)) * 1000.0) / 1000.0;

    return ((Fraction1.getNumerator() == frac.getNumerator()) && (Fraction1.getDenominator() == frac.getDenominator())) || fNum1 == fractionD;
}

bool ariel::operator>(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    return Fraction1 > frac;
}

bool ariel::operator<(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    return Fraction1 < frac;
}

bool ariel::operator>=(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    return Fraction1 >= frac;
}

bool ariel::operator<=(const float fNum, const Fraction &frac)
{
    Fraction Fraction1 = floatToFraction(fNum);
    return Fraction1 <= frac;
}
