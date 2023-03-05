//https://www.luogu.com.cn/problem/P3979
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
const ll INF = 0x3f3f3f3f3f3f3f3fll;
//Graph
int n, m;
struct Edge {
   int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
ll w[MAXN];
void addedge(int u, int v) {
   e[++cnt].v = v;
   e[cnt].nxt = head[u];
   head[u] = cnt;
}
int nowrt, rt;
//------
//Segment tree
struct Segtree {
   #define ls (o<<1)
   #define rs (o<<1|1)
   ll val[MAXN << 2], sg[MAXN << 2];
   void pushup(int o) {
      val[o] = min(val[ls], val[rs]);
   }
   void build(int o, int l, int r, ll a[]) {
      sg[o] = -1;//-1表示不用修改
      if(l == r) {
         val[o] = a[l];
         return;
      }
      int m = (l + r) >> 1;
      build(ls, l, m, a);
      build(rs, m+1, r, a);
      pushup(o);
   }
   void mdypoint(int o, ll k) {
      val[o] = k;
      sg[o] = k;
   }
   void pushdown(int o) {
      if(sg[o] != -1) {
         mdypoint(ls, sg[o]);
         mdypoint(rs, sg[o]);
         sg[o] = -1;
      }
   }
   void mdyrange(int o, int l, int r, int x, int y, ll k) {
      if(x <= l && r <= y) {
         mdypoint(o, k);
         return;
      }
      pushdown(o);
      int m = (l + r) >> 1;
      if(x <= m) mdyrange(ls, l, m, x, y, k);
      if(y > m) mdyrange(rs, m+1, r, x, y, k);
      pushup(o);
   }
   ll qryrange(int o, int l, int r, int x, int y) {
      if(x <= l && r <= y) return val[o];
      pushdown(o);
      int m = (l + r) >> 1; ll ans = INF;
      if(x <= m) ans = min(ans, qryrange(ls, l, m, x, y));
      if(y > m) ans = min(ans, qryrange(rs, m+1, r, x, y));
      return ans;
   }
   #undef ls
   #undef rs
};
//-------
//Tree cut
namespace Treecut {
   int dep[MAXN], fa[MAXN], sz[MAXN], son[MAXN];
   void dfs1(int u, int f) {
      dep[u] = dep[f] + 1; fa[u] = f; sz[u] = 1; son[u] = 0;
      int maxsz = -1;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v;
         if(v == f) continue;
         dfs1(v, u);
         sz[u] += sz[v];
         if(sz[v] > maxsz) maxsz = sz[v], son[u] = v;
      }
   }
   ll wl[MAXN];
   int top[MAXN], dfn[MAXN], tim;
   void dfs2(int u, int tprt) {
      dfn[u] = ++tim;
      top[u] = tprt;
      wl[tim] = w[u];
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
   void mdyroute(int u, int v, ll k) {
      while(top[u] != top[v]) {
         if(dep[top[u]] < dep[top[v]]) swap(u, v);
         tr.mdyrange(1, 1, n, dfn[top[u]], dfn[u], k);
         u = fa[top[u]];
      }
      if(dep[u] < dep[v]) swap(u, v);
      tr.mdyrange(1, 1, n, dfn[v], dfn[u], k);
   }
   int lca(int u, int v) {
      while(top[u] != top[v]) {
         if(dep[top[u]] < dep[top[v]]) swap(u, v);
         u = fa[top[u]];
      }
      return dep[u] > dep[v] ? v : u;
   }
   int find(int v, int u) {   //找到u的一个儿子，并且满足v在这个儿子的子树里（已经满足v在u子树中）
      while(top[v] != top[u]) {
         if(fa[top[v]] == u) return top[v];//v所在重链的顶端正好是u的一个轻儿子，那么直接返回这个顶端
         v = fa[top[v]];
      }
      return son[u];//当两者在同一重链上，满足条件的便是u的重儿子
   }
   ll query(int u) {
      if(u == nowrt) return tr.val[1];//当询问点与当前根相同，那么返回整个子树
      if(dfn[nowrt] < dfn[u] || dfn[nowrt] > dfn[u] + sz[u] - 1) return tr.qryrange(1, 1, n, dfn[u], dfn[u] + sz[u] - 1);
      //当前根不在询问点的子树中，那么直接就是原树的u子树
      int t = find(nowrt, u);
      ll ans = INF;
      if(dfn[t] > 1) ans = min(ans, tr.qryrange(1, 1, n, 1, dfn[t] - 1));
      if(dfn[t] < n) ans = min(ans, tr.qryrange(1, 1, n, dfn[t] + sz[t], n));
      return ans;
      //排除掉以t为根的子树
   }
}
//-------
int main() {
   n = read(), m = read();
   for(int i = 1; i < n; i++) {
   int u = read(), v = read();
      addedge(u, v); addedge(v, u);
   }
   for(int i = 1; i <= n; i++) w[i] = read();
   nowrt = rt = read();
   Treecut::init();
   for(int i = 1; i <= m; i++) {
      int opt = read();
      if(opt == 1) nowrt = read();
      else if(opt == 2) {
         int x = read(), y = read(); ll k = read();
         Treecut::mdyroute(x, y, k);
      } else {
         int u = read();
         printf("%lld\n", Treecut::query(u));
      }
   }
   return 0;
}