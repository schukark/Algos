#ifndef NUMBER_FIELD_H
#define NUMBER_FIELD_H

#include <cstddef>
#include <cmath>
#include <fstream>

template<std::size_t p>
class number_field {
private:
    int number;
public:
    //! Rule of five

    number_field();
    number_field(int number);
    number_field(const number_field& other);
    number_field(number_field&& other) noexcept;

    number_field& operator=(const number_field& other);
    number_field& operator=(number_field&& other) noexcept;

    ~number_field() = default;

    //! Bool operators

    bool operator<(const number_field& other) const;
    bool operator>(const number_field& other) const;
    bool operator<=(const number_field& other) const;
    bool operator>=(const number_field& other) const;
    bool operator==(const number_field& other) const;
    bool operator!=(const number_field& other) const;

    //! Arithmetic operators

    number_field& operator+=(const number_field& other);
    number_field& operator*=(const number_field& other);
    number_field& operator-=(const number_field& other);
    number_field& operator/=(const number_field& other);

    //! Methods

    number_field inverse() const;
    int get_number() const;
};

#endif // NUMBER_FIELD_H