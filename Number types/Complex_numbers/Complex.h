#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

#include <vector>
#include <cmath>
#include <fstream>

template<class vt>
class complex {
private:
    vt real, imag;
public:
    //! Rule of five
    complex();
    complex(const vt& scalar);
    complex(const vt& _real, const vt& _imag);

    complex(const complex& other);
    complex(complex&& other) noexcept;

    complex& operator=(const complex& other);
    complex& operator=(complex&& other) noexcept;

    //! Methods

    double argument() const;
    double length() const;
    complex conjugate() const;

    vt _real() const;
    vt _imag() const;

    std::vector<complex> roots(int n) const;

    //! In-class arithmetic operators

    complex& operator+=(const complex& other);
    complex& operator-=(const complex& other);
    complex& operator/=(const complex& other);
    complex& operator*=(const complex& other);

    complex operator-() const;
    complex operator+() const;

    //! Comparison operators
};

#endif // COMPLEX_H
