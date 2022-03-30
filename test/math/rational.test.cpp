#include <gtest/gtest.h>

#include <math/rational.h>

TEST(Rational, DefaultConstructor)
{
    Rational r;
    EXPECT_EQ(r.getNumerator(), 0);
    EXPECT_EQ(r.getDenominator(), 1);
}

TEST(Rational, NumeratorConstructor)
{
    Rational r(1);
    EXPECT_EQ(r.getNumerator(), 1);
    EXPECT_EQ(r.getDenominator(), 1);
}

TEST(Rational, NumeratorDenominatorConstructor)
{
    Rational r(1, 2);
    EXPECT_EQ(r.getNumerator(), 1);
    EXPECT_EQ(r.getDenominator(), 2);
}

TEST(Rational, CopyConstructor)
{
    Rational r1(1, 2);
    Rational r2(r1);
    EXPECT_EQ(r2.getNumerator(), 1);
    EXPECT_EQ(r2.getDenominator(), 2);
}

TEST(Rational, AssignmentOperator)
{
    Rational r1(1, 2);
    Rational r2;
    r2 = r1;
    EXPECT_EQ(r2.getNumerator(), 1);
    EXPECT_EQ(r2.getDenominator(), 2);
}

TEST(Rational, AssignNumeratorDenominator)
{
    Rational r1;
    r1.assign(1, 2);
    EXPECT_EQ(r1.getNumerator(), 1);
    EXPECT_EQ(r1.getDenominator(), 2);
}

TEST(Rational, GetNumerator)
{
    Rational r(1, 2);
    EXPECT_EQ(r.getNumerator(), 1);
}

TEST(Rational, GetDenominator)
{
    Rational r(1, 2);
    EXPECT_EQ(r.getDenominator(), 2);
}

TEST(Rational, UnaryPlusOperator)
{
    Rational r1(1, 2);
    Rational r2 = +r1;
    EXPECT_EQ(r2.getNumerator(), 1);
    EXPECT_EQ(r2.getDenominator(), 2);
}

TEST(Rational, UnaryMinusOperator)
{
    Rational r1(1, 2);
    Rational r2 = -r1;
    EXPECT_EQ(r2.getNumerator(), -1);
    EXPECT_EQ(r2.getDenominator(), 2);
}

TEST(Rational, RationalAdditionOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3 = r1 + r2;
    EXPECT_EQ(r3.getNumerator(), 5);
    EXPECT_EQ(r3.getDenominator(), 6);
    
}

TEST(Rational, RationalSubtractionOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3 = r1 - r2;
    EXPECT_EQ(r3.getNumerator(), 1);
    EXPECT_EQ(r3.getDenominator(), 6);
}

TEST(Rational, RationalMultiplicationOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3 = r1 * r2;
    EXPECT_EQ(r3.getNumerator(), 1);
    EXPECT_EQ(r3.getDenominator(), 6);
}

TEST(Rational, RationalDivisionOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3 = r1 / r2;
    EXPECT_EQ(r3.getNumerator(), 3);
    EXPECT_EQ(r3.getDenominator(), 2);
}

TEST(Rational, IntAddtionOperator)
{
    Rational r1(1, 2);
    Rational r2 = r1 + 1;
    EXPECT_EQ(r2.getNumerator(), 3);
    EXPECT_EQ(r2.getDenominator(), 2);
}

TEST(Rational, IntSubtractionOperator)
{
    Rational r1(1, 2);
    Rational r2 = r1 - 1;
    EXPECT_EQ(r2.getNumerator(), -1);
    EXPECT_EQ(r2.getDenominator(), 2);
}

TEST(Rational, IntMultiplicationOperator)
{
    Rational r1(1, 2);
    Rational r2 = r1 * 2;
    EXPECT_EQ(r2.getNumerator(), 1);
    EXPECT_EQ(r2.getDenominator(), 1);
}

TEST(Rational, IntDivisionOperator)
{
    Rational r1(1, 2);
    Rational r2 = r1 / 2;
    EXPECT_EQ(r2.getNumerator(), 1);
    EXPECT_EQ(r2.getDenominator(), 4);
}

TEST(Rational, RationalAdditionAssignmentOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    r1 += r2;
    EXPECT_EQ(r1.getNumerator(), 5);
    EXPECT_EQ(r1.getDenominator(), 6);
}

TEST(Rational, RationalSubtractionAssignmentOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    r1 -= r2;
    EXPECT_EQ(r1.getNumerator(), 1);
    EXPECT_EQ(r1.getDenominator(), 6);
}

TEST(Rational, RationalMultiplicationAssignmentOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    r1 *= r2;
    EXPECT_EQ(r1.getNumerator(), 1);
    EXPECT_EQ(r1.getDenominator(), 6);
}

TEST(Rational, RationalDivisionAssignmentOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    r1 /= r2;
    EXPECT_EQ(r1.getNumerator(), 3);
    EXPECT_EQ(r1.getDenominator(), 2);
}

