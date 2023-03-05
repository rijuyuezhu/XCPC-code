//https://www.luogu.com.cn/problem/P3372

#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e5 + 5;
struct Segtree {
    #define ls (o << 1)
    #define rs (o << 1 | 1)
    ll val[MAXN << 2];
    ll add[MAXN << 2];
    void pushup(int o) {
        val[o] = val[ls] + val[rs];
    }
    void build(int o, int l, int r, ll A[]) {
        if(l == r) {
            val[o] = A[l];
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, A);
        build(rs, m+1, r, A);
        pushup(o);
    }
    void addpoint(int o, int l, int r, ll k) {
        int len = r - l + 1;
        val[o] += len * k;
        add[o] += k;
    }
    void pushdown(int o, int l, int r) {
        if(add[o] != 0) {
            int m = (l + r) >> 1;
            addpoint(ls, l, m, add[o]);
            addpoint(rs, m+1, r, add[o]);
            add[o] = 0;
        }
    }
    void addrange(int o, int l, int r, int x, int y, ll k) {
        if(x <= l && r <= y) {
            addpoint(o, l, r, k);
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if(x <= m) addrange(ls, l, m, x, y, k);
        if(y > m) addrange(rs, m+1, r, x, y, k);
        pushup(o);
    }
    ll query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        ll ans = 0;
        if(x <= m) ans += query(ls, l, m, x, y);
        if(y > m) ans += query(rs, m+1, r, x, y);
        return ans;
    }
    #undef ls
    #undef rs
};
Segtree tr;

int n, m;
ll a[MAXN];

int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    tr.build(1, 1, n, a);
    for(int i = 1; i <= m; i++) {
        int opt = read();
        if(opt == 1) {
            int x = read(), y = read(); ll k = read();
            tr.addrange(1, 1, n, x, y, k);
        } else {
            int x = read(), y = read();
            printf("%lld\n", tr.query(1, 1, n, x, y));
        }
    }    
    return 0;
}