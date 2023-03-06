#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>
#include <fstream>

long long fast_power_mod(long long base, long long exponent, long long mod) {
    long long result = 1;
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

bool check_prime(long long number, std::size_t iterations = 10) {
    if (number % 2 == 0) return false;
    std::srand(time(NULL));

    for (std::size_t i = 0; i < iterations; i++) {
        int a = rand() % (number - 2) + 2;

        while (std::gcd(a, number) != 1) {
            a = rand() % (number - 2) + 2;
        }

        int d = 0, s = 0;
        long long copy = number - 1;

        while (copy % 2 == 0) {
            s++;
            copy /= 2;
        }
        d = copy;
        
        bool flag = false;
        long long result = fast_power_mod(a, d, number); // a^d = 1 mod n

        for (long long r = 0; r < s; r++) {
            long long result1 = fast_power_mod(a, (1 << r) * d, number);
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