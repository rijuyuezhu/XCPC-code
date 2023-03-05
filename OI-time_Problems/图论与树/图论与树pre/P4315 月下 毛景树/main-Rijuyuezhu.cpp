//https://www.luogu.com.cn/problem/P4315
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
const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
struct Segtree {
    #define ls o << 1
    #define rs o << 1 | 1
    int val[MAXN << 2];
    int cha[MAXN << 2];
    int add[MAXN << 2];
    void pushup(int o) {
        val[o] = max(val[ls], val[rs]);
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

    void changep(int o, int l, int r, int k) {
        val[o] = k;
        cha[o] = k;
        add[o] = 0;
    }
    void addp(int o, int l, int r, int k) {
        val[o] += k;
        add[o] += k;
    }

    void pushdown(int o, int l, int r) {
        int m = (l + r) >> 1;
        if(cha[o]) {
            changep(ls, l, m, cha[o]);
            changep(rs, m + 1, r, cha[o]);
            cha[o] = 0;
        }
        if(add[o]) {
            addp(ls, l, m, add[o]);
            addp(rs, m + 1, r, add[o]);
            add[o] = 0;
        }
    }
    void changer(int o, int l, int r, int x, int y, int k) {
        if(x <= l && r <= y) {
            changep(o, l, r, k);
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if(x <= m) changer(ls, l, m, x, y, k);
        if(y > m) changer(rs, m + 1, r, x, y, k);
        pushup(o);
    }
    void addr(int o, int l, int r, int x, int y, int k) {
        if(x <= l && r <= y) {
            addp(o, l, r, k);
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if(x <= m) addr(ls, l, m, x, y, k);
        if(y > m) addr(rs, m + 1, r, x, y, k);
        pushup(o);
    }
    int query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[o];
        pushdown(o, l, r);
        int m = (l + r) >> 1; int ans = -INF;
        if(x <= m) ans = max(ans, query(ls, l, m, x, y));
        if(y > m) ans = max(ans, query(rs, m + 1, r, x, y));
        return ans;
    }
    #undef ls
    #undef rs
};
int n;
struct Edge {
    int v, nxt, w, num;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v, int w, int num) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].num = num;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int dep[MAXN], fa[MAXN], son[MAXN], sz[MAXN];
int w[MAXN], wl[MAXN], dfn[MAXN], tim, top[MAXN];
int per[MAXN];//per[i]存储把第i条边的边权转化为点权后点的坐标
void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u] = f;
    sz[u] = 1;
    son[u] = 0;
    int maxsz = -1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == f) continue;
        per[e[i].num] = v;
        w[v] = e[i].w; //边权转点权
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[v] > maxsz) maxsz = sz[v], son[u] = v;
    }
}
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
void changepoint(int t, int k) {//这里t是树枝编号
    int x = per[t];
    tr.changer(1, 1, n, dfn[x], dfn[x], k);
}
void changeroute(int x, int y, int k) {//这里x、y是节点
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        tr.changer(1, 1, n, dfn[top[x]], dfn[x], k);
        x = fa[top[x]];
    }
    if(x == y) return;
    if(dep[x] < dep[y]) swap(x, y);
    tr.changer(1, 1, n, dfn[y] + 1, dfn[x], k);
}
void addroute(int x, int y, int k) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        tr.addr(1, 1, n, dfn[top[x]], dfn[x], k);
        x = fa[top[x]];
    }
    if(x == y) return;
    if(dep[x] < dep[y]) swap(x, y);
    tr.addr(1, 1, n, dfn[y] + 1, dfn[x], k);
}
int queryroute(int x, int y) {
    int ans = -INF;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, tr.query(1, 1, n, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if(x == y) return ans;
    if(dep[x] < dep[y]) swap(x, y);
    ans = max(ans, tr.query(1, 1, n, dfn[y] + 1, dfn[x]));
    return ans;
}
int main() {
    n = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read(), w = read();
        addedge(u, v, w, i); addedge(v, u, w, i);
    }
    init();
    while(1) {
        char s[10];
        scanf("%s", s);
        if(s[1] == 'h') {//Change k w
            int k = read(), w = read();
            changepoint(k, w);
        } else if(s[1] == 'o') {//Cover u v w
            int u = read(), v = read(), w = read();
            changeroute(u, v, w);
        } else if(s[1] == 'd') {//Add u v w
            int u = read(), v = read(), w = read();
            addroute(u, v, w);
        } else if(s[1] == 'a') {//Max u v
            int u = read(), v = read();
            printf("%d\n", queryroute(u, v));
        } else break;
    }
    return 0;
}