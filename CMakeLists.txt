cmake_minimum_required(VERSION 3.12)
project(BigInteger)

set(CMAKE_CXX_STANDARD 14)

add_executable(BigInteger src/main.cpp src/BigInteger.cpp src/BigInteger.h src/Fraction.cpp src/Fraction.h)