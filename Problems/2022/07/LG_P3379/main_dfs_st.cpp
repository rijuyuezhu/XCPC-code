/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 08:44:39
 * @Description: https://www.luogu.com.cn/problem/P3379
 * @Tag: LCA，dfs序+RMQ ST
*/
#define LOCAL
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 5e5 + 5;

int n, m, s;
struct Edge {int v, nxt;}e[MAXN*2];
int head[MAXN], cnt;
void addedge(int u, int v) {
   e[++cnt] = (Edge){v, head[u]}; head[u] = cnt;
}
int dep[MAXN], fa[MAXN], st[MAXN][19], dfn[MAXN], _dfn, lg2[MAXN];
void dfs(int u, int f) {
   dep[u] = dep[f] + 1; fa[u] = f; dfn[u] = ++_dfn;
   for(int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v; if(v == f) continue;
      dfs(v, u);
   }
}
int getbt(int u, int v) {
   return dep[u] < dep[v] ? u : v;
}
void init() {
   dfs(s, 0);
   lg2[0] = -1;
   for(int i = 1; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
   for(int i = 1; i <= n; i++) st[dfn[i]][0] = i;
   for(int k = 1; k <= 18; k++)
      for(int i = 1; i + (1 << k) - 1 <= n; i++)
         st[i][k] = getbt(st[i][k-1], st[i+(1<<(k-1))][k-1]);
}
int lca(int u, int v) {
   if(u == v) return u;
   u = dfn[u], v = dfn[v];
   if(u > v) swap(u, v);
   u++;
   int k = lg2[v - u + 1];
   return fa[getbt(st[u][k], st[v - (1 << k) + 1][k])];
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
   init();
   for(int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      printf("%d\n", lca(u, v));
   }
   return 0;
}
