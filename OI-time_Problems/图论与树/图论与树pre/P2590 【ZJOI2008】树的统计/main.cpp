//https://www.luogu.com.cn/problem/P2590
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
//Graph
const int MAXN = 3e4 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, q;
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
ll w[MAXN];
//-----
//Segment tree
struct Segtree {
    #define ls (o<<1)
    #define rs (o<<1|1)
    ll val[MAXN << 2]; ll maxv[MAXN << 2];
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
        build(ls, l, m, a);
        build(rs, m+1, r, a);
        pushup(o);
    }
    void changepoint(int o, int l, int r, int x, ll k) {
        if(l == r) {
            val[o] = maxv[o] = k;
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) changepoint(ls, l, m, x, k);
        else changepoint(rs, m+1, r, x, k);
        pushup(o);
    }
    ll qryrangesum(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        int m = (l + r) >> 1; ll ans = 0;
        if(x <= m) ans += qryrangesum(ls, l, m, x, y);
        if(y > m) ans += qryrangesum(rs, m+1, r, x, y);
        return ans;
    }
    ll qryrangemax(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return maxv[o];
        int m = (l + r) >> 1; ll ans = -INF;
        if(x <= m) ans = max(ans, qryrangemax(ls, l, m, x, y));
        if(y > m) ans = max(ans, qryrangemax(rs, m+1, r, x, y));
        return ans;
    }
    #undef ls
    #undef rs  
};
//-----
//Link cut
namespace Linkcut {
    int dep[MAXN];
    int fa[MAXN];
    int sz[MAXN];
    int son[MAXN];
    void dfs1(int u, int f) {
        dep[u] = dep[f] + 1;
        fa[u] = f;
        sz[u] = 1;
        son[u] = 0;
        int maxsz = -1;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(v == f) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if(sz[v] > maxsz) maxsz = sz[v], son[u] = v;
        }
    }
    int dfn[MAXN], tim;
    int top[MAXN];
    ll wl[MAXN];
    void dfs2(int u, int tprt) {
        dfn[u] = ++tim;
        wl[tim] = w[u];
        top[u] = tprt;
        if(!son[u]) return;
        dfs2(son[u], tprt);
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }
    Segtree tr;
    void init() {
        dfs1(1, 0);
        dfs2(1, 1);
        tr.build(1, 1, n, wl);        
    }
    void change(int u, int k) {
        tr.changepoint(1, 1, n, dfn[u], k);
    }
    ll qmax(int u, int v) {
        ll ans = -INF;
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            ans = max(ans, tr.qryrangemax(1, 1, n, dfn[top[u]], dfn[u]));
            u = fa[top[u]];
        }
        if(dep[u] < dep[v]) swap(u, v);
        ans = max(ans, tr.qryrangemax(1, 1, n, dfn[v], dfn[u]));
        return ans;
    }
    ll qsum(int u, int v) {
        ll ans = 0;
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            ans += tr.qryrangesum(1, 1, n, dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }
        if(dep[u] < dep[v]) swap(u, v);
        ans += tr.qryrangesum(1, 1, n, dfn[v], dfn[u]);
        return ans;
    }
}
//------

char s[100];
int main() {
    n = read();
    for(int i = 1; i < n; i++) {
        int a = read(), b = read();
        addedge(a, b); addedge(b, a);
    }
    for(int i = 1; i <= n; i++) w[i] = read();
    Linkcut::init();
    q = read();
    for(int i = 1; i <= q; i++) {
        scanf("%s", s);
        if(s[1] == 'H') {
            int u = read(), t = read();
            Linkcut::change(u, t);
        } else if(s[1] == 'M') {
            int u = read(), v = read();
            printf("%lld\n", Linkcut::qmax(u, v));
        } else {
            int u = read(), v = read();
            printf("%lld\n", Linkcut::qsum(u, v));
        }
    }
    return 0;
}