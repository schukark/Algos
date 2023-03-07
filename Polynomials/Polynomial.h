#pragma once
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>
#include <fstream>
#include <cmath>

template<typename T>
class polynomial {
private:
    std::vector<T> coefficients;
public:
    //! Rule of 5
    polynomial(const T& scalar);
    polynomial(const std::vector<T>& coefficients);

    polynomial(const polynomial& other);
    polynomial(polynomial&& other) noexcept;

    polynomial& operator=(const polynomial& other);
    polynomial& operator=(polynomial&& other) noexcept;

    ~polynomial() = default;

    //! Comparison operators

    bool operator==(const polynomial& other) const;
    bool operator!=(const polynomial& other) const;

    //! Methods and non-arithmetic operators

    std::size_t degree() const;
    T& operator[] (std::size_t index);
    const T& operator[] (std::size_t index) const;

    polynomial differentiate() const;
    polynomial integrate(const T& constant) const;

    T operator() (const T& point) const;
    std::vector<T>& coef();
    const std::vector<T>& coef() const;

    //! Linear in-class opeartors

    polynomial& operator+= (const polynomial& other);
    polynomial& operator-= (const polynomial& other);

    polynomial operator+() const;
    polynomial operator-() const;

    polynomial& operator*=(const polynomial& other);
    polynomial& operator/=(const polynomial& other);
    polynomial& operator%=(const polynomial& other);
};

#endif // POLYNOMIAL_H