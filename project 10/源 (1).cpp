#include <iostream>
#include <vector>

using namespace std;

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
        h = (h * 31 + c_str[i]) % 37; // 这里使用简单的哈希函数，可以根据实际需要替换为更强大的哈希函数
    }
    return h;
}

pair<int, int> ECDSA_Sign(int e, pair<int, int> G, int d, int k, int a, int mod_value, int n) {
    pair<int, int> R = Multi(k, G, a, mod_value);  // R = kG
    int r = R.first % n;  // r = Rx mod n
    int s = (Multi_inverse(k, n) * (e + d * r)) % n;
    return make_pair(r, s);
}

bool ECDSA_Verify(int e, pair<int, int> G, int r, int s, pair<int, int> P, int a, int mod_value, int n) {
    int w = Multi_inverse(s, n);
    int ele1 = (e * w) % n;
    if (ele1 < 0) {
        ele1 += n;
    }
    int ele2 = (r * w) % n;
    if (ele1 < 0) {
        ele2 += n;
    }
    pair<int, int> w_point = Point_Add(Multi(ele1, G, a, mod_value), Multi(ele2, P, a, mod_value), a, mod_value);
    if (w_point.first == 0) {
        cout << "false" << endl;
        return false;
    }
    else {
        if (w_point.first == r) {
            cout << "签名验证通过" << endl;
            return true;
        }
        else {
            cout << "签名不通过" << endl;
            return false;
        }
    }
}



int main() {
    int mod_value = 29;//椭圆曲线域上的模数
    int a = 4;
    int b = 20;
    pair<int, int> G = make_pair(13, 23);
    int n = 37;//G点的基数
    string message = "hello world";
    int d = 25;
    int e = Hash(message);
    int k = 6;
    pair<int, int> signature = ECDSA_Sign(e, G, d, k, a, mod_value, n);
    pair<int, int> P = Multi(d, G, a, mod_value);
    cout << "公钥为: (" << P.first << ", " << P.second << ")" << endl;
    cout << "签名为: (" << signature.first << ", " << signature.second << ")" << endl;
    ECDSA_Verify(e, G, signature.first, signature.second, P, a, mod_value, n);
   
    return 0;
}