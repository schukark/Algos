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

    //! Methods and non-arithmetic operators

    std::size_t degree() const noexcept {
        return coefficients.size() - 1;
    }

    T& operator[] (std::size_t index) {
        return coefficients[index];
    }

    const T& operator[] (std::size_t index) const {
        return coefficients[index];
    }

    //! Linear in-class opeartors

    polynomial& operator+= (const polynomial& other) {
        for (int i = 0; i < coefficients.size(); i++) {
            if (coefficients.size() <= i) coefficients.push_back(0);

            coefficients[i] += other[i];
        }

        return *this;
    }

    polynomial& operator-= (const polynomial& other) {
        for (int i = 0; i < coefficients.size(); i++) {
            if (coefficients.size() <= i) coefficients.push_back(0);

            coefficients[i] -= other[i];
        }

        int i = coefficients.size() - 1;
        while (i > 0 && equal(coefficients[i], 0.0) && coefficients.size() > 0) {
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
            if (equal(poly[i], 0.0)) continue;

            if (!i) out << poly[i];
            else {
                if (spaces_needed) {
                    if (poly[i] > 0) out << " + ";
                    else out << " - ";
                }

                T coef = std::fabs(poly[i]);
                out << coef << "x";
                spaces_needed = true;

                if (i != 1) out << "^" << i;
            }
        }

        return out;
    }
};


#endif // POLYNOMIAL_H