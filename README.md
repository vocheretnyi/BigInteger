# BigInteger
BigInteger library for C++

* [Description](#description)   
* [Operators](#operators)
  * [Addition](#addition)
  * [Subtraction](#subtraction)
  * [Multiplication](#multiplication)
  * [Comparison](#comparison)
  * [Streaming operators](#streaming-operators)
* [Methods](#methods)
  * [to_string](#to_stringBigInteger)
* [Functions](#functions)
  * [abs](#absBigInteger)
  * [pow](#powint)
  

# Description
Implementation of long arithmetic on C++.

# Operators
## Addition
```C++
BigIntegerLibrary::BigInteger a, b, c;
c = a + b;
c += a;
c = a + 6;
c += 6;
```
## Subtraction
```C++
BigIntegerLibrary::BigInteger a, b, c;
c = a - b;
c -= a;
c = a - 6;
c -= 6;
```
## Multiplication
```C++
BigIntegerLibrary::BigInteger a, b, c;
c = a * b;
c *= a;
c = a * 6;
c *= 6;
```
## Comparison
```C++
BigIntegerLibrary::BigInteger a(152);
BigIntegerLibrary::BigInteger b(22943);

if (a == b) cout << "A is equal to B";
if (a < b) cout << "A is less than B";
if (a > b) cout << "A is greater than B";
if (a >= b) cout << "A is greater than or equal to B";
if (a <= b) cout << "A is less than or equal to B";
if (a != b) cout << "A is not equal to B";
```
## Stream operators
```C++
BigIntegerLibrary::BigInteger a, b;
cin >> a >> b;
cout << a * b;
```
# Methods
## to_string()
Converts the big integer to a string.
```C++
BigIntegerLibrary::BigInteger a(-152);
string str = a.to_string();
```
# Functions
## abs(BigInteger)
Absolute value.
```C++
BigIntegerLibrary::BigInteger a(-152);
cout << abs(a); // 152
```
## pow(BigInteger, long long)
Raises to the power of N.
```C++
Dodecahedron::Bigint a = 19;
cout << pow(a, 87); // ~1.784e+111
```
