//
// Created by Viacheslav on 22.09.2018.
//

#include "BigInteger.h"


// Constructors

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
    bool negate = false;
    if (s[0] == '-') {
        s.erase(s.begin());
        negate = true;
    }
    a = BigInteger(s);
    a.isNegative = negate;
    return in;
}

ostream& operator<<(ostream& out, const BigInteger& a) {
    out << a.to_string();
    return out;
}


// Adding

BigInteger BigInteger::operator+(const BigInteger &other) const {
    BigInteger res(*this);
    res += other;
    return res;
}

BigInteger BigInteger::operator+(long long x) const {
    return *this + BigInteger(x);
}

BigInteger& BigInteger::operator+=(const BigInteger &other) {
    if (!isNegative && other.isNegative) { // + -
        return *this -= -other;
    }
    if (isNegative && !other.isNegative) { // - +
        cout << other << "_+_" << (*this) << " = " << other + (*this) << endl;
        cout << other << "_-_" << -(*this) << " = " << other - (-(*this)) << endl;
        return *this = other - -(*this);
    }
    if (isNegative && other.isNegative) { // - -
        
        *this = -((-(*this)) + (-other));
        return *this;
    }
    int carry = 0;
    vector<int> :: iterator it1 = num.begin();
    vector<int> :: const_iterator it2 = other.num.cbegin();

    for (; it1 != num.end() || it2 != other.num.cend() || carry; ++it1) {
        if (it1 == num.end()) {
            num.push_back(0);
            it1 = num.end() - 1;
        }
        *it1 += carry + (it2 != other.num.cend() ? *(it2++) : 0);
        carry = *it1 >= base;
        if (carry) {
            *it1 -= base;
        }
    }
    return *this;
}

BigInteger &BigInteger::operator+=(long long x) {
    (*this) += BigInteger(x);
    return *this;
}


// Subtraction

BigInteger BigInteger::operator-(const BigInteger& other) const {
    BigInteger res(*this);
    res -= other;
    return res;
    
}

BigInteger BigInteger::operator-(long long other) const {
    return *this - BigInteger(other);
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    if (!isNegative && other.isNegative) { // + -
        return *this = *this + (-other);
    }
    if (isNegative && !other.isNegative) { // - +
        *this = -((-(*this)) + (other));
        return *this;
    }
    if (isNegative && other.isNegative) { // - -
        return *this = (*this) + (-other);
    }
    if (other > *this) {
        return *this = -(other - (*this));
    }
    int carry = 0;
    
    int other_len = other.num.size();
    for (int i = 0; i < other_len || carry; ++i) {
        num[i] -= carry + (i < other_len ? other.num[i] : 0);
        carry = num[i] < 0;
        if (carry) {
            num[i] += base;
        }
    }
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
    
    return *this;
}

BigInteger& BigInteger::operator-=(long long other) {
    *this -= BigInteger(other);
    return *this;
}

BigInteger BigInteger::operator-() const{
    BigInteger res(*this);
    res.isNegative ^= true;
    return res;
}

bool BigInteger::operator>(const BigInteger& other) const {
    if (isNegative && other.isNegative) { // - -
        return (-other) > (-(*this));
    }
    if (isNegative) {
        return false;
    }
    if (other.isNegative) {
        return true;
    }
    if (num.size() > other.num.size()) {
        return true;
    }
    if (num.size() < other.num.size()) {
        return false;
    }
    for(int i = (int)num.size() - 1; i >= 0; --i) {
        if (num[i] > other.num[i]) {
            return true;
        }
        if (num[i] < other.num[i]) {
            return false;
        }
    }
    return false; // a == b
}

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

BigInteger BigInteger::operator*(const BigInteger& other) const {
    BigInteger res = BigInteger(0);
    int len_a = num.size();
    int len_b = other.num.size();
    res.isNegative = isNegative ^ other.isNegative;
    res.num.resize(len_a + len_b);
    for (int i = 0; i < len_a; ++i) {
        for (int j = 0, carry = 0; j < len_b || carry; ++j) {
            long long cur = res.num[i + j] + num[i] * 1LL * (j < len_b ? other.num[j] : 0) + carry;
            res.num[i + j] = cur % base;
            carry = cur / base;
        }
    }
    while (res.num.size() > 1 && res.num.back() == 0) {
        res.num.pop_back();
    }
    return res;
}

BigInteger BigInteger::operator*(long long other) const {
    BigInteger res(*this);
    return res * BigInteger(other);
}

BigInteger &BigInteger::operator*=(const BigInteger& other) {
    *this = *this * other;
    return *this;
}

BigInteger &BigInteger::operator*=(long long b) {
    *this = *this * BigInteger(b);
    return *this;
}

bool BigInteger::operator<(const BigInteger & other) const {
    return other > *this;
}

bool BigInteger::operator<=(const BigInteger & other) const {
    return !(*this > other);
}

bool BigInteger::operator>=(const BigInteger & other) const {
    return !(*this < other);
}

bool BigInteger::operator==(const BigInteger & other) const {
    return !(*this < other) && !(*this > other);
}

bool BigInteger::operator!=(const BigInteger & other) const {
    return !(*this == other);
}

BigInteger BigInteger::pow(long long step) const {
    if (step == 0) {
        return BigInteger(1);
    }
    if (step == 1) {
        return *this;
    }
    if (step & 1LL) {
        return pow(step - 1) * (*this);
    }
    BigInteger tmp = pow(step >> 1LL);
    return tmp * tmp;
}

BigInteger BigInteger::operator/(int other) const {
    BigInteger res(*this);
    int carry = 0;
    for (int i = (int)num.size() - 1; i >= 0; --i) {
        long long cur = res.num[i] + carry * 1LL * base;
        res.num[i] = cur / other;
        carry = cur % other;
    }
    while (res.num.size() > 1 && res.num.back() == 0) {
        res.num.pop_back();
    }
    return res;
}

BigInteger &BigInteger::operator/=(int other) {
    return *this = *this / other;
}

BigInteger BigInteger::operator/(const BigInteger & other) const {
    BigInteger a(*this);
    a.isNegative = false;
    BigInteger b(other);
    b.isNegative = false;
    
    BigInteger l(0);
    BigInteger r(a);
    bool sign = isNegative ^ other.isNegative;
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

BigInteger &BigInteger::operator/=(const BigInteger & other) {
    return *this = *this / other;
}

BigInteger BigInteger::operator%(int other) const {
    return *this - ((*this / other) * other);
}

BigInteger &BigInteger::operator%=(int other) {
    return *this = *this % other;
}

BigInteger BigInteger::operator%(const BigInteger & other) const {
    BigInteger res = *this / other;
    res = *this - ((res) * other);
    return res;
}

BigInteger &BigInteger::operator%=(const BigInteger & other) {
    return *this = *this % other;
}

BigInteger BigInteger::sqrt() const {
    if (isNegative) {
        throw invalid_argument("sqrt from negative number");
    }
    BigInteger l(0);
    BigInteger r(*this);
    while (r - l > 1) {
        BigInteger mid = (l + r) / 2;
        if (mid * mid <= *this) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    if (r * r <= *this) {
        l = r;
    }
    return l;
}






