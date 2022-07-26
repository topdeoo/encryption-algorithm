#pragma once
#ifndef BIG_INT_H
#define BIG_INT_H

#include <string>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <memory>
#include <iostream>


class BigInt {
public:
    BigInt();
    BigInt(long long num);
    BigInt(const std::string& num);
    BigInt(const BigInt& other);
    ~BigInt() = default;

    friend std::ostream& operator << (std::ostream& os, BigInt num);
    friend std::istream& operator >> (std::istream& is, BigInt& num);

    BigInt& operator = (const BigInt& other);
    BigInt operator + (BigInt other);
    BigInt operator * (const BigInt& other);
    BigInt operator - (const BigInt& other);
    BigInt operator / (const BigInt& other);
    BigInt operator % (const BigInt& other);
    int abscompare(const BigInt& other);
    bool operator < (const BigInt& other);
    bool operator > (const BigInt& other);
    bool operator <= (const BigInt& other);
    bool operator >= (const BigInt& other);
    bool operator == (const BigInt& other);
    bool operator != (const BigInt& other);
private:
    BigInt operator * (const int s);
    void squeeze();
private:
    std::string _num;
    int sign;
};
#endif BIG_INT_H