// https://www.luogu.com.cn/problem/CF438D
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e5 + 5;
struct Segment_tree {
    #define ls o << 1
    #define rs o << 1 | 1
    ll val[MAXN << 2], maxv[MAXN << 2];
    void pushup(int o) {
        val[o] = val[ls] + val[rs];
        maxv[o] = max(maxv[ls], maxv[rs]);
    }
    void build(int o, int l, int r, ll a[]) {
        if(l == r) {
            val[o] = maxv[o] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, a); build(rs, m+1, r, a);
        pushup(o);
    }
    void modrange(int o, int l, int r, int x, int y, ll p) {
        if(maxv[o] < p) return;
        if(l == r) {
            maxv[o] %= p;
            val[o] %= p;
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) modrange(ls, l, m, x, y, p);
        if(y > m) modrange(rs, m + 1, r, x, y, p);
        pushup(o);
    }
    void mdypos(int o, int l, int r, int x, ll k) {
        if(l == r) {
            maxv[o] = val[o] = k;
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) mdypos(ls, l, m, x, k);
        else mdypos(rs, m+1, r, x, k);
        pushup(o);
    }
    ll query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        int m = (l + r) >> 1;
        if(y <= m) return query(ls, l, m, x, y);
        else if(x > m) return query(rs, m+1, r, x, y);
        else return query(ls, l, m, x, y) + query(rs, m+1, r, x, y);
    }
    #undef ls
    #undef rs
}tr;
int n, m;
ll a[MAXN];
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    tr.build(1, 1, n, a);
    for(int i = 1; i <= m; i++) {
        int opt = read();
        if(opt == 1) {
            int l = read(), r = read();
            printf("%lld\n", tr.query(1, 1, n, l, r));
        } else if(opt == 2) {
            int l = read(), r = read(); ll x = read();
            tr.modrange(1, 1, n, l, r, x);
        } else {
            int k = read(), x = read();
            tr.mdypos(1, 1, n, k, x);
        }
    }
    return 0;
}