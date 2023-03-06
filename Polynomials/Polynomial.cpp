#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>
#include <fstream>
#include <cmath>

template<typename T>
bool equal(const T& a, const T& b, const double eps=1e-6) {
    return std::fabs(a - b) < eps;
}

template<typename T>
class polynomial {
private:
    std::vector<T> coefficients;
public:
    //! Rule of 5

    polynomial& operator=(const polynomial& other) { 
        coefficients = other.coefficients; 
        return *this; 
    }

    polynomial(const T& scalar = 1): coefficients(std::vector<T>(1, scalar)) {}
    explicit polynomial(const std::vector<T>& coefficients): coefficients(coefficients) {}

    polynomial(const polynomial& other) { 
        *this = other; 
    }

    polynomial& operator=(polynomial&& other) noexcept {
        if (this != &other) {
            coefficients = other.coefficients;
            other.coefficients.clear();
        }

        return *this;
    }

    polynomial(polynomial&& other) noexcept { 
        *this = other;
    }

    ~polynomial() = default;

    //! Comparison operators

    bool operator==(const polynomial& other) const {
        for (std::size_t i = 0; i < coefficients.size(); i++) {
            if (!equal(coefficients[i], other[i])) return false;
        }

        return true;
    }

    bool operator!=(const polynomial& other) const {
        return !(*this == other);
    }

    //! Methods and non-arithmetic operators

    std::size_t degree() const {
        return coefficients.size() - 1;
    }

    T operator[] (std::size_t index) const {
        if (index >= coefficients.size()) return T(0);
        return coefficients[index];
    }

    polynomial differentiate() const {
        polynomial result = *this;

        for (int i = 0; i < coefficients.size() - 1; i++) {
            result[i] = coefficients[i + 1] * (i + 1);
        }

        result.coefficients.pop_back();

        return result;
    }

    polynomial integrate(const T& constant) const {
        polynomial result = *this;
        result.coefficients.push_back(T(0));

        for (int i = 1; i < coefficients.size() + 1; i++) {
            result[i] = coefficients[i - 1] / i;
        }

        result[0] = constant;

        return result;
    }

    T operator() (const T& point) const {
        T ans = T(0);

        for (int i = coefficients.size() - 1; i >= 0; i--) {
            ans += coefficients[i];

            if (i >= 1) ans *= point;
        }

        return ans;
    }

    //! Linear in-class opeartors

    polynomial& operator+= (const polynomial& other) {
        for (int i = 0; i < coefficients.size(); i++) {
            if (coefficients.size() <= i) coefficients.push_back(T(0));

            coefficients[i] += other[i];
        }

        return *this;
    }

    polynomial& operator-= (const polynomial& other) {
        for (int i = 0; i < coefficients.size(); i++) {
            if (coefficients.size() <= i) coefficients.push_back(T(0));

            coefficients[i] -= other[i];
        }

        int i = coefficients.size() - 1;
        while (i > 0 && equal(coefficients[i], T(0)) && coefficients.size() > 0) {
            coefficients.pop_back();
        }

        if (coefficients.empty()) coefficients.push_back(0);

        return *this;
    }

    polynomial operator+() const {
        return *this;
    }

    polynomial operator-() const {
        polynomial result(*this);

        for (int i = 0; i < coefficients.size(); i++) {
            result[i] *= -1;
        }

        return *this;
    }

    polynomial& operator*=(const polynomial& other) {
        *this = (*this) * other;
        return *this;
    }

    //! Out-of-class operators

    friend polynomial operator* (const polynomial& self, const polynomial& other) {
        polynomial result(0);
        
        for (int i = 0; i < self.coefficients.size(); i++) {
            for (int j = 0; j < other.coefficients.size(); j++) {
                int k = i + j;
                if (result.coefficients.size() >= k) result.coefficients.push_back(0);

                result[k] += self[i] * other[j];
            }
        }

        return result;
    }

    friend polynomial operator+ (const polynomial& self, const polynomial& other) {
        polynomial result(self);
        result += other;
        return result;
    }

    friend polynomial operator- (const polynomial& self, const polynomial& other) {
        polynomial result(self);
        result -= other;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, const polynomial& poly) {
        if (poly.coefficients.size() == 1) {
            out << poly[0];
            return out;
        }

        bool spaces_needed = false;
        for (std::size_t i = 0; i < poly.coefficients.size(); i++) {
            if (equal(poly[i], T(0))) continue;

            if (!i) {
                out << poly[i];
                spaces_needed = true;
            }
            else {
                if (spaces_needed) {
                    if (poly[i] > T(0)) out << " + ";
                    else out << " - ";
                }

                T coef = std::fabs(poly[i]);

                if (coef != 1)
                    out << coef;
                out << "x";

                spaces_needed = true;

                if (i != 1) out << "^" << i;
            }
        }

        return out;
    }
};


#endif // POLYNOMIAL_H