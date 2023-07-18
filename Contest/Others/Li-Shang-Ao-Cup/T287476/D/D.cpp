#include <iostream>
using namespace std;
const int MAXN = 10005;
const int P = 19260817;
int MOD(int v) {return v >= P ? v - P : v;}
int pls(int a, int b) {return MOD(a + b);}
int mns(int a, int b) {return MOD(a - b + P);}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n = P-2) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, S[MAXN][2], fac[MAXN], ifac[MAXN];
int C(int n, int m) {
    return 1ll * fac[n] * ifac[m] % P * ifac[n-m] % P;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    S[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        int now = i & 1, pre = now ^ 1;
        S[0][now] = 0;
        for(int j = 1; j <= i; j++) {
            S[j][now] = pls(S[j-1][pre], mul(j, S[j][pre]));
        }
    }
    fac[0] = 1;
    for(int i = 1; i <= n; i++)
        fac[i] = mul(fac[i-1], i);
    ifac[n] = qpow(fac[n]);
    for(int i = n-1; i >= 0; i--)
        ifac[i] = mul(ifac[i+1], i+1);
    int ans = 0;
    for(int i = 1; i <= n; i++)
        ans = pls(ans, 1ll * i * fac[i] * C(n, i) % P * S[i][n & 1] % P);
    cout << ans;
    return 0;
}