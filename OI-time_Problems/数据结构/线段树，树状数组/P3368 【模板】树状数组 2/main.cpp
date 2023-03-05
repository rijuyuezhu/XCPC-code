//https://www.luogu.com.cn/problem/P3368
#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 500005;
int n, m;
struct BItree {
    ll t[MAXN];
    static int lowbit(int x) {return x & (-x);}
    void add(int x, ll k) {
        for(int i = x; i <= n; i += lowbit(i)) t[i] += k;
    }
    ll sum(int x) {
        ll ans = 0;
        for(int i = x; i; i -= lowbit(i)) ans += t[i];
        return ans;
    }
}tr;
ll a[MAXN];
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++) {
        a[i] = read();
    }
    for(int i = 1; i <= m; i++) {
        int opt = read();
        if(opt == 1) {
            int x = read(), y = read();
            ll k = read();
            tr.add(x, k); tr.add(y + 1, -k);
        } else {
            int x = read();
            printf("%lld\n", a[x] + tr.sum(x));
        }
    }
    return 0;
}