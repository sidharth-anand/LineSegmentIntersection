constexpr Rational::Rational()
    : mNumerator(0), mDenominator(1)
{
}

constexpr Rational::Rational(const int &n)
    : mNumerator(n), mDenominator(1)
{
}

constexpr Rational::Rational(const int &n, const int &d)
    : mNumerator(n), mDenominator(d)
{
    normalize();
}

constexpr Rational &Rational::operator=(const int &n)
{
    return assign(n, 1);
}

constexpr Rational &Rational::assign(const int &n, const int &d)
{
    *this = Rational(n, d);
    return *this;
}

constexpr const int &Rational::getNumerator() const
{
    return mNumerator;
}

constexpr const int &Rational::getDenominator() const
{
    return mDenominator;
}

constexpr Rational Rational::operator+() const
{
    return *this;
}

constexpr Rational Rational::operator-() const
{
    return Rational(-mNumerator, mDenominator);
}

constexpr Rational operator+(const Rational &q, const Rational &r)
{
    return Rational(q.getNumerator() * r.getDenominator() + r.getNumerator() * q.getDenominator(), q.getDenominator() * r.getDenominator());
}

constexpr Rational operator-(const Rational &q, const Rational &r)
{
    return Rational(q.getNumerator() * r.getDenominator() - r.getNumerator() * q.getDenominator(), q.getDenominator() * r.getDenominator());
}

constexpr Rational operator*(const Rational &q, const Rational &r)
{
    return Rational(q.getNumerator() * r.getNumerator(), q.getDenominator() * r.getDenominator());
}

constexpr Rational operator/(const Rational &q, const Rational &r)
{
    return Rational(q.getNumerator() * r.getDenominator(), q.getDenominator() * r.getNumerator());
}

constexpr Rational operator+(const int &n, Rational &r)
{
    return r += (Rational(n));
}

constexpr Rational operator-(const int &n, Rational &r)
{
    return r -= (Rational(n));
}

constexpr Rational operator*(const int &n, Rational &r)
{
    return r *= (Rational(n));
}

constexpr Rational operator/(const int &n, Rational &r)
{
    return r /= (Rational(n));
}

constexpr Rational operator+(Rational &r, const int &n)
{
    return r += (Rational(n));
}

constexpr Rational operator-(Rational &r, const int &n)
{
    return r -= (Rational(n));
}

constexpr Rational operator*(Rational &r, const int &n)
{
    return r *= (Rational(n));
}

constexpr Rational operator/(Rational &r, const int &n)
{
    return r /= (Rational(n));
}

constexpr Rational &Rational::operator+=(const Rational &r)
{
    int gcd = Rational::gcd(mDenominator, r.getDenominator());

    mDenominator /= gcd;
    mNumerator = mNumerator * (r.getDenominator() / gcd) + r.getNumerator() * mDenominator;

    gcd = Rational::gcd(mNumerator, gcd);

    mNumerator /= gcd;
    mDenominator *= r.getDenominator() / gcd;

    return *this;
}

constexpr Rational &Rational::operator-=(const Rational &r)
{
    int gcd = Rational::gcd(mDenominator, r.getDenominator());

    mDenominator /= gcd;
    mNumerator = mNumerator * (r.getDenominator() / gcd) - r.getNumerator() * mDenominator;

    gcd = Rational::gcd(mNumerator, gcd);

    mNumerator /= gcd;
    mDenominator *= r.getDenominator() / gcd;

    return *this;
}

constexpr Rational &Rational::operator*=(const Rational &r)
{
    const int gcd1 = Rational::gcd(mNumerator, r.getDenominator());
    const int gcd2 = Rational::gcd(mDenominator, r.getNumerator());

    mNumerator = (mNumerator / gcd1) * (r.getNumerator() / gcd2);
    mDenominator = (mDenominator / gcd2) * (r.getDenominator() / gcd1);

    return *this;
}

constexpr Rational &Rational::operator/=(const Rational &r)
{
    if (r.getNumerator() == 0)
        throw std::domain_error("Division by zero");
    if (mNumerator == 0)
        return *this;

    const int gcd1 = Rational::gcd(mNumerator, r.getNumerator());
    const int gcd2 = Rational::gcd(mDenominator, r.getDenominator());

    mNumerator = (mNumerator / gcd1) * (r.getDenominator() / gcd2);
    mDenominator = (mDenominator / gcd2) * (r.getNumerator() / gcd1);

    if (mDenominator < 0)
    {
        mNumerator = -mNumerator;
        mDenominator = -mDenominator;
    }

    return *this;
}

