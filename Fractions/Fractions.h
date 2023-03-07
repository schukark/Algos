#pragma once
#ifndef FRACTIONS_H
#define FRACTIONS_H

#include <cmath>
#include <numeric>
#include <fstream>
#include <string>

template<class T>
bool equal(const T& a, const T& b, const double eps = 1e-6) {
    return std::fabs(a - b) < eps;
}

template<class T>
class fraction {
private:
    T numerator, denominator;
public:
    //! Rule of five
    fraction();
    fraction(T scalar);
    fraction(T numerator, T denominator);
    fraction(const fraction& other);
    fraction(fraction&& other) noexcept;

    fraction& operator=(const fraction& other);
    fraction& operator=(fraction&& other) noexcept;

    ~fraction() = default;

    //! Comprsion operators

    bool operator<(const fraction& other) const;
    bool operator>(const fraction& other) const;
    bool operator<=(const fraction& other) const;
    bool operator>=(const fraction& other) const;
    bool operator==(const fraction& other) const;
    bool operator!=(const fraction& other) const;

    //! Arithmetic in-class operators

    fraction operator+=(const fraction& other) const;
    fraction operator-=(const fraction& other) const;
    fraction operator*=(const fraction& other) const;
    fraction operator/=(const fraction& other) const;

    //! Different methods

    fraction inverse() const;
    long double value() const;

    T num() const;
    T denom() const;
};

#endif // FRACTIONS_H