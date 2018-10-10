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

int main() {
    BigInteger a(0);
    cin >> a;
    try {
        cout << a.sqrt();
    } catch (exception &ex) {
        cout << ex.what() << "/n";
    }
    
    return 0;
}