constexpr Rational &Rational::operator+=(const int &n)
{
    mNumerator += n * mDenominator;
    return *this;
}

constexpr Rational &Rational::operator-=(const int &n)
{
    mNumerator -= n * mDenominator;
    return *this;
}

constexpr Rational &Rational::operator*=(const int &n)
{
    const int gcd = Rational::gcd(n, mDenominator);

    mNumerator *= n / gcd;
    mDenominator /= gcd;

    return *this;
}

constexpr Rational &Rational::operator/=(const int &n)
{
    if (n == 0)
        throw std::domain_error("Division by zero");

    if (mNumerator == 0)
        return *this;

    const int gcd = Rational::gcd(mNumerator, n);

    mNumerator /= gcd;
    mDenominator *= n / gcd;

    normalize();

    return *this;
}

constexpr const Rational &Rational::operator++()
{
    mNumerator += mDenominator;
    return *this;
}

constexpr const Rational Rational::operator++(int)
{
    Rational r(*this);
    ++(*this);
    return r;
}

constexpr const Rational &Rational::operator--()
{
    mNumerator -= mDenominator;
    return *this;
}

constexpr const Rational Rational::operator--(int)
{
    Rational r(*this);
    --(*this);
    return r;
}

constexpr bool Rational::operator<(const Rational &r) const
{
    return mNumerator * r.getDenominator() < r.getNumerator() * mDenominator;
}

constexpr bool Rational::operator>(const Rational &r) const
{
    return mNumerator * r.getDenominator() > r.getNumerator() * mDenominator;
}

constexpr bool Rational::operator>=(const Rational &r) const
{
    return mNumerator * r.getDenominator() >= r.getNumerator() * mDenominator;
}

constexpr bool Rational::operator<=(const Rational &r) const
{
    return mNumerator * r.getDenominator() <= r.getNumerator() * mDenominator;
}

constexpr bool Rational::operator!() const
{
    return mNumerator == 0;
}

constexpr bool Rational::operator!=(const Rational &r) const
{
    return mNumerator != r.getNumerator() || mDenominator != r.getDenominator();
}

constexpr bool Rational::operator==(const Rational &r) const
{
    return mNumerator == r.getNumerator() && mDenominator == r.getDenominator();
}

constexpr bool Rational::operator!=(const int &n) const
{
    return mNumerator != n * mDenominator;
}

constexpr bool Rational::operator==(const int &n) const
{
    return mNumerator == n * mDenominator;
}

// rational int comparison

constexpr bool Rational::operator<(const int &n) const
{
    return mNumerator < n * mDenominator;
}

constexpr bool Rational::operator>(const int &n) const
{
    return mNumerator > n * mDenominator;
}

constexpr bool Rational::operator>=(const int &n) const
{
    return mNumerator >= n * mDenominator;
}

constexpr bool Rational::operator<=(const int &n) const
{
    return mNumerator <= n * mDenominator;
}

constexpr int Rational::gcd(const int &a, const int &b)
{
    return b == 0 ? a : gcd(b, a % b);
}

constexpr int Rational::lcm(const int &a, const int &b)
{
    return a * b / gcd(a, b);
}

constexpr bool Rational::isNormalized(const int &n, const int &d)
{
    return (d > 0) && (n != 0 || d == 1) && (abs(gcd(n, d)) == 1);
}

constexpr void Rational::normalize()
{
    if (mDenominator < 0)
    {
        mNumerator = -mNumerator;
        mDenominator = -mDenominator;
    }

    const int gcd = Rational::gcd(mNumerator, mDenominator);

    mNumerator /= gcd;
    mDenominator /= gcd;

    if (mDenominator < 0)
    {
        mNumerator = -mNumerator;
        mDenominator = -mDenominator;
    }
}

inline std::ostream& operator <<(std::ostream& stream, const Rational & rational)
{
    stream << rational.getNumerator() << "/" << rational.getDenominator();
    return stream;
}