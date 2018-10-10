//
// Created by Viacheslav on 22.09.2018.
//

#include "BigInteger.h"

BigInteger::BigInteger() : BigInteger(0) {}

BigInteger::BigInteger(long long number) : BigInteger(to_string(number)) {}

BigInteger::BigInteger(string number) {
    if (!number.empty() && number[0] == '-') {
        isNegative = true;
        number.erase(number.begin());
    } else {
        isNegative = false;
    }
    for (int i = number.length(); i > 0; i -= 9) {
        if (i >= 9) {
            num.push_back(stoi(number.substr(i - 9, 9)));
        } else {
            num.push_back(stoi(number.substr(0, i)));
        }
    }
    while (num.size() > 1 && !num.back()) { // remove leading zeros
        num.pop_back();
    }
}

BigInteger::BigInteger(const BigInteger &other) {
    isNegative = other.isNegative;
    num = other.num;
}

BigInteger& BigInteger::operator=(BigInteger &other) {
    num = other.num;
    isNegative = other.isNegative;
    return *this;
}

ostream& operator<<(ostream &out, const BigInteger &a) {

    if (!a.num.size()) {
        return out << 0;
    }

    if (a.isNegative) {
        out << '-';
    }

    vector<int>::const_reverse_iterator it = a.num.rbegin();
    out << *it++;

    for (; it != a.num.rend(); ++it) {
        string s = to_string(*it);
        s.insert(s.begin(), 9 - s.length(), '0');
        out << s;
    }
    return out;
}

BigInteger BigInteger::operator+(const BigInteger &other) const {
    BigInteger res = BigInteger();
    if (!isNegative != other.isNegative) {
        if (abs() > other.abs()) {
            res = abs() - other.abs();
            res.isNegative = isNegative;
        } else {
            res = other.abs() - abs();
            res.isNegative = other.isNegative;
        }
    } else {
        res = *this;
        int carry = 0;
        vector<int>::iterator it1 = res.num.begin();
        vector<int>::const_iterator it2 = other.num.cbegin();

        for (; it1 != res.num.end() || it2 != other.num.cend() || carry; ++it1) {
            if (it1 == res.num.end()) {
                res.num.push_back(0);
                it1 = res.num.end() - 1;
            }
            *it1 += carry + (it2 != other.num.cend() ? *(it2++) : 0);
            carry = *it1 >= base;
            if (carry) {
                *it1 -= base;
            }
        }
    }
    return res;
}

BigInteger BigInteger::operator+(long long x) const {
    return *this + BigInteger(x);
}

BigInteger &BigInteger::operator+=(const BigInteger &other) {
    *this = *this + other;
    return *this;
}

BigInteger &BigInteger::operator+=(long long x) {
    *this = *this + BigInteger(x);
    return *this;
}


