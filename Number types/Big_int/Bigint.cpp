#include "Bigint.h"

//! Rule of five

bigint::bigint(): sign(1), digits(std::vector<int>(1, 0)) {}

bigint::bigint(long long value) { *this = value; }

bigint::bigint(const bigint &other): sign(other.sign), digits(other.digits) {}

bigint& bigint::operator=(long long value) {
    sign = 1;
    if (value < 0) {
        sign = -1;
        value *= -1;
    }

    digits.clear();

    while (value > 0) {
        digits.push_back(value % 10);
        value /= 10;
    }

    return *this;
}

bigint& bigint::operator=(const bigint &other) {
    sign = other.sign;
    digits = other.digits;

    return *this;
}

//! In-class methods

std::string bigint::to_string() const {
    std::string s;

    for (int i = digits.size() - 1; i >= 0; i--) {
        s += std::to_string(digits[i]);
    }

    if (sign == -1) s = '-' + s;

    return s;
}

bigint bigint::abs() const  {
    bigint result = *this;
    result.sign = 1;
    return result;
}

void bigint::trim_zeros() {
    while (!digits.empty() && !digits.back()) digits.pop_back();

    if (digits.empty()) {
        sign = 1;
        digits.resize(1, 0);
    }
}

std::vector<int> &bigint::_digits() {
    return digits;
}

const std::vector<int> &bigint::_digits() const {
    return digits;
}

int &bigint::_sign() {
    return sign;
}

const int &bigint::_sign() const {
    return sign;
}

bigint::operator bool() const {
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i]) return true;
    }

    return false;
}

bigint bigint::operator-() const  {
    bigint result = *this;
    result.sign *= -1;
    return result;
}

bigint bigint::operator+() const {
    bigint result = *this;
    return result;
}

//! In-class arithmetic operators

bigint &bigint::operator+=(const bigint &other) {
    *this = other + *this;

    return *this;
}

bigint &bigint::operator-=(const bigint &other) {
    *this = *this - other;

    return *this;
}

bigint &bigint::operator*=(const bigint &other)  {
    *this = other * (*this);
    return *this;
}

bigint &bigint::operator++()  {
    *this += 1;
    return *this;
}

const bigint bigint::operator++(int)  {
    bigint result = *this;
    *this += 1;
    return result;
}

bigint &bigint::operator--()  {
    *this -= 1;
    return *this;
}

const bigint bigint::operator--(int)  {
    bigint result = *this;
    *this -= 1;
    return result;
}

//! Out-of-class arithmetic operators

bigint operator+(const bigint& self, const bigint& other) {
    if (self._sign() != other._sign()) return self - (-other);
    bigint result = other;

    for (int i = 0, carry = 0; i < std::max(self._digits().size(), other._digits().size()) || carry; i++) {
        if (i == result._digits().size()) result._digits().push_back(0);

        result._digits()[i] += carry + (i < self._digits().size() ? self._digits()[i] : 0);
        carry = (result._digits()[i] >= 10);

        if (carry) result._digits()[i] -= 10;
    }

    return result;
}

bigint operator-(const bigint& self, const bigint& other) {
    if (self._sign() != other._sign()) return self + (-other);

    if (self.abs() < other.abs()) return -(other - self);

    bigint result = self;

    for (int i = 0, carry = 0; i < other._digits().size() || carry; i++) {
        result._digits()[i] -= carry + (i < other._digits().size() ? other._digits()[i] : 0);
        carry = result._digits()[i] < 0;

        if (carry) result._digits()[i] += 10;
    }

    result.trim_zeros();
    return result;
}

bigint operator*(const bigint& self, const bigint& other) {
    bigint result;
    result._digits().resize(0);

    result._sign() = self._sign() * other._sign();

    for (int i = 0; i < self._digits().size(); i++) {
        int carry = 0;

        for (int j = 0; j < other._digits().size(); j++) {
            int k = i + j;

            if (k == result._digits().size()) result._digits().push_back(0);

            long long prod = self._digits()[i] * other._digits()[j] + result._digits()[k] + carry;
            result._digits()[k] = prod % 10;
            carry = prod / 10;
        }

        if (result._digits().size() == i + other._digits().size()) {
            result._digits().push_back(0);
        }

        result._digits()[i + other._digits().size()] += carry;
    }

    result.trim_zeros();

    return result;
}

//! Out-of-class non-arithmetic operators

std::istream& operator>>(std::istream& stream, bigint& value) {
    std::string s;
    stream >> s;

    if (s[0] == '-') {
        value._sign() = -1;
        s = s.substr(1, s.size());
    }

    value._digits().resize(s.size());

    for (int i = s.size() - 1, j = 0; i >= 0; i--, j++) {
        value._digits()[j] = s[i] - '0';
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const bigint& value) {
    stream << value.to_string();

    return stream;
}

//! Boolean operators

bool operator<(const bigint &self, const bigint &other) {
    if (self._sign() != other._sign()) return self._sign() < other._sign();

    if (self._digits().size() != other._digits().size())
        return self._sign() * self._digits().size() < other._sign() * other._digits().size();

    for (int i = self._digits().size() - 1; i >= 0; i--) {
        if (self._digits()[i] != other._digits()[i]) 
            return self._sign() * self._digits()[i] < other._sign() * other._digits()[i];
    }

    return false;
}

bool operator>(const bigint& self, const bigint& other) {
    return other < self;
}

bool operator>=(const bigint& self, const bigint& other) {
    return !(self < other);
}

bool operator<=(const bigint& self, const bigint& other) {
    return !(self > other);
}

bool operator==(const bigint& self, const bigint& other) {
    return (self <= other) && (self >= other);
}

bool operator!=(const bigint& self, const bigint& other) {
    return !(self == other);
}
