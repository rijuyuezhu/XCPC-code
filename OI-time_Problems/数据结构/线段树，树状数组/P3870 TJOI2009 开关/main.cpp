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
    #define ls o << 1
    #define rs o << 1 | 1
    int val[MAXN << 2];//save the count of lights that were turned on
    int rev[MAXN << 2];//the range need[=1] or needn't[=0] to reverse
    void pushup(int o) {
        val[o] = val[ls] + val[rs];
    }
    void changep(int o, int l, int r) {
        val[o] = (r - l + 1) - val[o];
        rev[o] ^= 1;
    }
    void pushdown(int o, int l, int r) {
        if(rev[o]) {
            int m = (l + r) >> 1;
            changep(ls, l, m);
            changep(rs, m + 1, r);
            rev[o] = 0;
        }
    }
    void changer(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            changep(o, l, r);
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if(x <= m) changer(ls, l, m, x, y);
        if(y > m) changer(rs, m + 1, r, x, y);
        pushup(o);
    }
    int query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        pushdown(o, l, r);
        int ans = 0, m = (l + r) >> 1;
        if(x <= m) ans += query(ls, l, m, x, y);
        if(y > m) ans += query(rs, m + 1, r, x, y);
        return ans;
    }
    #undef ls
    #undef rs
};
int n, m;
Segtree tr;
int main() {
    n = read(), m = read();
    while(m--) {
        int c = read(), a = read(), b = read();
        if(c == 0) {
            tr.changer(1, 1, n, a, b);
        } else {
            printf("%d\n", tr.query(1, 1, n, a, b));
        }
    }
    return 0;
}