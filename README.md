# Maths

There are templated classes for widely used types of numbers:
1. Big integer(+, -, /, $\times$, <, >, ==)
2. Fractions(+, -, /, $\times$, $^{-1}$, <, >, ==)
3. Complex numbers(+, -, /, $\times$, $\overline{z}$, $\sqrt[n]{z}$, ==)
4. Number field modulo some $p^a$, where $p$ is a prime(+, -, /, $\times$, ==, $^{-1}$)

In brackets are operations allowed upon those numbers

All number classes are templated so you can use them in each other, for example $\mathbb{Q}\[i\]$, which are rational complex numbers

---------------------------------------------------------------------


Also there is a class Polynomial, which incorporates all necessary operations upon them, including GCD

---------------------------------------------------------------------

The Miller-Rabin primality test is also implemented, checking a number for being a probable prime in $O(klog^3n)$
