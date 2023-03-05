//https://www.luogu.com.cn/problem/P3811
#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 3e6 + 5;
ll n, p;
ll inv[MAXN];
int main() {
    n = read(), p = read();
    inv[1] = 1;
    printf("%lld\n", inv[1]);
    for(int i = 2; i <= n; i++) {
        inv[i] = (p - p / i) * inv[p % i] % p;
        printf("%lld\n", inv[i]);
    }
    
    return 0;
}