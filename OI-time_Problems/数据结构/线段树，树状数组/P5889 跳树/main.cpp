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
const int MAXM = 5e5 + 5;
int n, m, q;
struct Node {
    int up;
    int down;
    ll s;
    void merge(Node a, Node b) {
        if(a.down <= b.up) {
            up = a.up - a.down + b.up;
            down = b.down;
            s = b.s;
        } else {
            up = a.up;
            down = a.down - b.up + b.down;
            s = (((a.s) >> b.up) << b.down) + b.s;
        }
    }
};
struct Segment_tree {
    #define ls o << 1
    #define rs o << 1 | 1
    Node t[MAXM << 2];
    void apply(int o, int k) {
        if(k == 1) t[o].up = 0, t[o].down = 1, t[o].s = 0;
        else if(k == 2) t[o].up = 0, t[o].down = 1, t[o].s = 1;
        else t[o].up = 1, t[o].down = 0, t[o].s = 0;
    }
    void build(int o, int l, int r, int a[]) {
        if(l == r) {
            apply(o, a[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, a); build(rs, m+1, r, a);
        t[o].merge(t[ls], t[rs]);
    }
    void mdypos(int o, int l, int r, int x, int k) {
        if(l == r) {
            apply(o, k);
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) mdypos(ls, l, m, x, k);
        else mdypos(rs, m+1, r, x, k);
        t[o].merge(t[ls], t[rs]);
    }
    Node query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return t[o];
        int m = (l + r) >> 1;
        if(y <= m) return query(ls, l, m, x, y);
        else if(x > m) return query(rs, m+1, r, x, y);
        else {
            Node ans;
            ans.merge(query(ls, l, m, x, y), query(rs, m+1, r, x, y));
            return ans;
        }
    }
    #undef ls
    #undef rs
}tr;
int a[MAXM];
int main() {
    n = read(), m = read(), q = read();
    for(int i = 1; i <= m; i++) a[i] = read();
    tr.build(1, 1, m, a);
    for(int i = 1; i <= q; i++) {
        int opt = read();
        if(opt == 1) {
            ll s = read(), x = read(), y = read();
            Node t = tr.query(1, 1, m, x, y);
            printf("%lld\n", (max(1ll, s >> t.up) << t.down) + t.s);
        } else {
            int x = read(), y = read();
            tr.mdypos(1, 1, m, x, y);
        }
    }
    return 0;
}