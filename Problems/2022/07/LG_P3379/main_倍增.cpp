/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 08:26:43
 * @Description: https://www.luogu.com.cn/problem/P3379
 * @Tag: LCA，倍增
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

int upto[MAXN][19], dep[MAXN];
void dfs(int u, int f) {
   upto[u][0] = f; dep[u] = dep[f] + 1;
   for(int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].v; if(v == f) continue;
      dfs(v, u);
   }
}
void init() {
   dfs(s, 0);
   for(int i = 1; i <= 18; i++)
      for(int u = 1; u <= n; u++)
         upto[u][i] = upto[upto[u][i-1]][i-1];
}
int lca(int u, int v) {
   if(dep[u] < dep[v]) swap(u, v);
   for(int i = 18; i >= 0; i--)
      if(dep[upto[u][i]] >= dep[v]) u = upto[u][i];
   if(u == v) return u;
   for(int i = 18; i >= 0; i--)
      if(upto[u][i] != upto[v][i])
         u = upto[u][i], v = upto[v][i];
   return upto[u][0];
}
int main() {
   #ifdef LOCAL
   freopen("main.in", "r", stdin);
   #endif
   scanf("%d%d%d", &n, &m, &s);
   for(int i = 1; i < n; i++) {
      int x, y; scanf("%d%d", &x, &y);
      addedge(x, y); addedge(y, x);
   }
   init();
   for(int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      printf("%d\n", lca(u, v));
   }
   return 0;
}