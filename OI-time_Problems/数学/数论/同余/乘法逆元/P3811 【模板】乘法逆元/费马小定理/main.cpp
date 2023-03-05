//https://www.luogu.com.cn/problem/P3811
#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
ll n, p;
ll ksm(ll a, ll k) {
    a %= p;
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return ans % p;
}
int main() {
    n = read(), p = read();
    for(int i = 1; i <= n; i++) printf("%lld\n", ksm(i, p - 2));
    return 0;
}