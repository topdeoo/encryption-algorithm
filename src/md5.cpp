#include "md5.h"

md5::md5() {}

md5::md5(const string& msg) {
    this->msg = msg;
    reg[0] = 0x67452301;
    reg[1] = 0xefcdab89;
    reg[2] = 0x98badcfe;
    reg[3] = 0x10325476;
}

md5::~md5() {}

string md5::to_string() {
    return md5::cypher;
}

void md5::setMsg(const string& msg) {
    this->msg = msg;
    reg[0] = 0x67452301;
    reg[1] = 0xefcdab89;
    reg[2] = 0x98badcfe;
    reg[3] = 0x10325476;
    this->cypher = "";
}

void md5::encypher() {
    init(this->msg.size());
    for (int i = 0; i < 4; i++) {
        char res[10];
        sprintf(res, "%x", reg[i]);
        for (int i = 7; i >= 0; i -= 2) {
            this->cypher += res[i - 1];
            this->cypher += res[i];
        }
    }
}

void md5::init(size_t len) {
    bit32 iter = (len + 8) / 64 + 1;
    bit32* block = new bit32[iter * 16];
    memset(block, 0, sizeof block);
    for (int i = 0;i < len;i++) {
        block[i >> 2] |= (this->msg[i]) << ((i % 4) * 8);
    }
    block[len >> 2] |= 0x80 << ((len % 4) * 8);
    block[iter * 16 - 2] = len * 8;
    for (int i = 0;i < iter;i++) {
        bit32 block_i[16];
        for (int j = 0;j < 16;j++)
            block_i[j] = block[i * 16 + j];
        md5::transform(block_i);
    }
    delete[] block;
}

void md5::transform(const bit32 block[16]) {
    bit32 a = reg[0], b = reg[1], c = reg[2], d = reg[3];
    FF(a, b, c, d, block[0], s_11, 0xd76aa478);
    FF(d, a, b, c, block[1], s_12, 0xe8c7b756);
    FF(c, d, a, b, block[2], s_13, 0x242070db);
    FF(b, c, d, a, block[3], s_14, 0xc1bdceee);
    FF(a, b, c, d, block[4], s_11, 0xf57c0faf);
    FF(d, a, b, c, block[5], s_12, 0x4787c62a);
    FF(c, d, a, b, block[6], s_13, 0xa8304613);
    FF(b, c, d, a, block[7], s_14, 0xfd469501);
    FF(a, b, c, d, block[8], s_11, 0x698098d8);
    FF(d, a, b, c, block[9], s_12, 0x8b44f7af);
    FF(c, d, a, b, block[10], s_13, 0xffff5bb1);
    FF(b, c, d, a, block[11], s_14, 0x895cd7be);
    FF(a, b, c, d, block[12], s_11, 0x6b901122);
    FF(d, a, b, c, block[13], s_12, 0xfd987193);
    FF(c, d, a, b, block[14], s_13, 0xa679438e);
    FF(b, c, d, a, block[15], s_14, 0x49b40821);

    /* Round 2 */
    GG(a, b, c, d, block[1], s_21, 0xf61e2562);
    GG(d, a, b, c, block[6], s_22, 0xc040b340);
    GG(c, d, a, b, block[11], s_23, 0x265e5a51);
    GG(b, c, d, a, block[0], s_24, 0xe9b6c7aa);
    GG(a, b, c, d, block[5], s_21, 0xd62f105d);
    GG(d, a, b, c, block[10], s_22, 0x2441453);
    GG(c, d, a, b, block[15], s_23, 0xd8a1e681);
    GG(b, c, d, a, block[4], s_24, 0xe7d3fbc8);
    GG(a, b, c, d, block[9], s_21, 0x21e1cde6);
    GG(d, a, b, c, block[14], s_22, 0xc33707d6);
    GG(c, d, a, b, block[3], s_23, 0xf4d50d87);
    GG(b, c, d, a, block[8], s_24, 0x455a14ed);
    GG(a, b, c, d, block[13], s_21, 0xa9e3e905);
    GG(d, a, b, c, block[2], s_22, 0xfcefa3f8);
    GG(c, d, a, b, block[7], s_23, 0x676f02d9);
    GG(b, c, d, a, block[12], s_24, 0x8d2a4c8a);

    /* Round 3 */
    HH(a, b, c, d, block[5], s_31, 0xfffa3942);
    HH(d, a, b, c, block[8], s_32, 0x8771f681);
    HH(c, d, a, b, block[11], s_33, 0x6d9d6122);
    HH(b, c, d, a, block[14], s_34, 0xfde5380c);
    HH(a, b, c, d, block[1], s_31, 0xa4beea44);
    HH(d, a, b, c, block[4], s_32, 0x4bdecfa9);
    HH(c, d, a, b, block[7], s_33, 0xf6bb4b60);
    HH(b, c, d, a, block[10], s_34, 0xbebfbc70);
    HH(a, b, c, d, block[13], s_31, 0x289b7ec6);
    HH(d, a, b, c, block[0], s_32, 0xeaa127fa);
    HH(c, d, a, b, block[3], s_33, 0xd4ef3085);
    HH(b, c, d, a, block[6], s_34, 0x4881d05);
    HH(a, b, c, d, block[9], s_31, 0xd9d4d039);
    HH(d, a, b, c, block[12], s_32, 0xe6db99e5);
    HH(c, d, a, b, block[15], s_33, 0x1fa27cf8);
    HH(b, c, d, a, block[2], s_34, 0xc4ac5665);

    /* Round 4 */
    II(a, b, c, d, block[0], s_41, 0xf4292244);
    II(d, a, b, c, block[7], s_42, 0x432aff97);
    II(c, d, a, b, block[14], s_43, 0xab9423a7);
    II(b, c, d, a, block[5], s_44, 0xfc93a039);
    II(a, b, c, d, block[12], s_41, 0x655b59c3);
    II(d, a, b, c, block[3], s_42, 0x8f0ccc92);
    II(c, d, a, b, block[10], s_43, 0xffeff47d);
    II(b, c, d, a, block[1], s_44, 0x85845dd1);
    II(a, b, c, d, block[8], s_41, 0x6fa87e4f);
    II(d, a, b, c, block[15], s_42, 0xfe2ce6e0);
    II(c, d, a, b, block[6], s_43, 0xa3014314);
    II(b, c, d, a, block[13], s_44, 0x4e0811a1);
    II(a, b, c, d, block[4], s_41, 0xf7537e82);
    II(d, a, b, c, block[11], s_42, 0xbd3af235);
    II(c, d, a, b, block[2], s_43, 0x2ad7d2bb);
    II(b, c, d, a, block[9], s_44, 0xeb86d391);

    reg[0] += a;
    reg[1] += b;
    reg[2] += c;
    reg[3] += d;
}
