//这题是树剖.jpg
#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 100005;

int n, q;
struct Edge {
    int v, nxt;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int dep[MAXN], sz[MAXN];
int dfn[MAXN], tim;

int mymin(int u, int v) {
    return dep[u] > dep[v] ? u : v;
}
struct Segtree {
    #define ls o << 1
    #define rs o << 1 | 1
    int val[MAXN << 2];
    int lz[MAXN << 2];
    void build(int o, int l, int r) {
        if(l == r) {
            val[o] = 1;
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m);
        build(rs, m + 1, r);
    }
    void changep(int o, int l, int r, int k) {
        lz[o] = mymin(lz[o], k);
        if(l == r) val[o] = mymin(val[o], k);
    }
    void pushdown(int o, int l, int r) {
        if(lz[o]) {
            int m = (l + r) >> 1;
            changep(ls, l, m, lz[o]);
            changep(rs, m + 1, r, lz[o]);
            lz[o] = 0;
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
    }
    int queryp(int o, int l, int r, int x) {
        if(l == r) return val[o];
        pushdown(o, l, r);
        int m = (l + r) >> 1;
        if(x <= m) return queryp(ls, l, m, x);
        else return queryp(rs, m + 1, r, x);
    }
    #undef ls
    #undef rs
};
void dfs1(int u, int f) {
    dfn[u] = ++tim;
    dep[u] = dep[f] + 1;
    sz[u] = 1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        dfs1(v, u);
        sz[u] += sz[v];
    }
}
Segtree tr;
void init() {
    dfs1(1, 0);
    tr.build(1, 1, n);
}
int main() {
    n = read(); q = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        addedge(u, v);
    }
    init();
    while(q--) {
        char op[5];
        scanf("%s", op);
        if(op[0] == 'C') {
            int x = read();
            tr.changer(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, x);
        } else {
            int x = read();
            printf("%d\n", tr.queryp(1, 1, n, dfn[x]));
        }
    }
    return 0;
}