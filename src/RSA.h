#pragma once
#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
using std::vector;
using std::string;

typedef unsigned long long ull;

class RSA {
private:
    ull pu, pv;
    ull n;
public:
    RSA();
    ~RSA();
    string to_string();
    vector<string> encypher(const string& msg);
    string decypher(const vector<string>& msg);
    ull encypher(const ull& msg);
    ull decypher(const ull& msg);

private:
    void gen_key();
};
#endif RSA_H