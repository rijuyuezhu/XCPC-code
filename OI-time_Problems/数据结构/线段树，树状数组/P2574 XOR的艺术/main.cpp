// https://www.luogu.com.cn/problem/P2574
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
const int MAXN = 2e5 + 5;
struct Segment_tree {
    #define ls o << 1
    #define rs o << 1 | 1
    int val[MAXN << 2], tag[MAXN << 2];
    void pushup(int o) {
        val[o] = val[ls] + val[rs];
    }
    void build(int o, int l, int r, char s[]) {
        tag[o] = 0;
        if(l == r) {
            val[o] = s[l] - '0';
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, s);
        build(rs, m+1, r, s);
        pushup(o);
    }
    void mdypoint(int o, int l, int r) {
        tag[o] ^= 1;
        val[o] = (r - l + 1) - val[o];
    }
    void pushdown(int o, int l, int r) {
        if(tag[o]) {
            int m = (l + r) >> 1;
            mdypoint(ls, l, m); mdypoint(rs, m+1, r);
            tag[o] = 0;
        }
    }
    void mdyrange(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            mdypoint(o, l, r);
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if(x <= m) mdyrange(ls, l, m, x, y);
        if(y > m) mdyrange(rs, m+1, r, x, y);
        pushup(o);
    }
    int query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        pushdown(o, l, r);
        int m = (l + r) >> 1, ans = 0;
        if(x <= m) ans += query(ls, l, m, x, y);
        if(y > m) ans += query(rs, m+1, r, x, y);
        return ans;
    }
    #undef ls
    #undef rs
}tr;
int n, m;
char s[MAXN];
int main() {
    n = read(), m = read();
    scanf("%s", s+1);
    tr.build(1, 1, n, s);
    for(int i = 1; i <= m; i++) {
        int op = read(), x = read(), y = read();
        if(op == 0) tr.mdyrange(1, 1, n, x, y);
        else printf("%d\n", tr.query(1, 1, n, x, y));
    }    
    return 0;
}