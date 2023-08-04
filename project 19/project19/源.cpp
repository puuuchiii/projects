#include <iostream>
#include <vector>

using namespace std;
extern int Multi_inverse(int a, int b);
extern pair<int, int> Point_Add(pair<int, int> P, pair<int, int> Q, int a, int mod_value);
extern int Hash(const std::string& str);
pair<int, int> ECDSA_Sign(int e, pair<int, int> G, int d, int k, int a, int mod_value, int n);
bool ECDSA_Verify(int e, pair<int, int> G, int r, int s, pair<int, int> P, int a, int mod_value, int n);
pair<int, int> Multi(int n, pair<int, int> point, int a, int mod_value);

int main() {
    int mod_value = 29;//椭圆曲线域上的模数
    int a = 4;
    int b = 20;
    pair<int, int> G = make_pair(13,23);
    int n = 37;//G点的基数
    string message = "12345678690";
    // cout << Point_Add(make_pair(5, 1), G, a, mod_value).first << endl;
    // cout << Multi(k, G, a, mod_value).first << endl;
    int d = 25;
    int e = Hash(message);
    int k = 6;
    pair<int, int> signature = ECDSA_Sign(e, G, d, k, a, mod_value,n);
    pair<int, int> P = Multi(d, G, a, mod_value);
    cout << "公钥为: (" << P.first << ", " << P.second << ")" << endl;
    cout << "签名为: ("<<signature.first<< ", " << signature.second <<")" << endl;
    ECDSA_Verify(e, G, signature.first, signature.second, P, a, mod_value,n);
    cout << "**************开始伪造签名***************" << endl;
    int u = rand() % (n - 1) + 1;
    int v = rand() % (n - 1) + 1;
    pair<int, int> R = Point_Add(Multi(u, G, a, mod_value), Multi(v, P, a, mod_value), a, mod_value);
    int r_ = R.first;
    int s_= r_* Multi_inverse(v,n);
    int e_ =u * s_;
    cout << "伪造签名为: (" << r_ << ", " << s_ << ")" << endl;
    ECDSA_Verify(e_, G, r_, s_, P, a, mod_value, n);
    return 0;
}