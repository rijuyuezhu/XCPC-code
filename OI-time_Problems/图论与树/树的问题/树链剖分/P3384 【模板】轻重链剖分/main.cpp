//https://www.luogu.com.cn/problem/P3384
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
const int MAXN = 1e5 + 5;

//mode
int p;
int pls(int a, int b) {return a + b < p ? a + b : a + b - p;}
int mns(int a, int b) {return a < b ? a - b + p : a - b;}
int mul(int a, int b) {return 1ll * a * b % p;}
//---
//segment tree
struct Segtree {
    #define ls (o<<1)
    #define rs (o<<1|1)
    int val[MAXN << 2], la[MAXN << 2];
    void pushup(int o) {
        val[o] = pls(val[ls], val[rs]);
    }
    void build(int o, int l, int r, int a[]) {
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
        val[o] = pls(val[o], mul(k, r - l + 1));
        la[o] = pls(la[o], k);
    }
    void pushdown(int o, int l, int r) {
        if(la[o]) {
            int m = (l + r) >> 1;
            addpoint(ls, l, m, la[o]);
            addpoint(rs, m+1, r, la[o]);
            la[o] = 0;
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
    int qryrange(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        pushdown(o, l, r);
        int m = (l + r) >> 1, ans = 0;
        if(x <= m) ans = pls(ans, qryrange(ls, l, m, x, y));
        if(y > m) ans = pls(ans, qryrange(rs, m+1, r, x, y));
        return ans;
    }
    #undef ls
    #undef rs
};
//---edge
int n, m, rt;
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int w[MAXN];
//---
//---树链剖分
namespace Treecut {

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

    int wl[MAXN];
    int dfn[MAXN], tim;
    int top[MAXN];
    
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
        dfs1(rt, 0);
        dfs2(rt, rt);
        tr.build(1, 1, n, wl);
    }
    
    void addroute(int x, int y, int k) {
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) swap(x, y); 
            tr.addrange(1, 1, n, dfn[top[x]], dfn[x], k);
            x = fa[top[x]];
        }
        if(dep[x] < dep[y]) swap(x, y);
        tr.addrange(1, 1, n, dfn[y], dfn[x], k);
    }

    int qryroute(int x, int y) {
        int ans = 0;
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) swap(x, y);
            ans = pls(ans, tr.qryrange(1, 1, n, dfn[top[x]], dfn[x]));
            x = fa[top[x]];
        }
        if(dep[x] < dep[y]) swap(x, y);
        ans = pls(ans, tr.qryrange(1, 1, n, dfn[y], dfn[x]));
        return ans;
    }

    void addsubtree(int x, int k) {
        tr.addrange(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, k);
    }

    int qrysubtree(int x) {
        return tr.qryrange(1, 1, n, dfn[x], dfn[x] + sz[x] - 1);
    }

}
//---

int main() {
    n = read(); m = read(); rt = read(); p = read();
    for(int i = 1; i <= n; i++) w[i] = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        addedge(u, v); addedge(v, u);
    }
    Treecut::init();
    for(int i = 1; i <= m; i++) {
        int opt = read();
        if(opt == 1) {
            int x = read(), y = read(), z = read();
            Treecut::addroute(x, y, z);
        } else if(opt == 2) {
            int x = read(), y = read();
            printf("%d\n", Treecut::qryroute(x, y));
        } else if(opt == 3) {
            int x = read(), z = read();
            Treecut::addsubtree(x, z);
        } else {
            int x = read();
            printf("%d\n", Treecut::qrysubtree(x));
        }
    }
    return 0;
}