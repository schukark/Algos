#include "Fractions.h"

//! Rule of five

template <class T>
fraction<T>::fraction(): numerator(T(0)), denominator(T(1)) {}

template <class T>
fraction<T>::fraction(T scalar): numerator(scalar), denominator(T(1)) {}

template <class T>
fraction<T>::fraction(T numerator, T denominator): numerator(numerator), denominator(denominator) {
    T tmp = std::gcd(std::abs(numerator), std::abs(denominator));
    if (tmp != T(0)) {
        numerator /= tmp;
        denominator /= tmp;
    }

    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

template <class T>
fraction<T>::fraction(const fraction<T>& other): numerator(other.numerator), denominator(other.denominator) {}

template <class T>
fraction<T>::fraction(fraction<T>&& other) noexcept {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;

        other.numerator = 0;
        other.denominator = 1;
    }
}

template <class T>
fraction<T>& fraction<T>::operator=(const fraction<T>& other) {
    numerator = other.numerator;
    denominator = other.denominator;

    return *this;
}

template <class T>
fraction<T>& fraction<T>::operator=(fraction<T>&& other) noexcept {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;

        other.numerator = 0;
        other.denominator = 1;
    }

    return *this;
}

template<class T>
bool fraction<T>::operator<(const fraction<T>& other) const { // a/b compated to c/d <=> a/b - c/d compated to 0 <=> (ad - bc) / bd compated to 0
    T result_num = numerator * other.denominator - denominator * other.numerator;
    T result_den = denominator * other.denominator;

    return (result_num > 0) == (result_den > 0);
}

template<class T>
bool fraction<T>::operator>(const fraction<T>& other) const {
    return other < *this;
}

template<class T>
bool fraction<T>::operator<=(const fraction<T>& other) const {
    return !(*this > other);
}

template<class T>
bool fraction<T>::operator>=(const fraction<T>& other) const {
    return !(*this < other);
}

template<class T>
bool fraction<T>::operator==(const fraction<T>& other) const {
    return (*this >= other) && (*this <= other);
}

template<class T>
bool fraction<T>::operator!=(const fraction<T>& other) const {
    return !(*this == other);
}

template<class T>
fraction<T> fraction<T>::operator+=(const fraction<T>& other) {
    *this = *this + other;

    return *this;
}

template<class T>
fraction<T> fraction<T>::operator-=(const fraction<T>& other) {
    *this = *this - other;
    
    return *this;
}

template<class T>
fraction<T> fraction<T>::operator*=(const fraction<T>& other) {
    *this = *this * other;
    
    return *this;
}

template<class T>
fraction<T> fraction<T>::operator/=(const fraction<T>& other) {
    *this = *this / other;
    
    return *this;
}

template <class T>
fraction<T> fraction<T>::operator-() const {
    return fraction<T>(-numerator, denominator);
}

template <class T>
fraction<T> fraction<T>::operator+() const {
    return *this;
}

template<class T>
fraction<T> operator+(const fraction<T>& self, const fraction<T>& other) {
    T result_num = self.num() * other.denom() + self.denom() * other.num();
    T result_den = self.denom() * other.denom();

    return fraction<T>(result_num, result_den);
}

template<class T>
fraction<T> operator-(const fraction<T>& self, const fraction<T>& other) {
    T result_num = self.num() * other.denom() - self.denom() * other.num();
    T result_den = self.denom() * other.denom();
    
    return fraction<T>(result_num, result_den);
}

template<class T>
fraction<T> operator*(const fraction<T>& self, const fraction<T>& other) {
    T result_num = self.num() * other.num();
    T result_den = self.denom() * other.denom();

    return fraction<T>(result_num, result_den);
}

template<class T>
fraction<T> operator/(const fraction<T>& self, const fraction<T>& other) {
    T result_num = self.num() * other.denom();
    T result_den = self.denom() * other.num();
    
    return fraction<T>(result_num, result_den);
}

template<class T>
fraction<T> fraction<T>::inverse() const {
    return fraction<T>(denominator, numerator);
}

template<class T>
long double fraction<T>::value() const {
    return static_cast<long double>(numerator) / denominator;
}

template<class T>
T fraction<T>::num() const {
    return numerator;
}

template<class T>
T fraction<T>::denom() const {
    return denominator;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const fraction<T>& frac) {
    if (frac.denom() == T(1)) out << frac.num();
    else out << frac.num() << "/" << frac.denom();
    return out;
}

template<class T>
std::istream& operator>>(std::istream& in, fraction<T>& frac) {
    std::string s;
    in >> s;

    std::string num, den;
    int index = -1;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '/') {
            index = i;
            continue;
        }
    }

    if (index == -1) {
        frac = fraction<T>(T(std::stoll(s)), T(1));
    }
    else {
        frac = fraction<T>(T(std::stoll(s.substr(0, index))), T(std::stoll(s.substr(index + 1, s.size() - index - 1))));
    }

    return in;
}