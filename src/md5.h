#pragma once
#ifndef MD5_H
#define MD5_H
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

/* Parameters of MD5. */
#define s_11 7
#define s_12 12
#define s_13 17
#define s_14 22
#define s_21 5
#define s_22 9
#define s_23 14
#define s_24 20
#define s_31 4
#define s_32 11
#define s_33 16
#define s_34 23
#define s_41 6
#define s_42 10
#define s_43 15
#define s_44 21

/* Basic Function of MD5 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))    
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* Rotate Left FUnction of MD5 */
#define ROTATELEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* Transform Function of MD5 */
#define FF(a, b, c, d, m, s, t) { \
  (a) += F ((b), (c), (d)) + (m) + t; \
  (a) = ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define GG(a, b, c, d, m, s, t) { \
  (a) += G ((b), (c), (d)) + (m) + t; \
  (a) = ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define HH(a, b, c, d, m, s, t) { \
  (a) += H ((b), (c), (d)) + (m) + t; \
  (a) = ROTATELEFT ((a), (s)); \
  (a) += (b); \
}
#define II(a, b, c, d, m, s, t) { \
  (a) += I ((b), (c), (d)) + (m) + t; \
  (a) = ROTATELEFT ((a), (s)); \
  (a) += (b); \
}


using std::string;

typedef unsigned int bit32;
typedef unsigned char byte;

class md5 {
private:
    string cypher;
    string msg;
    bit32 reg[4];
public:
    md5(const string& msg);
    ~md5();
    string to_string();
    void encypher();
private:
    void init(size_t len);
    void transform(const bit32 block[64]);
};

md5::md5(const string& msg) {
    this->msg = msg;
    reg[0] = 0x67452301;
    reg[1] = 0xefcdab89;
    reg[2] = 0x98badcfe;
    reg[3] = 0x10325476;
}

md5::~md5() {}
#endif
