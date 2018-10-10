//
// Created by Viacheslav on 22.09.2018.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class BigInteger {
public:
    //Constructors
    BigInteger();
    BigInteger(long long);
    BigInteger(string);
    BigInteger(const BigInteger &);

    // Adding
    BigInteger operator+(const BigInteger&) const;
    BigInteger operator+(long long) const;
    BigInteger& operator+=(const BigInteger&);
    BigInteger& operator+=(long long);

    // Subtraction
    BigInteger operator-(const BigInteger&) const;
    BigInteger operator-(long long) const;
    BigInteger& operator-=(const BigInteger&);
    BigInteger& operator-=(long long);

    // Multiplication
    BigInteger operator*(const BigInteger&) const;
    BigInteger operator*(long long) const;
    BigInteger& operator*=(const BigInteger&);
    BigInteger& operator*=(long long);

    // Dividing
    BigInteger operator/(long long) const;
    BigInteger& operator/=(long long);
    BigInteger operator%(long long) const;
    BigInteger& operator%=(long long);


    BigInteger& operator=(/*const*/ BigInteger &);

    // Compare
    bool operator<(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;
    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;

    // Input & Output
    friend istream &operator>>(istream &, BigInteger &);
    friend ostream &operator<<(ostream &, BigInteger const &);

    // Other methods
    BigInteger pow(long long) const;
    BigInteger abs() const;
    operator string();

private:
    vector<int> num;
    bool isNegative;
    static const int base = 1e9;
};


#endif //BIGINTEGER_BIGINTEGER_H
