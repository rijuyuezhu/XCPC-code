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
struct Node {
    int sum, len, tag;
    int val1, lv1, rv1;
    int val0, lv0, rv0;
    void merge(Node a, Node b) {
        sum = a.sum + b.sum;

        if(a.val1 == a.len) lv1 = a.len + b.lv1;
        else lv1 = a.lv1;
        if(a.val0 == a.len) lv0 = a.len + b.lv0;
        else lv0 = a.lv0;

        if(b.val1 == b.len) rv1 = b.len + a.rv1;
        else rv1 = b.rv1;
        if(b.val0 == b.len) rv0 = b.len + a.rv0;
        else rv0 = b.rv0;

        val1 = max(max(a.val1, b.val1), a.rv1 + b.lv1);
        val0 = max(max(a.val0, b.val0), a.rv0 + b.lv0);
    }
}t[MAXN << 2];
struct Segment_tree {
    #define ls o << 1
    #define rs o << 1 | 1
    
    
    void build(int o, int l, int r, int a[]) {//ok
        t[o].len = r - l + 1; t[o].tag = 0;
        if(l == r) {
            t[o].sum = t[o].val1 = t[o].lv1 = t[o].rv1 = a[l];
            t[o].val0 = t[o].lv0 = t[o].rv0 = a[l]^1;
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, a); build(rs, m+1, r, a);
        t[o].merge(t[ls], t[rs]);
        /*
        https://www.luogu.com.cn/discuss/show/270442
        一定要注意，不能写成像t[o] = ..的东西！
        这样会覆盖掉len之类的，就会出错！
        */
    }
    void mdypoint(int o, int k) {
        if(k == 1) {
            t[o].sum = t[o].len - t[o].sum;
            swap(t[o].val0, t[o].val1); swap(t[o].lv0, t[o].lv1); swap(t[o].rv0, t[o].rv1);
            t[o].tag ^= 1;
        } else if(k == 2) {
            t[o].sum = t[o].val1 = t[o].lv1 = t[o].rv1 = 0;
            t[o].val0 = t[o].lv0 = t[o].rv0 = t[o].len;
            t[o].tag = 2;
        } else if(k == 3) {
            t[o].sum = t[o].val1 = t[o].lv1 = t[o].rv1 = t[o].len;
            t[o].val0 = t[o].lv0 = t[o].rv0 = 0;
            t[o].tag = 3;
        }
    }
    void pushdown(int o) {
        if(t[o].tag) {
            mdypoint(ls, t[o].tag);
            mdypoint(rs, t[o].tag);
            t[o].tag = 0;
        }
    }
    void mdyrange(int o, int l, int r, int x, int y, int k) {
        if(x <= l && r <= y) {
            mdypoint(o, k);
            return;
        }
        pushdown(o);
        int m = (l + r) >> 1;
        if(x <= m) mdyrange(ls, l, m, x, y, k);
        if(y > m) mdyrange(rs, m+1, r, x, y, k);
        t[o].merge(t[ls], t[rs]);
    }
    Node query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return t[o];
        pushdown(o);
        int m = (l + r) >> 1;
        if(y <= m) return query(ls, l, m, x, y);
        else if(x > m) return query(rs, m+1, r, x, y);
        else {
            Node ans; ans.merge(query(ls, l, m, x, y), query(rs, m+1, r, x, y));
            return ans;
        }
    }
    void print1(int o, int l, int r) {
        if(l == r) {
            printf("%d ", t[o].sum);
            return;
        }
        pushdown(o);
        int m = (l + r) >> 1;
        print1(ls, l, m); print1(rs, m+1, r);
    }
    void print2(int o, int l, int r) {
        if(l != r) pushdown(o);
        printf("%d[%d,%d]:%d,%d\n", o, l, r, t[o].sum, t[o].val1);
        if(l == r) return;
        int m = (l + r) >> 1;
        print2(ls, l, m); print2(rs, m+1, r);
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
    while(m--) {
        int opt = read(), l = read() + 1, r = read() + 1;
        switch(opt) {
            case 0:
                tr.mdyrange(1, 1, n, l, r, 2);
                break;
            case 1:
                tr.mdyrange(1, 1, n, l, r, 3);
                break;
            case 2:
                tr.mdyrange(1, 1, n, l, r, 1);
                break;
            case 3:
                printf("%d\n", tr.query(1, 1, n, l, r).sum);
                break;
            case 4:
                printf("%d\n", tr.query(1, 1, n, l, r).val1);
        }
    }
    return 0;
}