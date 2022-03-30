#pragma once

#include <iostream>
#include <stdexcept>

class Rational
{
public:
    constexpr Rational();
    explicit constexpr Rational(const int &n);
    constexpr Rational(const int &n, const int &d);

    constexpr Rational &operator=(const int &n);
    constexpr Rational &assign(const int &n, const int &d);

    constexpr const int &getNumerator() const;
    constexpr const int &getDenominator() const;

    constexpr Rational operator+() const;
    constexpr Rational operator-() const;

    constexpr Rational &operator+=(const Rational &r);
    constexpr Rational &operator-=(const Rational &r);
    constexpr Rational &operator*=(const Rational &r);
    constexpr Rational &operator/=(const Rational &r);

    constexpr Rational &operator+=(const int &n);
    constexpr Rational &operator-=(const int &n);
    constexpr Rational &operator*=(const int &n);
    constexpr Rational &operator/=(const int &n);

    constexpr const Rational &operator++();
    constexpr const Rational operator++(int);
    constexpr const Rational &operator--();
    constexpr const Rational operator--(int);

    constexpr bool operator<(const Rational &r) const;
    constexpr bool operator>(const Rational &r) const;
    constexpr bool operator>=(const Rational &r) const;
    constexpr bool operator<=(const Rational &r) const;

    constexpr bool operator<(const int &n) const;
    constexpr bool operator>(const int &n) const;
    constexpr bool operator>=(const int &n) const;
    constexpr bool operator<=(const int &n) const;

    constexpr bool operator!() const;
    constexpr bool operator!=(const Rational &r) const;
    constexpr bool operator==(const Rational &r) const;

    constexpr bool operator!=(const int &n) const;
    constexpr bool operator==(const int &n) const;

    static constexpr int gcd(const int &a, const int &b);
    static constexpr int lcm(const int &a, const int &b);

private:
    static constexpr bool isNormalized(const int &n, const int &d);
    constexpr void normalize();

private:
    int mNumerator;
    int mDenominator;
};

#include <internal/src/rational.inl>