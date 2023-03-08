#include "Polynomial.h"

//! Rule of five

template<typename T>
polynomial<T>::polynomial(const T& scalar): coefficients(std::vector<T>(1, scalar)) {}

template<typename T>
polynomial<T>::polynomial(const std::vector<T>& coefficients): coefficients(coefficients) {}

template<typename T>
polynomial<T>::polynomial(const polynomial<T>& other) { 
    *this = other; 
}

template<typename T>
polynomial<T>::polynomial(polynomial<T>&& other) noexcept { 
    *this = other;
}

template<typename T>
polynomial<T>& polynomial<T>::operator=(const polynomial<T>& other) { 
    coefficients = other.coefficients; 
    return *this; 
}

template<typename T>
polynomial<T>& polynomial<T>::operator=(polynomial<T>&& other) noexcept {
    if (this != &other) {
        coefficients = other.coefficients;
        other.coefficients.clear();
    }

    return *this;
}

//! Comparison operators

template<typename T>
bool polynomial<T>::operator==(const polynomial<T>& other) const {
    if (coefficients.size() != other.coefficients.size()) return false;

    for (std::size_t i = 0; i < coefficients.size(); i++) {
        if (coefficients[i] != other[i]) return false;
    }

    return true;
}

template<typename T>
bool polynomial<T>::operator!=(const polynomial<T>& other) const {
    return !(*this == other);
}

//! Methods and non-arithmetic operators

template<typename T>
std::size_t polynomial<T>::degree() const {
    return coefficients.size() - 1;
}

template<typename T>
T& polynomial<T>::operator[] (std::size_t index) {
    return coefficients[index];
}

template<typename T>
const T& polynomial<T>::operator[] (std::size_t index) const {
    return coefficients[index];
}

template<typename T>
polynomial<T> polynomial<T>::differentiate() const {
    polynomial<T> result = *this;

    for (int i = 0; i < coefficients.size() - 1; i++) {
        result[i] = coefficients[i + 1] * (i + 1);
    }

    result.coefficients.pop_back();

    return result;
}

template<typename T>
polynomial<T> polynomial<T>::integrate(const T& constant) const {
    polynomial<T> result = *this;
    result.coefficients.push_back(T(0));

    for (int i = 1; i < coefficients.size() + 1; i++) {
        result[i] = coefficients[i - 1] / i;
    }

    result[0] = constant;

    return result;
}

template<typename T>
T polynomial<T>::operator() (const T& point) const {
    T ans = T(0);

    for (int i = coefficients.size() - 1; i >= 0; i--) {
        ans += coefficients[i];

        if (i >= 1) ans *= point;
    }

    return ans;
}

template<typename T>
std::vector<T>& polynomial<T>::coef() {
    return coefficients;
}

template<typename T>
const std::vector<T>& polynomial<T>::coef() const {
    return coefficients;
}

template <typename T>
void polynomial<T>::reduce() {
    for (int i = 0; i < coefficients.size(); i++) {
        coefficients[i] /= coefficients.back();
    }
}

//! Linear in-class opeartors

template<typename T>
polynomial<T>& polynomial<T>::operator+= (const polynomial<T>& other) {
    for (int i = 0; i < coefficients.size(); i++) {
        if (coefficients.size() <= i) coefficients.push_back(T(0));

        coefficients[i] += other[i];
    }

    int i = coefficients.size() - 1;
    while (i > 0 && i < coefficients.size() && coefficients[i] == T(0)) {
        coefficients.pop_back();
        i--;
    }

    if (coefficients.empty()) coefficients = std::vector<T>({T(0)});

    return *this;
}

template <typename T>
polynomial<T>& polynomial<T>::operator-= (const polynomial<T>& other) {
    *this = (*this) + (-other);
    return *this;
}

template <typename T>
polynomial<T> polynomial<T>::operator+() const {
    return *this;
}

template <typename T>
polynomial<T> polynomial<T>::operator-() const {
    polynomial<T> result(*this);

    for (int i = 0; i < coefficients.size(); i++) {
        result[i] *= -1;
    }

    return result;
}

template <typename T>
polynomial<T>& polynomial<T>::operator*=(const polynomial<T>& other) {
    *this = (*this) * other;
    return *this;
}

template <typename T>
polynomial<T> &polynomial<T>::operator/=(const polynomial<T> &other)
{
    *this = *this / other;
    return *this;
}

template <typename T>
polynomial<T> &polynomial<T>::operator%=(const polynomial<T> &other)
{
    *this = *this % other;
    return *this;
}

//! Out-of-class operators

template <typename T>
polynomial<T> operator* (const polynomial<T>& self, const polynomial<T>& other) {
    polynomial<T> result(T(0));
    
    for (int i = 0; i < self.coef().size(); i++) {
        for (int j = 0; j < other.coef().size(); j++) {
            int k = i + j;
            if (result.coef().size() >= k) result.coef().push_back(0);

            result[k] += self[i] * other[j];
        }
    }

    return result;
}

template <typename T>
polynomial<T> operator+ (const polynomial<T>& self, const polynomial<T>& other) {
    polynomial result(self);
    result += other;
    return result;
}

template<typename T>
polynomial<T> operator- (const polynomial<T>& self, const polynomial<T>& other) {
    polynomial result(self);
    result -= other;
    return result;
}

template<typename T>
polynomial<T> operator/ (const polynomial<T>& self, const polynomial<T> other) {
    polynomial<T> tmp = self;
    polynomial<T> result(std::vector<T>(tmp.degree() - other.degree() + 1, 0));

    while (tmp.degree() >= other.degree()) {
        int new_degree = tmp.degree() - other.degree();
        T new_coef = tmp.coef().back() / other.coef().back();

        std::vector<T> new_coefficients(new_degree, 0);
        new_coefficients.push_back(new_coef);   

        polynomial<T> divisor(new_coefficients);
        tmp -= (divisor * other);

        result[new_degree] = new_coef;
    }

    return result;
}

template<typename T>
polynomial<T> operator% (const polynomial<T>& self, const polynomial<T> other) {
    return self - (self / other) * other;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const polynomial<T>& poly) {
    bool spaces = false;
    for (int i = 0; i < poly.coef().size(); i++) {
        if (poly[i] == 0) continue;

        if (i == 0) {
            out << poly[i];
            spaces = true;
            continue;
        }
        if (spaces) {
            if (poly[i] > 0) out << " + ";
            else out << " - ";
        }

        spaces = true;

        T coef = (poly[i] > 0 ? poly[i] : -poly[i]);

        if (coef != 1)
            out << coef;
        out << "x";

        if (i == 1) continue;

        out << "^" << i;
    }

    return out;
}

template<typename T>
polynomial<T> gcd(polynomial<T> self, polynomial<T> other) {
    while (true) {
        //std::cout << self << " " << self.degree() << std::endl << other << " " << other.degree() << std::endl;
        if ((self % other) == polynomial<T>(0)) {
            other.reduce();
            return other;
        }
        else if ((self % other).degree() == 0) return polynomial<T>(T(1));

        if (self.degree() < other.degree()) {
            polynomial<T> tmp = self;
            self = other;
            other = tmp;
        }

        polynomial<T> remainder = self % other;
        self = other;
        other = remainder;
    }

    return polynomial<T>(T(1));
}