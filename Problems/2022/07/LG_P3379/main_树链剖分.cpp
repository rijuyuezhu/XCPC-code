/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:32:23
 * @Description: https://www.luogu.com.cn/problem/P3379
 * @Tag: LCA，树链剖分
*/
#define LOCAL
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 5e5 + 5;
const int MAXM = 5e5 + 5;
int n, m, s;
struct Edge {int v, nxt;}e[MAXN * 2];
int head[MAXN], cnt;
void addedge(int u, int v) {
   e[++cnt] = (Edge){v, head[u]}; head[u] = cnt;
}

int sz[MAXN], son[MAXN], top[MAXN], dep[MAXN], fa[MAXN];
void dfs1(int u, int f) {
   fa[u] = f; dep[u] = dep[f] + 1; sz[u] = 1;
   for(int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v; if(v == f) continue;
      dfs1(v, u);
      sz[u] += sz[v];
      if(sz[v] > sz[son[u]]) son[u] = v;
   }
}
void dfs2(int u, int tprt) {
   top[u] = tprt; if(son[u]) dfs2(son[u], tprt);
   for(int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v; if(v == fa[u] || v == son[u]) continue;
      dfs2(v, v);
   }
}
int lca(int u, int v) {
   while(top[u] != top[v]) {
      if(dep[top[u]] < dep[top[v]]) swap(u, v);
      u = fa[top[u]];
   }
   return dep[u] < dep[v] ? u : v;
}
int main() {
   #ifdef LOCAL
   freopen("main.in", "r", stdin);
   #endif
   scanf("%d%d%d", &n, &m, &s);
   for(int i = 1; i < n; i++) {
      int u, v; scanf("%d%d", &u, &v);
      addedge(u, v); addedge(v, u);
   }
   dfs1(s, 0);
   dfs2(s, s);
   for(int i = 1; i <= m; i++) {
      int u, v; scanf("%d%d", &u, &v);
      printf("%d\n", lca(u, v));
   }
   return 0;
}