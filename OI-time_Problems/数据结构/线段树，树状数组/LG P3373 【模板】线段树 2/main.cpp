//https://www.luogu.com.cn/problem/P3373

#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}

const int MAXN = 1e5 + 5;
int n, m, p;
int add(int a, int b) {return a + b < p ? a + b : a + b - p;}
int mns(int a, int b) {return a < b ? a - b + p : a - b;}
int mul(int a, int b) {return 1ll * a * b % p;}
int a[MAXN];
struct Segtree {
    #define ls (o << 1) 
    #define rs (o << 1 | 1)
    int val[MAXN << 2], ladd[MAXN << 2], lmul[MAXN << 2];
    void pushup(int o) {
        val[o] = add(val[ls], val[rs]);
    }
    void build(int o, int l, int r, int a[]) {
        lmul[o] = 1;
        if(l == r) {
            val[o] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, a);
        build(rs, m+1, r, a);
        pushup(o);
    }
    void addpoint(int o, int l, int r, int k) {
        int len = r - l + 1;
        val[o] = add(val[o], mul(len, k));
        ladd[o] = add(ladd[o], k);
    }
    void mulpoint(int o, int k) {
        val[o] = mul(val[o], k);
        ladd[o] = mul(ladd[o], k);
        lmul[o] = mul(lmul[o], k);
    }
    void pushdown(int o, int l, int r) {
        if(lmul[o] != 1) {
            mulpoint(ls, lmul[o]);
            mulpoint(rs, lmul[o]);
            lmul[o] = 1;
        }
        if(ladd[o] != 0) {
            int m = (l + r) >> 1;
            addpoint(ls, l, m, ladd[o]);
            addpoint(rs, m+1, r, ladd[o]);
            ladd[o] = 0;
        }
    }
    void addrange(int o, int l, int r, int x, int y, int k) {
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
    void mulrange(int o, int l, int r, int x, int y, int k) {
        if(x <= l && r <= y) {
            mulpoint(o, k);
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if(x <= m) mulrange(ls, l, m, x, y, k);
        if(y > m) mulrange(rs, m+1, r, x, y, k);
        pushup(o);
    }
    int query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        int ans = 0;
        if(x <= m) ans = add(ans, query(ls, l, m, x, y));
        if(y > m) ans = add(ans, query(rs, m+1,r, x, y));
        return ans;
    }
    #undef ls
    #undef rs
}tr;
int main() {
    n = read(), m = read(), p = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    tr.build(1, 1, n, a);
    for(int i = 1; i <= m; i++) {
        int opt = read();
        if(opt == 1) {
            int x = read(), y = read(), k = read() % p;
            tr.mulrange(1, 1, n, x, y, k);
        } else if(opt == 2) {
            int x = read(), y = read(), k = read() % p;
            tr.addrange(1, 1, n, x, y, k);
        }  else {
            int x = read(), y = read();
            printf("%d\n", tr.query(1, 1, n, x, y));
        }
    }
    return 0;
}