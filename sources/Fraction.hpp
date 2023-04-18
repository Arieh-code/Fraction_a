#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
using namespace std;
namespace ariel
{
    class Fraction
    {
        int numerator;
        int denominator;

    public:
        const int &getNumerator();
        const int &getDenominator();
        void setNumerator(int);
        void setDenominator(int);

        Fraction(int num, int den);
        // mathematical operation on two Fraction objects therefore they are const
        // I am sending a  reference and not a value is for efficiency not creating another object
        // and using const to make sure the other isn't modified inside the function
        Fraction operator+(const Fraction &other) const;
        // Fraction operator+(float f) const;
        Fraction operator-(const Fraction &other) const;
        // Fraction operator-(float f) const;
        Fraction operator*(const Fraction &other) const;
        // Fraction operator*(float f) const;
        Fraction operator/(const Fraction &other) const;
        // Fraction operator/(float f) const;

        // bool functions
        bool operator==(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;

        Fraction &operator++();   // pre-increment
        Fraction operator++(int); // post-increment
        Fraction &operator--();   // pre-decrement
        Fraction operator--(int); // post-decrement

        // float operators
        Fraction operator+(const float f) const;
        Fraction operator-(const float f) const;
        Fraction operator*(const float f) const;
        Fraction operator/(const float f) const;

        // float bool operators
        bool operator==(const float f) const;
        bool operator>(const float f) const;
        bool operator<(const float f) const;
        bool operator>=(const float f) const;
        bool operator<=(const float f) const;

        // Helper functions
        Fraction reduce() const;
        int gcd(int a, int b) const;

        friend std::ostream &operator<<(std::ostream &os, const Fraction &frac);
        friend std::istream &operator>>(std::istream &is, Fraction &frac);
    };

    Fraction operator+(float f, const Fraction &frac);
    Fraction operator-(float f, const Fraction &frac);
    Fraction operator*(float f, const Fraction &frac);
    Fraction operator/(float f, const Fraction &frac);
    bool operator==(float f, const Fraction &frac);
    bool operator>(float f, const Fraction &frac);
    bool operator>=(float f, const Fraction &frac);
    bool operator<(float f, const Fraction &frac);
    bool operator<=(float f, const Fraction &frac);
}

#endif // FRACTION_HPP