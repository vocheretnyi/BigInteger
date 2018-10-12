//
//  main.cpp
//  BigInteger
//
//  Created by Viacheslav Ocheretnyi on 26.09.2018.
//  Copyright © 2018 Viacheslav Ocheretnyi. All rights reserved.
//

#include <iostream>
#include <string>
#include "BigInteger.h"

using namespace std;
using namespace BigIntegerLibrary;

int main() {
    BigInteger a, b = 12;
    cin >> a;
    cout << a + b;

    return 0;
}
