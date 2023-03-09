#include "Complex.h"

template<class vt>
complex<vt>::complex(): real(0), imag(0) {}

template<class vt>
complex<vt>::complex(const vt &scalar): real(scalar), imag(0) {}

template<class vt>
complex<vt>::complex(const vt &_real, const vt &_imag): real(_real), imag(_imag) {}

template<class vt>
complex<vt>::complex(const complex<vt> &other): real(other.real), imag(other.imag) {}

template<class vt>
complex<vt>::complex(complex<vt> &&other) noexcept {
    if (this != &other) {
        real = other.real;
        imag = other.imag;

        other.real = 0;
        other.imag = 0;
    }
}

template<class vt>
complex<vt>& complex<vt>::operator=(const complex<vt> &other) {
    real = other.real;
    imag = other.imag;

    return *this;
}

template<class vt>
complex<vt>& complex<vt>::operator=(complex<vt> &&other) noexcept {
    if (this != &other) {
        real = other.real;
        imag = other.imag;

        other.real = 0;
        other.imag = 0;
    }

    return *this;
}

template<class vt>
double complex<vt>::argument() const {
    return std::atan2(imag, real);
}

template<class vt>
double complex<vt>::length() const {
    return std::hypot(real, imag);
}

template<class vt>
complex<vt> complex<vt>::conjugate() const {
    return complex<vt>(real, -imag);
}

template<class vt>
vt complex<vt>::_real() const {
    return real;
}

template<class vt>
vt complex<vt>::_imag() const {
    return imag;
}

template<class vt>
std::vector<complex<vt>> complex<vt>::roots(int n) const {
    double arg = argument();
    double len = length();

    double new_len = std::pow(len, 1.0 / n);
    double new_arg = arg / n;

    std::vector<complex<vt>> result;

    for (int i = 0; i < n; i++) {
        result.emplace_back(new_len * std::cos(new_arg), new_len * std::sin(new_arg));
        new_arg += std::acos(-1) * 2.0 / n;
    }

    return result;
}

template<class vt>
complex<vt>& complex<vt>::operator+=(const complex<vt>& other) {
    real += other.real;
    imag += other.imag;

    return *this;
}

template<class vt>
complex<vt>& complex<vt>::operator-=(const complex<vt>& other) {
    real -= other.real;
    imag -= other.imag;

    return *this;
}

template<class vt>
complex<vt>& complex<vt>::operator*=(const complex<vt>& other) {
    vt real_ = real * other.real - imag * other.imag;
    vt imag_ = real * other.imag + imag * other.real;

    *this = complex<vt>(real_, imag_);

    return *this;
}

template<class vt>
complex<vt>& complex<vt>::operator/=(const complex<vt>& other) {
    vt coef = (other.real * other.real + other.imag * other.imag);
    *this *= other.conjugate();

    *this = complex<vt>(real / coef, imag / coef);

    return *this;
}

template<class vt>
bool equal(const vt& a, const vt& b) {
    return a == b;
}

bool equal(double a, double b) {
    return std::fabs(a - b) < 1e-10;
}

template<class vt>
bool operator==(const complex<vt>& self, const complex<vt>& other) {
    return equal(self._real(), other._real()) && equal(self._imag(), other._imag());
}

template<class vt>
bool operator!=(const complex<vt>& self, const complex<vt>& other) {
    return !(self == other);
}

template<class vt>
std::ostream& operator<<(std::ostream& out, const complex<vt>& num) {
    if (!equal(num._real(), vt(0))) {
        if (!equal(num._imag(), vt(0))) out << "(";

        out << num._real();

        if (equal(num._imag(), vt(0))) {
            return out;
        }

        if (num._imag() > vt(0)) out << " + ";
        else out << " - ";

        vt coef = (num._imag() > vt(0) ? num._imag() : -num._imag());

        out << coef << "i)";

        return out;
    }

    if (!equal(num._imag(), vt(0))) {
        if (equal(num._imag(), vt(1))) out << "i";
        else if (equal(num._imag(), vt(-1))) out << "-i";
        else out << num._imag() << "i";
        return out;
    }

    out << "0";
    return out;
}

template<class vt>
complex<vt> operator+(const complex<vt>& self, const complex<vt>& other) {
    complex<vt> result(self);
    result += other;
    return result;
}

template<class vt>
complex<vt> operator-(const complex<vt>& self, const complex<vt>& other) {
    complex<vt> result(self);
    result -= other;
    return result;
}

template<class vt>
complex<vt> operator*(const complex<vt>& self, const complex<vt>& other) {
    complex<vt> result(self);
    result *= other;
    return result;
}

template<class vt>
complex<vt> operator/(const complex<vt>& self, const complex<vt>& other) {
    complex<vt> result(self);
    result /= other;
    return result;
}

template<class vt>
complex<vt> complex<vt>::operator-() const {
    return complex<vt>(-real, -imag);
}

template<class vt>
complex<vt> complex<vt>::operator+() const {
    return *this;
}

template<class vt>
bool operator>(const complex<vt>& self, int num) { //only for polynomial printing, this doesn't convey anything
    if (equal(self._real() - num, 0)) return self._imag() > 0;
    return self._real() - num > 0;
}