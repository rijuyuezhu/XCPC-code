#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int P = 998244353;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
    int v;
    mint (int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint qpow(mint a, ll n) {
    mint ret = 1;
    for (; n; n >>= 1, a = a * a)
        if (n & 1)
            ret = ret * a;
    return ret;
}
ll n, m;

void work() {
    cin >> n >> m;
    mint pn = mint(n % P);
    cout << ( (pn - 1) * (1 - qpow(1 - 2 * qpow(pn, P-2), m)) ).v << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        work();
    return 0;
}
