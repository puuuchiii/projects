#include <iostream>
#include <vector>
using namespace std;
struct sign {
    pair<int, int> R;
    int s;
};

extern int Multi_inverse(int a, int b);
extern pair<int, int> Point_Add(pair<int, int> P, pair<int, int> Q, int a, int mod_value);
extern int Hash(const string& str);
pair<int, int> Multi(int n, pair<int, int> point, int a, int mod_value);
extern struct sign Schnorr_Sign(int mod_value, string m, int prikey, pair<int, int> G, int a,int n);
extern bool sign_Verify_Batch(struct sign sign[5], string m[5], pair<int, int> G, pair<int, int> pubkey, int a, int mod_value, int n);
extern bool sign_Verify(struct sign sign, string m, pair<int, int> G, pair<int, int> pubkey, int a, int mod_value);
int main() {
    int mod_value = 17;//椭圆曲线域上的模数
    int a = 2;
    int b = 2;
    pair<int, int> G = make_pair(7, 1);
    int n =19;//G点的基数
    int prikey = 2;
    pair<int, int> pubkey = Multi(prikey, G, a, mod_value);
    string message[3] = { "message1", "message2", "message3"};
    struct sign sign[3];
    cout << "分别对3个消息签名中……" << endl;
    for (int i = 0; i < 3; i++) {
        sign[i] = Schnorr_Sign(mod_value, message[i], prikey, G, a, n);
    }
    bool result = sign_Verify(sign[0], message[0], G, pubkey, a, mod_value);
   result=sign_Verify_Batch(sign,message,G, pubkey, a, mod_value, n);

    return 0;
}