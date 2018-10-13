//
//  main.cpp
//  BigInteger
//
//  Created by Viacheslav Ocheretnyi on 26.09.2018.
//  Copyright © 2018 Viacheslav Ocheretnyi. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "BigInteger.h"
#include "Fraction.h"

using namespace std;
using namespace BigIntegerLibrary;

int gauss(vector<vector<Fraction> > a, vector<Fraction>& ans) {
    const Fraction EPS(BigInteger(1), BigInteger(1000000));
    const int INF = 1e9;
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
         if (EPS > abs (a[sel][col]))
            continue;
        for (int i = col; i <= m; ++i)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = 0; i < n; ++i)
            if (i != row) {
                Fraction c = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j)
                    a[i][j] = a[i][j] - (a[row][j] * c);
            }
        ++row;
    }

    ans.assign(m, Fraction(0));
    for (int i = 0; i < m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i = 0; i < n; ++i) {
        Fraction sum(0);
        for (int j = 0; j < m; ++j)
            sum = sum + (ans[j] * a[i][j]);
        if (abs(sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i = 0; i < m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

void solveGauss() {
    ifstream cin("C:\\Users\\Viacheslav\\BigInteger\\BigInteger\\src\\gaussInputExample.txt");
    int n = 0, m = 0;
    cin >> n >> m;
    // n - кол-во уравнени
    // m - переменных
    vector<vector<Fraction> > a(n, vector<Fraction>(m + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            BigInteger tmp;
            cin >> tmp;
            a[i][j] = Fraction(tmp);
        }
    }
    for (int i = 0; i < n; ++i) {
        BigInteger tmp;
        cin >> tmp;
        a[i][m] = Fraction(tmp);
    }
    vector<Fraction> ans(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << setw(5) << right << a[i][j].getNumerator() << "x" << (j+1);
            if (j + 1 < m) {
                cout << " + ";
            }
        }
        cout << " = " << a[i][m].getNumerator() << "\n";
    }
    cout << "\n";
    int res = gauss(a, ans);
    cout << "Number of system solutions: " << res << "\n";
    if (res != 0) {
        for (int i = 0; i < ans.size(); ++i) {
            cout << 'x' << (i + 1) << " = " << ans[i].getNumerator() << '/' << ans[i].getDenominator() << ",\n";
        }
    }
}

int main() {
    solveGauss();
    return 0;
}
