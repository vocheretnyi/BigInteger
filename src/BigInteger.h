//
// Created by Viacheslav on 22.09.2018.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

namespace BigIntegerLibrary {

    class BigInteger {
    public:
        //Constructors
        BigInteger(long long);

        BigInteger(string);

        BigInteger(const BigInteger &);

        BigInteger &operator=(const BigInteger &);

        // Adding
        BigInteger operator+(const BigInteger &) const;

        BigInteger operator+(long long) const;

        BigInteger &operator+=(const BigInteger &);

        BigInteger &operator+=(long long);

        // Subtraction
        BigInteger operator-(const BigInteger &) const;

        BigInteger operator-(long long) const;

        BigInteger &operator-=(const BigInteger &);

        BigInteger &operator-=(long long);

        BigInteger operator-() const; // Unary minus

        // Multiplication
        BigInteger operator*(const BigInteger &) const;

        BigInteger operator*(long long) const;

        BigInteger &operator*=(const BigInteger &);

        BigInteger &operator*=(long long);

        // Dividing
        BigInteger operator/(int) const;

        BigInteger &operator/=(int);

        BigInteger operator/(const BigInteger &) const;

        BigInteger &operator/=(const BigInteger &);

        BigInteger operator%(int) const;

        BigInteger &operator%=(int);

        BigInteger operator%(const BigInteger &) const;

        BigInteger &operator%=(const BigInteger &);

        // Compare
        bool operator<(const BigInteger &) const;

        bool operator>(const BigInteger &) const;

        bool operator<=(const BigInteger &) const;

        bool operator>=(const BigInteger &) const;

        bool operator==(const BigInteger &) const;

        bool operator!=(const BigInteger &) const;

        // Input & Output
        friend istream &operator>>(istream &, BigInteger &);

        friend ostream &operator<<(ostream &, const BigInteger &);

        // Other methods
        string to_string() const;

        bool is_Negative() const;

        friend BigInteger abs(const BigInteger&);

    private:
        vector<int> num;
        bool isNegative;
        static const int base = 1e9;

        /*
         * a < b return -1
         * a > b return 1
         * a == b return 0
         */
        int compare(const BigInteger&) const;
    };

    BigInteger pow(const BigInteger&, long long);

    BigInteger sqrt(const BigInteger&);

}
#endif //BIGINTEGER_BIGINTEGER_H
