#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>
#include <fstream>

template<typename vt>
vt fast_power_mod(vt base, vt exponent, vt mod) {
    vt result = 1;
    base %= mod;

    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exponent >>= 1;
    }

    return result;
}

template<typename vt>
bool check_prime(vt number, std::size_t iterations = 10) {
    if (number % 2 == 0) return false; //If it is even it is not prime
    std::srand(time(NULL)); // New seed for random number generation

    for (std::size_t i = 0; i < iterations; i++) {
        int a = rand() % (number - 2) + 2;

        while (std::gcd(a, number) != 1) { // It shuold be coprime to number
            a = rand() % (number - 2) + 2;
        }

        int d = 0, s = 0;
        vt copy = number - 1;

        while (copy % 2 == 0) {
            s++;
            copy /= 2;
        }
        d = copy;
        
        bool flag = false;
        vt result = fast_power_mod<vt>(a, d, number); // a^d = 1 mod n

        for (vt r = 0; r < s; r++) { //a^(2^r * d)= -1 mod n
            vt result1 = fast_power_mod<vt>(a, (1 << r) * d, number);
            if (result1 == number - 1) {
                flag = true;
                break;
            }
        }

        if (result != 1 && !flag) return false;
    }

    return true;
}

std::ifstream fin("100_random_primes_below_10000.txt");

int main() {
    while (!fin.eof()) {
        long long test;
        fin >> test;
        std::cout << "Is " << test << " prime? " << (check_prime(test) ? "YES" : "NO") << std::endl;
    }
}