//https://www.luogu.com.cn/problem/P3379
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
const int MAXN = 500005;
int n, m, s;
struct Edge {
    int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int dep[MAXN];
int sz[MAXN];
int fa[MAXN];
int son[MAXN];
void dfs1(int u, int f) {
    fa[u] = f;
    sz[u] = 1;
    dep[u] = dep[f] + 1;
    int maxsz = -1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == f) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(maxsz < sz[v]) maxsz = sz[v], son[u] = v;
    }
}
int top[MAXN];
void dfs2(int u, int tprt) {
    top[u] = tprt;
    if(!son[u]) return;
    dfs2(son[u], tprt);
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
int lca(int x, int y) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}

int main() {
    n = read(), m = read(), s = read();
    for(int i = 1; i < n; i++) {
        int u = read(), v = read();
        addedge(u, v); addedge(v, u);
    }
    dfs1(s, 0);
    dfs2(s, s);
    for(int i = 1; i <= m; i++) {
        int a = read(), b = read();
        printf("%d\n", lca(a, b));
    }
    return 0;
}