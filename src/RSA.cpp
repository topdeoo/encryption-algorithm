#include "RSA.h"

typedef unsigned long long ull;

const ull e = 65537;
const string _base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const string table[] = {
    "00", "01", "02","03", "04", "05","06", "07", "08","09",
    "10", "11","12","13", "14","15","16", "17","18","19",
    "20","21","22","23","24","25","26"
};

ull qmul(ull a, ull b, ull mod) {
    ull res = 0;
    while (b) {
        if (b & 1) res = (a + res) % mod;
        a = a * 2 % mod;
        b >>= 1;
    }
    return res % mod;
}

ull qpow(ull a, ull n, ull mod) {
    ull res = 1;
    while (n) {
        if (n & 1) res = qmul(res, a, mod);
        a = qmul(a, a, mod);
        n >>= 1;
    }
    return res % mod;
}

int exgcd(ull a, ull b, ull& x, ull& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }

    int d = exgcd(b, a % b, y, x);

    y = y - a / b * x;
    return d;
}

inline ull inv(ull a, ull m) {
    ull x, y;
    int d = exgcd(a, m, x, y);
    if (d == 1)
        return x;
}

bool Miller_Rabin(ull n) {
    if (n == 2) return true;
    if (!(n & 1) || n < 2) return false;
    ull s = 0, t = n - 1;
    while (!(t & 1)) {
        s++;
        t >>= 1;
    }
    for (int i = 0; i < 20; i++) {
        ull a = rand() % (n - 1) + 1;
        ull x = qpow(a, t, n);
        for (int j = 1; j <= s; j++) {
            ull test = qmul(x, x, n);
            if (test == 1 && x != 1 && x != n - 1) return false;
            x = test;
        }
        if (x != 1) return false;
    }
    return true;
}

string trans(ull msg) {
    string ret;
    while (msg) {
        int temp = (msg % 10) + '0';
        string s;
        while (temp) {
            s += char((temp & 1) + '0');
            temp >>= 1;
        }
        while (s.length() < 8)
            s.append("0");
        ret.append(s);
        msg /= 10;
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

string base64(const ull& msg) {
    string temp = trans(msg);
    int cnt = 0;
    if (temp.length() % 6 <= 2 && temp.length() % 6 != 0)
        cnt = 1;
    else if (temp.length() % 6 > 3)
        cnt = 2;
    while (temp.length() % 3 != 0) {
        temp.append("0");
    }
    string ret;
    for (int i = 0; i < temp.length(); i += 6) {
        int idx = 0;
        for (int j = i; j < i + 6; j++)
            idx = idx * 2 + temp[j] - '0';
        ret += _base64_table[idx];
    }
    if (cnt == 2)
        ret += '=';
    else if (cnt == 1)
        ret.append("==");
    return ret;
}

RSA::RSA() {
    RSA::gen_key();
}

RSA::~RSA() {}

string RSA::to_string() {
    string base64_pu = base64(this->pu), base64_pv = base64(this->pv);
    return base64_pu + ", " + base64_pv;
}

void RSA::gen_key() {
    srand(time(NULL));
    int cnt = 0;
    ull prime[2];
    ull bound = INT64_MAX / e;
    ull phi;
    while (cnt < 2) {
        ull r = rand() % bound + e;
        if (Miller_Rabin(r)) {
            if (cnt == 0)
                prime[cnt++] = r;
            else if (r != prime[0])
                prime[cnt++] = r;
        }
    }
    this->n = prime[0] * prime[1];
    phi = (prime[0] - 1) * (prime[1] - 1);
    this->pu = e;
    this->pv = inv(e, phi);
}

vector<string> RSA::encypher(const string& msg) {
    string msg_trans;
    for (auto& i : msg)
        msg_trans.append(table[tolower(i) - 'a']);
    vector<string> c;
    for (int i = 0; i < msg_trans.length(); i += 2) {
        ull x = 0;
        for (int j = i; j < i + 2; j++)
            x = x * 10 + msg_trans[j] - '0';

        c.push_back(std::to_string(qpow(x, this->pu, this->n)));
    }
    return c;
}

string RSA::decypher(const vector<string>& msg) {
    string text;
    for (auto& i : msg) {
        ull x;
        for (auto& j : i) {
            x = x * 10 + j - '0';
        }
        text.append(std::to_string(qpow(x, this->pv, this->n)));
    }
    return text;
}


ull RSA::encypher(const ull& msg) {
    return qpow(msg, this->pu, this->n);
}


ull RSA::decypher(const ull& msg) {
    return qpow(msg, this->pv, this->n);
}
