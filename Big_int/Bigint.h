#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <vector>
#include <iostream>

class bigint {
private:
    std::vector<int> digits;
    int sign;
public:
    //! Rule of five
    bigint();
    bigint(long long value);
    bigint(const bigint& other);
    ~bigint() = default;

    bigint& operator=(long long value);
    bigint& operator=(const bigint& other);

    //! In-class methods

    std::string to_string() const;
    bigint abs() const;
    void trim_zeros();

    std::vector<int>& _digits();
    const std::vector<int>& _digits() const;

    int& _sign();
    const int& _sign() const;

    explicit operator bool() const;

    bigint operator-() const;
    bigint operator+() const;

    //! In-class arithmetic operators

    bigint& operator+=(const bigint& other);
    bigint& operator-=(const bigint& other);
    bigint& operator*=(const bigint& other);

    bigint& operator++();
    const bigint operator++(int);

    bigint& operator--();
    const bigint operator--(int);
};


#endif /// BIGINT_H.