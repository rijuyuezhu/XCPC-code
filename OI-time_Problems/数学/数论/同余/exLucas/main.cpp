#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
    ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}


void exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll a, ll m) {
    ll x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}
ll qpow(ll a, ll n, ll p) {
    ll ret = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) ret = ret * a % p;
    return ret;
}
ll fac(ll n, ll p, ll pk) {
    if(!n) return 1;
    ll ret = 1;
    for(int i = 1; i <= pk; i++)
        if(i % p) ret = ret * i % pk;
    ret = qpow(ret, n / pk, pk);
    for(int i = 1; i <= n % pk; i++)
        if(i % p) ret = ret * i % pk;
    return ret * fac(n / p, p, pk) % pk;
}
ll C(ll n, ll m, ll p, ll pk) {
    ll x = 0, y = 0, z = 0;
    for(ll i = p; i <= n; i *= p)
        x += n / i;
    for(ll i = p; i <= m; i *= p)
        y += m / i;
    for(ll i = p; i <= n-m; i *= p)
        z += (n-m) / i;
    return fac(n, p, pk) * inv(fac(m, p, pk), pk) % pk * inv(fac(n-m, p, pk), pk  ) % pk * qpow(p, x - y - z, pk) % pk;
}
ll a[55], b[55], tot;
ll CRT() {
    ll M = 1, ans = 0;
    for(int i = 1; i <= tot; i++) M *= b[i];
    for(int i = 1; i <= tot; i++) {
        ll Mi = M / b[i];
        ans = (ans + a[i] * inv(Mi, b[i]) * Mi) % M;
    }
    return ans % M;
}
ll exlucas(ll n, ll m, ll P) {
    for(int i = 2; 1ll * i * i <= P; i++) 
        if(P % i == 0) {
            ll pk = 1;
            while(P % i == 0) pk *= i, P /= i;
            ++tot;
            a[tot] = C(n, m, i, pk);
            b[tot] = pk;
        }
    if(P > 1) {
        ++tot;
        a[tot] = C(n, m, P, P);
        b[tot] = P;
    }
    return CRT();
}
int main() {
    ll n = read(), m = read(), p = read();
    printf("%lld\n", exlucas(n, m, p));
    return 0;
}