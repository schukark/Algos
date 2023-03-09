#include <iostream>
#include "Fractions.h"
#include "Fractions.cpp"

int main() {
    fraction<int> a, b;
    std::cin >> a >> b;
    std::cout << a << " " << b << " " << a.inverse() << " " << b.value() << std::endl;
}