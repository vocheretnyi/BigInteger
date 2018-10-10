//
// Created by Viacheslav on 22.09.2018.
//

#include "BigInteger.h"

namespace BigIntegerLibrary {

// Constructors

    BigInteger::BigInteger() : BigInteger(0) {}

    BigInteger::BigInteger(long long number) : BigInteger(::to_string(number)) {}

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

    BigInteger::BigInteger(const BigInteger& other) {
        isNegative = other.isNegative;
        num = other.num;
    }

    BigInteger& BigInteger::operator=(const BigInteger& other) {
        if (this != &other) {
            isNegative = other.isNegative;
            num = other.num;
        }
        return *this;
    }


// Input & Output

    istream& operator>>(istream& in, BigInteger& a) {
        string s;
        in >> s;
        a = BigInteger(s);
        return in;
    }

    ostream& operator<<(ostream& out, const BigInteger& a) {
        out << a.to_string();
        return out;
    }


// Adding

    BigInteger BigInteger::operator+(const BigInteger& b) const {
        BigInteger a(*this);
        if (!a.isNegative && b.isNegative) { // + -
            return a - (-b);
        }
        if (a.isNegative && !b.isNegative) { // - +
            return b - (-a);
        }
        if (a.isNegative && b.isNegative) { // - -
            return -((-a) + (-b));
        }
        int carry = 0;
        vector<int>::iterator it1 = a.num.begin();
        vector<int>::const_iterator it2 = b.num.cbegin();

        for (; it1 != a.num.end() || it2 != b.num.cend() || carry; ++it1) {
            if (it1 == a.num.end()) {
                a.num.push_back(0);
                it1 = a.num.end() - 1;
            }
            *it1 += carry + (it2 != b.num.cend() ? *(it2++) : 0);
            carry = *it1 >= base;
            if (carry) {
                *it1 -= base;
            }
        }
        return a;
    }

    BigInteger BigInteger::operator+(long long x) const {
        return *this + BigInteger(x);
    }

    BigInteger& BigInteger::operator+=(const BigInteger& other) {
        return *this = *this + other;
    }

    BigInteger& BigInteger::operator+=(long long x) {
        return *this = *this + BigInteger(x);
    }


// Subtraction

    BigInteger BigInteger::operator-(const BigInteger& b) const {
        BigInteger a(*this);
        if (!a.isNegative && b.isNegative) { // + -
            return a + (-b);
        }
        if (a.isNegative && !b.isNegative) { // - +
            return -((-a) + b);
        }
        if (a.isNegative && b.isNegative) { // - -
            return a + (-b);
        }
        if (b > a) {
            return -(b - a);
        }

        int carry = 0;

        int b_len = b.num.size();
        for (int i = 0; i < b_len || carry; ++i) {
            a.num[i] -= carry + (i < b_len ? b.num[i] : 0);
            carry = a.num[i] < 0;
            if (carry) {
                a.num[i] += base;
            }
        }
        while (a.num.size() > 1 && a.num.back() == 0) {
            a.num.pop_back();
        }

        return a;
    }

    BigInteger BigInteger::operator-(long long other) const {
        return *this - BigInteger(other);
    }

    BigInteger& BigInteger::operator-=(const BigInteger& other) {
        return *this = *this - other;
    }

    BigInteger& BigInteger::operator-=(long long other) {
        return *this = *this - BigInteger(other);
    }

    BigInteger BigInteger::operator-() const {
        BigInteger res(*this);
        res.isNegative ^= true;
        return res;
    }
    
// Multiplication

    BigInteger BigInteger::operator*(const BigInteger& other) const {
        BigInteger res;
        int len_a = num.size();
        int len_b = other.num.size();
        res.isNegative = isNegative ^ other.isNegative;
        res.num.resize(len_a + len_b);
        for (int i = 0; i < len_a; ++i) {
            for (int j = 0, carry = 0; j < len_b || carry; ++j) {
                long long cur = res.num[i + j] + num[i] * 1LL * (j < len_b ? other.num[j] : 0) + carry;
                res.num[i + j] = int(cur % base);
                carry = int(cur / base);
            }
        }
        while (res.num.size() > 1 && res.num.back() == 0) {
            res.num.pop_back();
        }
        return res;
    }

    BigInteger BigInteger::operator*(long long other) const {
        return *this * BigInteger(other);
    }

    BigInteger& BigInteger::operator*=(const BigInteger& other) {
        return *this = *this * other;
    }

