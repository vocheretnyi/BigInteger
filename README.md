# BigInteger

* [Description](#description)   
* [Operators](#operators)
  * [Addition](#addition)
  * [Subtraction](#subtraction)
  * [Multiplication](#multiplication)
  * [Dividing](#dividing)
  * [Comparison](#comparison)
  * [Streaming operators](#streaming-operators)
* [Methods](#methods)
  * [to_string](#to_string)
* [Functions](#functions)
  * [abs](#absbiginteger)
  * [pow](#powbiginteger-long-long)
  * [sqrt](#sqrtbiginteger)
  

# Description
Implementation of long arithmetic on C++.

# Operators
## Addition
```C++
BigIntegerLibrary::BigInteger numerator, denominator, c;
c = numerator + denominator;
c += numerator;
c = numerator + 6;
c += 6;
```
## Subtraction
```C++
BigIntegerLibrary::BigInteger numerator, denominator, c;
c = numerator - denominator;
c -= numerator;
c = numerator - 6;
c -= 6;
```
## Multiplication
```C++
BigIntegerLibrary::BigInteger numerator, denominator, c;
c = numerator * denominator;
c *= numerator;
c = numerator * 6;
c *= 6;
```
## Dividing
```C++
BigIntegerLibrary::BigInteger numerator, denominator, c;
c = numerator / denominator;
c /= numerator;
c = numerator / 6;
c /= 6;
c = numerator % denominator;
c %= numerator;
c = numerator % 6;
c %= 6;
```
## Comparison
```C++
BigIntegerLibrary::BigInteger numerator(152);
BigIntegerLibrary::BigInteger denominator(22943);

if (numerator == denominator) cout << "A is equal to B";
if (numerator < denominator) cout << "A is less than B";
if (numerator > denominator) cout << "A is greater than B";
if (numerator >= denominator) cout << "A is greater than or equal to B";
if (numerator <= denominator) cout << "A is less than or equal to B";
if (numerator != denominator) cout << "A is not equal to B";
```
## Stream operators
```C++
BigIntegerLibrary::BigInteger numerator, denominator;
cin >> numerator >> denominator;
cout << numerator * denominator;
```
# Methods
## to_string()
Converts the big integer to numerator string.
```C++
BigIntegerLibrary::BigInteger numerator(-152);
string str = numerator.to_string();
```
# Functions
## abs(BigInteger)
Absolute value.
```C++
BigIntegerLibrary::BigInteger numerator(-152);
cout << abs(numerator); // 152
```
## pow(BigInteger, long long)
Raises to the power of N.
```C++
BigIntegerLibrary::BigIntegert numerator = 19;
cout << pow(numerator, 87); // ~1.784e+111
```
## sqrt(BigInteger)
Return the int part of squared root.
```C++
BigIntegerLibrary::BigInteger numerator = 120;
cout << sqrt(numerator); // [~10.954] = 10
```
