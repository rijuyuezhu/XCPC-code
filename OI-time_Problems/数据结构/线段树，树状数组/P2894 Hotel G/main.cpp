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
const int MAXN = 50005;
/*
要维护的信息：
某个节点的最长空余长度
*/
struct Segment_tree {
    #define ls o << 1
    #define rs o << 1 | 1
    int val[MAXN << 2], lv[MAXN << 2], rv[MAXN << 2], tag[MAXN << 2], len[MAXN << 2];
    void build(int o, int l, int r) {
        val[o] = lv[o] = rv[o] = len[o] = r - l + 1;
        tag[o] = 0;
        if(l == r) return;
        int m = (l + r) >> 1;
        build(ls, l, m);
        build(rs, m+1, r);
    }
    void pushup(int o, int l, int r) {
        if(val[ls] == len[ls]) lv[o] = len[ls] + lv[rs];
            else lv[o] = lv[ls];
        if(val[rs] == len[rs]) rv[o] = rv[ls] + len[rs];
            else rv[o] = rv[rs];
        val[o] = max(max(val[ls], val[rs]), rv[ls] + lv[rs]);
    }
    void mdypoint(int o, int l, int r, int k) {
        if(k == 1) {//check in
            val[o] = lv[o] = rv[o] = 0;
            tag[o] = 1;
        } else if(k == 2) {//check out
            val[o] = lv[o] = rv[o] = len[o];
            tag[o] = 2;
        }
    }
    void pushdown(int o, int l, int r) {
        if(tag[o]) {
            int m = (l + r) >> 1;
            mdypoint(ls, l, m, tag[o]);
            mdypoint(rs, m+1, r, tag[o]);
            tag[o] = 0;
        }
    }
    void mdyrange(int o, int l, int r, int x, int y, int k) {
        if(x <= l && r <= y) {
            mdypoint(o, l, r, k);
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if(x <= m) mdyrange(ls, l, m, x, y, k);
        if(y > m) mdyrange(rs, m+1, r, x, y, k);
        pushup(o, l, r);
    }
    int query(int o, int l, int r, int len) {
        pushdown(o, l, r);
        if(l == r) return l;
        int m = (l + r) >> 1;
        if(val[ls] >= len) return query(ls, l, m, len);
        else if(rv[ls] + lv[rs] >= len) return m - rv[ls] + 1;
        else return query(rs, m+1, r, len);
    }
    #undef ls
    #undef rs
}tr;
int n, m;

int main() {
    n = read(), m = read();
    tr.build(1, 1, n);
    while(m--) {
        int opt = read();
        if(opt == 1) {
            int d = read();
            if(tr.val[1] >= d) {
                int x = tr.query(1, 1, n, d);
                printf("%d\n", x);
                tr.mdyrange(1, 1, n, x, x + d - 1, 1);
            } else printf("0\n");
        } else {
            int x = read(), d = read();
            tr.mdyrange(1, 1, n, x, x + d - 1, 2);
        }
    }
    return 0;
}