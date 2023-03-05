//https://www.luogu.com.cn/problem/P3038
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
//Graph
int n, m;
struct Edge {
   int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
   e[++cnt].v = v;
   e[cnt].nxt = head[u];
   head[u] = cnt;
}
//------
//Segment tree
struct Segtree {
   #define ls (o<<1)
   #define rs (o<<1|1)
   int val[MAXN << 2], la[MAXN << 2];
   void pushup(int o) {
      val[o] = val[ls] + val[rs];
   }
   void addpoint(int o, int l, int r, int k) {
      val[o] += (r - l + 1) * k;
      la[o] += k;
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
   int qrypoint(int o, int l, int r, int x) {
      if(l == r) return val[o];
      int m = (l + r) >> 1;
      pushdown(o, l, r);
      if(x <= m) return qrypoint(ls, l, m, x);
      else return qrypoint(rs, m+1, r, x);
   }
   #undef ls
   #undef rs
};
//------
//Tree cut
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
   int dfn[MAXN], tim;
   int top[MAXN];
   void dfs2(int u, int tprt) {
      dfn[u] = ++tim;
      top[u] = tprt;
      if(!son[u]) return;
      dfs2(son[u], tprt);
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v;
         if(v == son[u] || v == fa[u]) continue;
         dfs2(v, v);
      }
   }
   Segtree tr;
   void init() {
      dfs1(1, 0);
      dfs2(1, 1);
   }
   void addroute(int u, int v) {
      while(top[u] != top[v]) {
         if(dep[top[u]] < dep[top[v]]) swap(u, v);
         tr.addrange(1, 1, n, dfn[top[u]], dfn[u], 1);
         u = fa[top[u]];
      }
      if(u == v) return;
      if(dep[u] < dep[v]) swap(u, v);
      tr.addrange(1, 1, n, dfn[v] + 1, dfn[u], 1);
   }
   int query(int u, int v) {
      if(dep[u] > dep[v]) return tr.qrypoint(1, 1, n, dfn[u]);
      else return tr.qrypoint(1, 1, n, dfn[v]);
   }
}
//------
int main() {
   n = read(), m = read();
   for(int i = 1; i < n; i++) {
      int u = read(), v = read();
      addedge(u, v); addedge(v, u);
   }
   Treecut::init();
   for(int i = 1; i <= m; i++) {
      char s[10];
      int x, y;
      scanf("%s", s);
      x = read(), y = read();
      if(s[0] == 'P') {
         Treecut::addroute(x, y);
      } else {
         printf("%d\n", Treecut::query(x, y));
      }
   }
   return 0;
}