#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e5 + 5;
ll qpow(ll a, ll n, ll M) {
    ll ret = 1;
    for(; n; a = a * a % M, n >>= 1)
        if(n & 1)
            ret = ret * a % M;
    return ret % M;
}
ll gcd(ll a, ll b) {
    return !b ? a : gcd(b, a % b);
}
int n;
ll A[MAXN], g, mxv;
void work() {
    cin >> n;
    g = mxv = 0;
    for(int i = 1; i <= n; i++)
        cin >> A[i], mxv = max(mxv, A[i]);
    for(int i = 1; i <= n; i++)
        if(g == 0) {
            g = abs((1ll << (i-1)) - A[i]);//g inside 2^30
        } else {
            g = gcd(g, (qpow(2, i-1, g) - A[i]) % g + g);
        }
    if(g <= mxv) {
        cout << -1 << '\n';
        return ;
    }
    if(g == 1) {
        cout << g << '\n';
        return ;
    }
    ll g2 = 0;
    for(ll i = 2; i * i <= g; i++)
        if(g % i == 0) {
            g2 = g / i;
            break;
        }
    if(!g2)
        g2 = 1;
    if(g2 <= mxv) {
        cout << g << '\n';//assure g is the only one
    } else {
        cout << -1 << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--)
        work();
    return 0;
}
