//
// Created by Viacheslav Ocheretnyi on 12.10.2018.
//

#include "Fraction.h"

Fraction::Fraction() : Fraction(BigInteger(1), BigInteger(1)){ }

Fraction::Fraction(const BigInteger& numerator) : Fraction(numerator, BigInteger(1)){ }

Fraction::Fraction(const BigInteger& numerator, const BigInteger& denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
    reduction(*this);
}

Fraction::Fraction(const Fraction& other) {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
    reduction(*this);
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
        reduction(*this);
    }
    return *this;
}

Fraction Fraction::operator+(const Fraction& b) const { // a/b + c/d = (ad+cb)/bd
    Fraction a = *this;
    Fraction c;
    c.denominator = a.denominator * b.denominator;
    c.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    reduction(c);
    return c;
}

Fraction Fraction::operator-(const Fraction& b) const {
    Fraction a = *this;
    Fraction c;
    c.denominator = a.denominator * b.denominator;
    c.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    reduction(c);
    return c;
}

Fraction Fraction::operator*(const Fraction& b) const {
    Fraction a = *this;
    Fraction c;
    c.denominator = a.denominator * b.denominator;
    c.numerator = a.numerator * b.numerator;
    reduction(c);
    return c;
}

Fraction Fraction::operator/(const Fraction& b) const {
    Fraction a = *this;
    Fraction c;
    c.denominator = a.denominator * b.numerator;
    c.numerator = a.numerator * b.denominator;
    reduction(c);
    return c;
}

bool Fraction::operator>(const Fraction& b) const {
    return (numerator * b.denominator > b.numerator * denominator);
}

void Fraction::reduction(Fraction& fract) {
    if (fract.denominator.is_Negative()) {
        fract.denominator.makePositive();
        fract.numerator = -fract.numerator;
    }
    BigInteger _gcd = gcd(fract.numerator, fract.denominator);
    fract.numerator /= _gcd;
    fract.denominator /= _gcd;
}

const BigInteger& Fraction::getNumerator() const {
    return numerator;
}

const BigInteger& Fraction::getDenominator() const {
    return denominator;
}

Fraction abs(const Fraction& fract) {
    return Fraction(abs(fract.getNumerator()), abs(fract.getDenominator()));
}