TEST(Rational, IntAdditionAssignmentOperator)
{
    Rational r1(1, 2);
    r1 += 1;
    EXPECT_EQ(r1.getNumerator(), 3);
    EXPECT_EQ(r1.getDenominator(), 2);
}

TEST(Rational, IntSubtractionAssignmentOperator)
{
    Rational r1(1, 2);
    r1 -= 1;
    EXPECT_EQ(r1.getNumerator(), -1);
    EXPECT_EQ(r1.getDenominator(), 2);
}

TEST(Rational, IntMultiplicationAssignmentOperator)
{
    Rational r1(1, 2);
    r1 *= 2;
    EXPECT_EQ(r1.getNumerator(), 1);
    EXPECT_EQ(r1.getDenominator(), 1);
}

TEST(Rational, IntDivisionAssignmentOperator)
{
    Rational r1(1, 2);
    r1 /= 2;
    EXPECT_EQ(r1.getNumerator(), 1);
    EXPECT_EQ(r1.getDenominator(), 4);
}

TEST(Rational, PrefixAddition)
{
    Rational r1(1, 2);
    Rational r2 = ++r1;
    EXPECT_EQ(r2.getNumerator(), 3);
    EXPECT_EQ(r2.getDenominator(), 2);
}

TEST(Rational, PostfixAddition)
{
    Rational r1(1, 2);
    Rational r2 = r1++;
    EXPECT_EQ(r2.getNumerator(), 1);
    EXPECT_EQ(r2.getDenominator(), 2);
    EXPECT_EQ(r1.getNumerator(), 3);
    EXPECT_EQ(r1.getDenominator(), 2);
}

TEST(Rational, PrefixSubtraction)
{
    Rational r1(1, 2);
    Rational r2 = --r1;
    EXPECT_EQ(r2.getNumerator(), -1);
    EXPECT_EQ(r2.getDenominator(), 2);
}

TEST(Rational, PostfixSubtraction)
{
    Rational r1(1, 2);
    Rational r2 = r1--;
    EXPECT_EQ(r2.getNumerator(), 1);
    EXPECT_EQ(r2.getDenominator(), 2);
    EXPECT_EQ(r1.getNumerator(), -1);
    EXPECT_EQ(r1.getDenominator(), 2);
}

TEST(Rational, RationalLessThan)
{
    Rational r1(1, 3);
    Rational r2(1, 2);
    EXPECT_TRUE(r1 < r2);
}

TEST(Rational, RationalGreaterThan)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    EXPECT_TRUE(r1 > r2);
}

TEST(Rational, RationalLessThanOrEqualTo)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    EXPECT_TRUE(r2 <= r1);
}

TEST(Rational, RationalGreaterThanOrEqualTo)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    EXPECT_TRUE(r1 >= r2);
}

// comparison operators between Rational and int

TEST(Rational, IntLessThan)
{
    Rational r1(1, 2);
    EXPECT_TRUE(r1 < 2);
}

TEST(Rational, IntGreaterThan)
{
    Rational r1(1, 2);
    EXPECT_TRUE(r1 > 0);
}

TEST(Rational, IntLessThanOrEqualTo)
{
    Rational r1(1, 2);
    EXPECT_TRUE(r1 <= 2);


}

TEST(Rational, IntGreaterThanOrEqualTo)
{
    Rational r1(1, 2);
    EXPECT_TRUE(r1 >= 0);
    
}

TEST(Rational, RationalNotOperator)
{
    Rational r1(1, 2);
    EXPECT_FALSE(!r1);
}

TEST(Rational, RationalNotEqualToOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    EXPECT_TRUE(r1 != r2);
}

TEST(Rational, RationalEqualToOperator)
{
    Rational r1(1, 2);
    Rational r2(1, 2);
    EXPECT_TRUE(r1 == r2);
}

TEST(Rational, IntNotEqualToOperator)
{
    Rational r1(1, 2);
    EXPECT_TRUE(r1 != 1);
}

TEST(Rational, IntEqualToOperator)
{
    Rational r1(2, 2);
    EXPECT_TRUE(r1 == 1);
}

TEST(Rational, GCD)
{
    EXPECT_EQ(Rational::gcd(1, 2), 1);
    EXPECT_EQ(Rational::gcd(2, 1), 1);
    EXPECT_EQ(Rational::gcd(2, 4), 2);
    EXPECT_EQ(Rational::gcd(4, 2), 2);
    EXPECT_EQ(Rational::gcd(4, 6), 2);
    EXPECT_EQ(Rational::gcd(6, 4), 2);
    
}

TEST(Rational, LCM)
{
    
    EXPECT_EQ(Rational::lcm(1, 2), 2);
    EXPECT_EQ(Rational::lcm(2, 1), 2);
    EXPECT_EQ(Rational::lcm(2, 4), 4);
    EXPECT_EQ(Rational::lcm(4, 2), 4);
    EXPECT_EQ(Rational::lcm(4, 6), 12);
    
}


