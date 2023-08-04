#pragma once
#include <iostream>
#include <vector>
#include<string>
using namespace std;


struct sign {
    pair<int, int> R;
    int s;
};
// 辗转相除法求最大公约数
int get_gcd(int a, int b) {
    int re = a % b;
    while (re != 0) {
        a = b;
        b = re;
        int k = a / b;
        re = a % b;
    }
    return b;
}

// 改进欧几里得算法求线性方程的x与y
pair<int, int> get_(int a, int b) {
    if (b == 0) {
        return make_pair(1, 0);
    }
    else {
        int k = a / b;
        int remainder = a % b;
        pair<int, int> p = get_(b, remainder);
        int x1 = p.first;
        int y1 = p.second;
        int x = y1;
        int y = x1 - k * y1;
        return make_pair(x, y);
    }
}

// 返回乘法逆元
int Multi_inverse(int a, int b) {
    // 将初始b的绝对值进行保存
    int m = (b < 0) ? abs(b) : b;
    int flag = get_gcd(a, b);
    // 判断最大公约数是否为1，若不是则没有逆元
    if (abs(flag) == 1) {
        pair<int, int> p = get_(a, b);
        int x = p.first;
        int y = p.second;
        int x0 = x % m;
        return x0;
    }
    else {
        cout << "Do not have!" << endl;
        return 0;
    }
}



// 所用的椭圆曲线
// y^2 = x^3 + ax + by mod (mod_value)

pair<int, int> Point_Add(pair<int, int> P, pair<int, int> Q, int a, int mod_value) {
    if (P.first == Q.first) {
        int fenzi = (3 * P.first * P.first + a) % mod_value;
        int fenmu = (2 * P.second) % mod_value;
        int val = Multi_inverse(fenmu, mod_value);
        int y = (fenzi * val) % mod_value;
        int Rx = (y * y - P.first - Q.first + mod_value) % mod_value;
        int Ry = (y * (P.first - Rx) - P.second + mod_value) % mod_value;
        return make_pair(Rx, Ry);
    }
    else {
        int fenzi = (Q.second - P.second + mod_value) % mod_value;
        int fenmu = (Q.first - P.first + mod_value) % mod_value;
        int val = Multi_inverse(fenmu, mod_value);
        int y = (fenzi * val) % mod_value;
        int Rx = (y * y - P.first - Q.first + mod_value) % mod_value;
        int Ry = (y * (P.first - Rx) - P.second + mod_value) % mod_value;
        return make_pair(Rx, Ry);
    }
}

pair<int, int> Multi(int n, pair<int, int> point, int a, int mod_value) {
    if (n == 0) {
        return make_pair(0, 0);
    }
    else if (n == 1) {
        return point;
    }
    pair<int, int> t = point;
    while (n >= 2) {
        t = Point_Add(t, point, a, mod_value);
        n = n - 1;
    }
    return t;
}

pair<int, int> double_point(pair<int, int> point, int a, int mod_value) {
    return Point_Add(point, point, a, mod_value);
}

pair<int, int> fast_Multi(int n, pair<int, int> point, int a, int mod_value) {
    if (n == 0) {
        return make_pair(0, 0);
    }
    else if (n == 1) {
        return point;
    }
    else if (n % 2 == 0) {
        return Multi(n / 2, double_point(point, a, mod_value), a, mod_value);
    }
    else {
        return Point_Add(Multi((n - 1) / 2, double_point(point, a, mod_value), a, mod_value), point, a, mod_value);
    }
}

int Hash(const std::string& str) {
    int h = 0;
    const char* c_str = str.c_str(); // 将std::string转换为const char*
    for (int i = 0; c_str[i] != '\0'; i++) {
        h = (h * 31 + c_str[i]) % 19; // 这里使用简单的哈希函数，可以根据实际需要替换为更强大的哈希函数
    }
    return h;
}
using namespace std;


struct sign Schnorr_Sign(int mod_value,string m,int prikey, pair<int, int> G,int a,int n) {
    int k = rand() % (mod_value - 1) + 1;
    pair<int, int> R = Multi(k, G, a, mod_value);
    string message = m + to_string(R.first) + to_string(R.second);
    int e = Hash(message)%n;
    int s = (k + e * prikey)%n;
    struct sign ret;
    ret.R = R;
    ret.s = s;
    return ret;
}

bool sign_Verify(struct sign sign,string m, pair<int, int> G, pair<int, int> pubkey, int a, int mod_value) {
    string message = m + to_string(sign.R.first) + to_string(sign.R.second);
    int e = Hash(message)%19;
    pair<int, int> A = Multi(sign.s, G, a, mod_value);
    pair<int, int> B = Point_Add(Multi(e,pubkey, a, mod_value), sign.R, a, mod_value);
    cout << "普通签名认证：" << endl;
     if ((A.first % mod_value) == (B.first%mod_value)) {
            cout << "签名验证通过！" << endl;
            return true;
        }
        else {
            cout << "签名不通过" << endl;
            return false;
        }
    }


bool sign_Verify_Batch(struct sign sign[3], string m[3], pair<int, int> G, pair<int, int> pubkey, int a, int mod_value, int n) {
    int bisi = sign[0].s;
    pair<int, int> biRi = sign[0].R;
    string message = m[0] + to_string(sign[0].R.first) + to_string(sign[0].R.second);
    int e = Hash(message) % n;
    int  eibi = e;
    pair<int, int> B;
    pair<int, int> A;
    int b;
    for (int i = 1;i < 3;i++) {
        b = rand() % (mod_value - 1) + 1;
        bisi = bisi + b * sign[i].s;
        biRi = Point_Add(Multi(b, sign[i].R, a, mod_value), biRi, a, mod_value);
        message = m[i] + to_string(sign[i].R.first) + to_string(sign[i].R.second);
        e = Hash(message) % n;
        eibi = eibi+e * b;
    }
    cout << "批量验签：" << endl;
    A = Multi(bisi%n, G, a, mod_value);
    B = Point_Add(Multi(eibi%n, pubkey, a, mod_value), biRi, a, mod_value);
    if ((A.first % mod_value) == (B.first % mod_value)) {
        cout << "签名验证通过！" << endl;
        return true;
    }
    else {
        cout << "签名不通过" << endl;
        return false;
    }
}




