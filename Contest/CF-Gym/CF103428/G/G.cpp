#include <iostream>
#include <algorithm>
using namespace std;

constexpr int P = 998244353;
constexpr int MAXN = 5e4 + 5;

struct mint {
    int v;
    mint(int v = 0) : v(v) {}
};
int MOD(int v) {return v >= P ? v : v - P;}
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint qpow(mint a, int n) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}

int n, m, mxa;
int a[MAXN], b[MAXN], cnt[MAXN], q;
mint ans, fac[MAXN], ifac[MAXN];

mint C(int n, int m) {
    if(n < 0 || m < 0 || n < m)
        return 0;
    return fac[n] * ifac[m] * ifac[n-m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mxa = max(mxa, a[i]);
    }

    for(int k = 1; k < mxa && k <= m; k++)
        cout << 0 << '\n';
    if(mxa > m)
        return 0;
    fac[0] = 1;
    for(int i = 1; i <= mxa; i++)
        fac[i] = fac[i-1] * i;
    ifac[mxa] = qpow(fac[mxa], P-2);
    for(int i = mxa-1; i >= 0; i--)
        ifac[i] = ifac[i+1] * (i+1);
    ans = 1;
    for(int i = 1; i <= n; i++)
        ans = ans * C(mxa, a[i]);
    cout << ans.v << '\n';
    sort(a+1, a+1+n);
    a[0] = -1; q = 0;
    for(int i = 1; i <= n; i++)
        if(a[i] != a[i-1]) {
            b[++q] = a[i];
            cnt[q] = 1;
        } else 
            cnt[q]++;
    for(int k = mxa+1; k <= m; k++) {
        ans = ans * qpow(k, n);
        for(int i = 1; i <= q; i++)
            ans = ans * qpow(k - b[i], P - 1 - cnt[i]);
        cout << ans.v << '\n';
    }
    return 0;
}

