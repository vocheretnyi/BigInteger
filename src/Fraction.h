//
// Created by Viacheslav Ocheretnyi on 12.10.2018.
//

#ifndef BIGINTEGER_FRACTION_H
#define BIGINTEGER_FRACTION_H

#include "BigInteger.h"

using namespace BigIntegerLibrary;

class Fraction {
public:
    Fraction();

    Fraction(const BigInteger&);

    Fraction(const BigInteger&, const BigInteger&);

    Fraction(const Fraction&);

    Fraction& operator=(const Fraction&);

    Fraction operator+(const Fraction&) const;

    Fraction operator-(const Fraction&) const;

    Fraction operator*(const Fraction&) const;

    Fraction operator/(const Fraction&) const;

    bool operator>(const Fraction&) const;

    const BigInteger& getNumerator() const;

    const BigInteger& getDenominator() const;


private:
    BigInteger numerator;
    BigInteger denominator;
    static void reduction(Fraction&);
};

Fraction abs(const Fraction&);


#endif //BIGINTEGER_FRACTION_H