    BigInteger& BigInteger::operator*=(long long other) {
        return *this = *this * BigInteger(other);
    }

// Dividing

    BigInteger BigInteger::operator/(int other) const {
        BigInteger res(*this);
        int carry = 0;
        for (int i = (int) num.size() - 1; i >= 0; --i) {
            long long cur = res.num[i] + carry * 1LL * base;
            res.num[i] = int(cur / other);
            carry = int(cur % other);
        }
        while (res.num.size() > 1 && res.num.back() == 0) {
            res.num.pop_back();
        }
        return res;
    }

    BigInteger& BigInteger::operator/=(int other) {
        return *this = *this / other;
    }

    BigInteger BigInteger::operator/(const BigInteger& other) const {
        BigInteger a(*this);
        a.isNegative = false;
        BigInteger b(other);
        b.isNegative = false;

        BigInteger l(0);
        BigInteger r(a);
        bool sign = isNegative ^other.isNegative;
        while (r - l > 1) {
            BigInteger mid = (l + r) / 2;
            if (mid * b <= a) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        if (r * b <= a) {
            l = r;
        }
        l.isNegative = sign;
        return l;
    }

    BigInteger& BigInteger::operator/=(const BigInteger& other) {
        return *this = *this / other;
    }

    BigInteger BigInteger::operator%(int other) const {
        return *this - ((*this / other) * other);
    }

    BigInteger& BigInteger::operator%=(int other) {
        return *this = *this % other;
    }

    BigInteger BigInteger::operator%(const BigInteger& other) const {
        return *this - ((*this / other) * other);
    }

    BigInteger& BigInteger::operator%=(const BigInteger& other) {
        return *this = *this % other;
    }

// Compare

    bool BigInteger::operator>(const BigInteger& other) const {
        return compare(other) == 1;
    }

    bool BigInteger::operator<(const BigInteger& other) const {
        return compare(other) == -1;
    }

    bool BigInteger::operator<=(const BigInteger& other) const {
        int compared = compare(other);
        return compared == 0 || compared == -1;
    }

    bool BigInteger::operator>=(const BigInteger& other) const {
        int compared = compare(other);
        return compared == 0 || compared == 1;
    }

    bool BigInteger::operator==(const BigInteger& other) const {
        return compare(other) == 0;
    }

    bool BigInteger::operator!=(const BigInteger& other) const {
        return compare(other) != 0;
    }

// Other methods

    string BigInteger::to_string() const {
        ostringstream out;
        if (!num.size()) {
            out << 0;
            return out.str();
        }

        if (isNegative) {
            out << '-';
        }

        vector<int>::const_reverse_iterator it = num.rbegin();
        out << *it++;

        for (; it != num.rend(); ++it) {
            string s = ::to_string(*it);
            s.insert(s.begin(), 9 - s.length(), '0');
            out << s;
        }
        return out.str();
    }

    bool BigInteger::is_Negative() const {
        return isNegative;
    }

    BigInteger abs(const BigInteger& a) {
        BigInteger res(a);
        res.isNegative = false;
        return res;
    }

    int BigInteger::compare(const BigInteger& other) const {
        int sign = 1;
        if (isNegative && other.isNegative) {
            sign = -1;
        }
        if (isNegative) { // a < b
            return -1;
        }
        if (other.isNegative) { // a > b
            return 1;
        }
        if (num.size() > other.num.size()) { // a > b
            return sign;
        }
        if (num.size() < other.num.size()) { // a < b
            return -sign;
        }
        for (int i = (int) num.size() - 1; i >= 0; --i) {
            if (num[i] > other.num[i]) { // a > b
                return sign;
            }
            if (num[i] < other.num[i]) { // a < b
                return -sign;
            }
        }
        return 0; // a == b
    }

// Namespace Functions

    BigInteger pow(const BigInteger& a, long long n) {
        if (n == 0) {
            return BigInteger(1);
        }
        if (n == 1) {
            return a;
        }
        if (n & 1LL) {
            return pow(a, n - 1) * a;
        }
        BigInteger tmp = pow(a, n >> 1LL);
        return tmp * tmp;
    }

    BigInteger sqrt(const BigInteger& a) {
        if (a.is_Negative()) {
            throw invalid_argument("sqrt from negative number");
        }
        BigInteger l(0);
        BigInteger r(a);
        while (r - l > 1) {
            BigInteger mid = (l + r) / 2;
            if (mid * mid <= a) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        if (r * r <= a) {
            l = r;
        }
        return l;
    }

}