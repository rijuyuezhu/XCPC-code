// https://www.luogu.com.cn/problem/P4513
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
const int MAXN = 500005;
struct Segment_tree {
    #define ls o << 1
    #define rs o << 1 | 1
    struct Node {
        int sum, val, lv, rv;
        void merge(const Node& a, const Node& b)const {//status combination
            Node res;
            res.sum = a.sum + b.sum;
            res.lv = max(a.lv, a.sum + b.lv);
            res.rv = max(b.rv, b.sum + a.rv);
            res.val = max(max(a.val, b.val), a.rv + b.lv);
            return res;
    }
    }t[MAXN << 2];
    Node merge(const Node& a, const Node& b)const {//status combination
        Node res;
        res.sum = a.sum + b.sum;
        res.lv = max(a.lv, a.sum + b.lv);
        res.rv = max(b.rv, b.sum + a.rv);
        res.val = max(max(a.val, b.val), a.rv + b.lv);
        return res;
    }
    void build(int o, int l, int r, int a[]) {
        t[o].sum = t[o].val = t[o].lv = t[o].rv = a[l]; //at least choose one num
        if(l == r) return;
        int m = (l + r) >> 1;
        build(ls, l, m, a); build(rs, m+1, r, a);
        t[o] = merge(t[ls], t[rs]);
    }
    void mdypoint(int o, int l, int r, int x, int k) {
        if(l == r) {
            t[o].sum = t[o].val = t[o].lv = t[o].rv = k;
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) mdypoint(ls, l, m, x, k);
        else mdypoint(rs, m+1, r, x, k);
        t[o] = merge(t[ls], t[rs]);
    }
    Node query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return t[o];
        int m = (l + r) >> 1;
        if(y <= m) return query(ls, l, m, x, y);
        else if(x > m) return query(rs, m+1, r, x, y);
        else return merge(query(ls, l, m, x, y), query(rs, m+1, r, x, y));
    }
    #undef ls
    #undef rs
}tr;
int n, m;
int a[MAXN];
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    tr.build(1, 1, n, a);
    for(int i = 1; i <= m; i++) {
        int opt = read();
        if(opt == 1) {
            int a = read(), b = read();
            if(a > b) swap(a, b);
            printf("%d\n", tr.query(1, 1, n, a, b).val);
        } else {
            int p = read(), s = read();
            tr.mdypoint(1, 1, n, p, s);
        }
    }
    return 0;
}