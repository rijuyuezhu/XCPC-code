//http://poj.org/problem?id=3694
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
#define CLA(A, t) memset(A, t, sizeof(A))
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
int n, m;
struct Graph {
   struct Edge {
       int v, nxt;
   }e[MAXM << 1];
   int head[MAXN], cnt;
   void addedge(int u, int v) {
       e[++cnt].v = v;
       e[cnt].nxt = head[u];
       head[u] = cnt;
   }
   void clear() {
       CLA(head, 0x00);
       cnt = 1;
   }
}g1, g2;
int dfn[MAXN], low[MAXN], tim;
bool bridge[MAXM << 1];
void tarjan(int u, int in_e) {
    dfn[u] = low[u] = ++tim;
    for(int i = g1.head[u]; i; i = g1.e[i].nxt) {
        int v = g1.e[i].v;
        if(!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) bridge[i] = bridge[i ^ 1] = 1;
        } else if(i != (in_e ^ 1)) low[u] = min(low[u], dfn[v]);
    }
}
//---
int bel[MAXN], gg;
void dfs(int u) {
    bel[u] = gg;
    for(int i = g1.head[u]; i; i = g1.e[i].nxt) {
        int v = g1.e[i].v;
        if(bel[v] || bridge[i]) continue;
        dfs(v);
    }
}
//---
int upto[MAXN];
int getup(int u) {
    if(u == upto[u]) return u;
    return upto[u] = getup(upto[u]);
}
//---
int dep[MAXN], fa[MAXN][21];
void dfs2(int u) {
    for(int i = g2.head[u]; i; i = g2.e[i].nxt) {
        int v = g2.e[i].v;
        if(v == fa[u][0]) continue;
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        dfs2(v);
    }
}
int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20; i >= 0; i--)
        if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if(u == v) return u;
    for(int i = 20; i >= 0; i--)
        if(fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
//---
ll ans;
void work(int u, int top) {
    while(1) {
        u = getup(u);
        if(dep[fa[u][0]] >= dep[top]) {
            ans--;
            upto[u] = fa[u][0];
        } else break;
    }
}
void solve() {
    g1.clear(); g2.clear();
    CLA(dfn, 0x00); CLA(low, 0x00); tim = 0;
    CLA(bridge, 0x00);
    CLA(bel, 0x00); gg = 0;
    CLA(dep, 0x00); CLA(fa, 0x00); 
    ans = 0;
    //-----
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        g1.addedge(u, v); g1.addedge(v, u);
    } 
    
    tarjan(1, 0);
    for(int i = 2; i <= g1.cnt; i += 2)
        if(bridge[i]) ans++;
       /* for(int i = 2; i <= g1.cnt; i += 2)
        if(bridge[i]) printf("%d->%d\n", g1.e[i^1].v, g1.e[i].v);*/
    for(int i = 1; i <= n; i++)
        if(!bel[i]) gg++, dfs(i);
    for(int u = 1; u <= n; u++)
        for(int i = g1.head[u]; i; i = g1.e[i].nxt) {
            int v = g1.e[i].v;
            if(bel[u] != bel[v]) g2.addedge(bel[u], bel[v]);
        }
    dep[1] = 1;
    dfs2(1);
    for(int i = 1; i <= 20; i++)
        for(int u = 1; u <= gg; u++)
            fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int i = 1; i <= gg; i++) upto[i] = i;
    int Q = read();
    while(Q--) {
        int u = read(), v = read();
        if(bel[u] != bel[v]) {
            u = bel[u], v = bel[v];
            int l = lca(u, v);
            work(u, l);
            work(v, l);
        }
        printf("%d\n", ans);
    }
}

int main() {
    int T = 0;
    while(1) {
        n = read(), m = read();
        if(n == 0 && m == 0) return 0;
        printf("Case %d:\n", ++T);
        solve();
        printf("\n");
    }
    return 0;
}