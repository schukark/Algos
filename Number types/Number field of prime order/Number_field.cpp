#include "Number_field.h"

//! Rule of five

template <std::size_t p>
number_field<p>::number_field(): number(0) {}

template <std::size_t p>
number_field<p>::number_field(int _number) {
    if (_number >= 0) number = _number % p;
    else number = p - (abs(_number) % p);
}

template<std::size_t p>
number_field<p>::number_field(const number_field<p>& other): number(other.number) {}

template<std::size_t p>
number_field<p>::number_field(number_field<p>&& other) noexcept {
    number = other.number;
    other.number = 0;
}

template<std::size_t p>
number_field<p>& number_field<p>::operator=(const number_field<p>& other) {
    number = other.number;
    return *this;
}

template<std::size_t p>
number_field<p>& number_field<p>::operator=(number_field<p>&& other) noexcept {
    number = other.number;
    other.number = 0;
    return *this;
}

//! Bool operators

template<std::size_t p>
bool number_field<p>::operator<(const number_field<p>& other) const {
    return number < other.number;
}

template<std::size_t p>
bool number_field<p>::operator>(const number_field<p>& other) const {
    return other < *this;
}

template<std::size_t p>
bool number_field<p>::operator<=(const number_field<p>& other) const {
    return !(*this > other);
}

template<std::size_t p>
bool number_field<p>::operator>=(const number_field<p>& other) const {
    return !(*this < other);
}

template<std::size_t p>
bool number_field<p>::operator==(const number_field<p>& other) const {
    return (*this <= other) && (*this >= other);
}

template<std::size_t p>
bool number_field<p>::operator!=(const number_field<p>& other) const {
    return !(other == *this);
}

//! In-class arithmetic operators

template<std::size_t p>
number_field<p>& number_field<p>::operator+=(const number_field<p>& other) {
    int result = number + other.number;
    *this = number_field<p>(result);

    return *this;
}

template<std::size_t p>
number_field<p>& number_field<p>::operator-=(const number_field<p>& other) {
    int result = number - other.number;
    *this = number_field<p>(result);

    return *this;
}

template<std::size_t p>
number_field<p>& number_field<p>::operator*=(const number_field<p>& other) {
    int result = number * other.number;
    *this = number_field<p>(result);

    return *this;
}

template<std::size_t p>
number_field<p>& number_field<p>::operator/=(const number_field<p>& other) {
    *this *= other.inverse();
    return *this;
}

template <std::size_t p>
number_field<p> &number_field<p>::operator^=(int power) {
    *this = (*this) ^ power;
    return *this;
}

template <std::size_t p>
number_field<p> number_field<p>::operator+() const {
    return number_field();
}

template <std::size_t p>
number_field<p> number_field<p>::operator-() const {
    return number_field(-number);
}

//! Methods

template<std::size_t p>
number_field<p> number_field<p>::inverse() const {
    for (int i = 1; i < p; i++) {
        if (i * number % p == 1) return number_field<p>(i);
    }

    throw std::runtime_error("Division by zero");
}

template<std::size_t p>
int number_field<p>::get_number() const {
    return number;
}

//! Out-of-class operators

template<std::size_t p>
number_field<p> operator+(const number_field<p>& self, const number_field<p>& other) {
    number_field<p> result = self;
    result += other;
    return result;
}

template<std::size_t p>
number_field<p> operator-(const number_field<p>& self, const number_field<p>& other) {
    number_field<p> result = self;
    result -= other;
    return result;
}

template<std::size_t p>
number_field<p> operator*(const number_field<p>& self, const number_field<p>& other) {
    number_field<p> result = self;
    result *= other;
    return result;
}

template<std::size_t p>
number_field<p> operator/(const number_field<p>& self, const number_field<p>& other) {
    number_field<p> result = self;
    result /= other;
    return result;
}

template<std::size_t p>
number_field<p> operator^(number_field<p> self, int power) {
    number_field<p> result = number_field<p>(1);

    while (power > 0) {
        if (power & 1) result *= self;
        power >>= 1;
        self *= self;
    }

    return result;
}

template<std::size_t p>
std::ostream& operator<<(std::ostream& out, const number_field<p>& num) {
    out << num.get_number();
    return out;
}

template<std::size_t p>
std::istream& operator>>(std::istream& in, number_field<p>& num) {
    int n;
    in >> n;
    num = number_field<p>(n);

    return in;
}