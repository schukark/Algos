#include <iostream>
#include "Number_field.h"
#include "Number_field.cpp"

int main() {
    number_field<29> F, G;
    std::cin >> F >> G;
    std::cout << F << " " << G << " " << F / G;
}