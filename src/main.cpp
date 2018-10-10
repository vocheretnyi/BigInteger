#include <bits/stdc++.h>
#include "BigInteger.h"

using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    BigInteger a(s1), b(s2);
    a += b;
    cout << a;
    return 0;
}