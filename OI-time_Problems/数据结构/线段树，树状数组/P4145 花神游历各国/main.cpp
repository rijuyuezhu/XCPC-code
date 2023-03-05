// https://www.luogu.com.cn/problem/P4145
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 100005;
struct Segment_tree {
    #define ls o << 1
    #define rs o << 1 | 1
    ll val[MAXN << 2];
    int br[MAXN << 2];
    void pushup(int o) {
        val[o] = val[ls] + val[rs];
        br[o] = br[ls] && br[rs];
    }
    void build(int o, int l, int r, ll a[]) {
        br[o] = 0;
        if(l == r) {
            val[o] = a[l];
            if(val[o] == 1 || val[o] == 0) br[o] = 1;
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, a);
        build(rs, m+1, r, a);
        pushup(o);
    }
    void mdyrange(int o, int l, int r, int x, int y) {
        if(br[o]) return;
        if(l == r) {
            val[o] = sqrt(val[o]);
            if(val[o] == 1 || val[o] == 0) br[o] = 1;
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) mdyrange(ls, l, m, x, y);
        if(y > m) mdyrange(rs, m+1, r, x, y);
        pushup(o);
    }
    ll query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        int m = (l + r) >> 1; ll ans = 0;
        if(x <= m) ans += query(ls, l, m, x, y);
        if(y > m) ans += query(rs, m+1, r, x, y);
        return ans;
    }
    #undef ls
    #undef rs
}tr;
int n, m;
ll a[MAXN];
int main() {
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    tr.build(1, 1, n, a);
    m = read();
    while(m--) {
        int opt = read(), l = read(), r = read();
        if(l > r) swap(l, r);
        if(opt == 0) {
            tr.mdyrange(1, 1, n, l, r);
        } else {
            printf("%lld\n", tr.query(1, 1, n, l, r));
        }
    }
    return 0;
}