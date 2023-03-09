#include "Complex.h"

template<class vt>
complex<vt>::complex(): real(0), imag(0) {}

template <class vt>
complex<vt>::complex(const vt &scalar): real(scalar), imag(0) {}

template <class vt>
complex<vt>::complex(const vt &_real, const vt &_imag): real(_real), imag(_imag) {}

template <class vt>
complex<vt>::complex(const complex <vt>&other): real(other.real), imag(other.imag) {}

template <class vt>
complex<vt>::complex(complex<vt> &&other) noexcept {
    if (this != &other) {
        real = other.real;
        imag = other.imag;

        other.real = 0;
        other.imag = 0;
    }
}

template <class vt>
complex<vt>& complex<vt>::operator=(const complex<vt> &other) {
    real = other.real;
    imag = other.imag;

    return *this;
}

template <class vt>
complex<vt>& complex<vt>::operator=(complex<vt> &&other) noexcept {
    if (this != &other) {
        real = other.real;
        imag = other.imag;

        other.real = 0;
        other.imag = 0;
    }

    return *this;
}

template <class vt>
double complex<vt>::argument() const {
    return std::atan2(imag, real);
}

template <class vt>
double complex<vt>::length() const {
    return std::hypot(real, imag);
}

template <class vt>
complex<vt> complex<vt>::conjugate() const {
    return complex(real, -imag);
}

template <class vt>
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

    *this = complex(real_, imag_);

    return *this;
}

template<class vt>
complex<vt>& complex<vt>::operator/=(const complex<vt>& other) {
    *this = *this * other.conjugate() / (other.real * other.real + other.imag * other.imag);

    return *this;
}

template <class vt>
bool complex<vt>::operator==(const complex &other) const {
    return (real == other.real) && (imag == other.imag);
}