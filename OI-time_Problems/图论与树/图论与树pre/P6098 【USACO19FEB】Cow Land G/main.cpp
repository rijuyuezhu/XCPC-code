//https://www.luogu.com.cn/problem/P6098
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
//graph
int n, q;
struct Edge {
   int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt;
void addedge(int u, int v) {
   e[++cnt].v = v;
   e[cnt].nxt = head[u];
   head[u] = cnt;
   return;
}
int w[MAXN];
//---
//segment tree
struct Segtree {
   #define ls (o<<1)
   #define rs (o<<1|1)
   int val[MAXN << 2];
   void pushup(int o) {
      val[o] = val[ls] ^ val[rs];
      return;
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
      return;
   }
   void mdypoint(int o, int l, int r, int x, int k) {
      if(l == r) {
         val[o] = k;
         return;
      }
      int m = (l + r) >> 1;
      if(x <= m) mdypoint(ls, l, m, x, k);
      else mdypoint(rs, m+1, r, x, k);
      pushup(o);
      return;
   }
   int qryrange(int o, int l, int r, int x, int y) {
      if(x <= l && r <= y) return val[o];
      int m = (l + r) >> 1, ans = 0;
      if(x <= m) ans ^= qryrange(ls, l, m, x, y);
      if(y > m) ans ^= qryrange(rs, m+1, r, x, y);
      return ans;
   }
   #undef ls
   #undef rs
};

//---
//treecut
namespace Treecut {
   int dep[MAXN];
   int fa[MAXN];
   int son[MAXN];
   int sz[MAXN];
   void dfs1(int u, int f) {
      dep[u] = dep[f] + 1;
      fa[u] = f;
      son[u] = 0;
      sz[u] = 1;
      int maxsz = -1;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v;
         if(v == f) continue;
         dfs1(v, u);
         sz[u] += sz[v];
         if(sz[v] > maxsz) maxsz = sz[v], son[u] = v;
      }
      return;
   }
   int dfn[MAXN], tim;
   int wl[MAXN];
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
      return;
   }
   Segtree tr;
   void init() {
      dfs1(1, 0);
      dfs2(1, 1);
      tr.build(1, 1, n, wl);
      return;
   }
   void mdynode(int x, int k) {
      tr.mdypoint(1, 1, n, dfn[x], k);
      return;
   }
   int qryroute(int x, int y) {
      int ans = 0;
      while(top[x] != top[y]) {
         if(dep[top[x]] < dep[top[y]]) swap(x, y);
         ans ^= tr.qryrange(1, 1, n, dfn[top[x]], dfn[x]);
         x = fa[top[x]];
      }
      if(dep[x] < dep[y]) swap(x, y);
      ans ^= tr.qryrange(1, 1, n, dfn[y], dfn[x]);
      return ans;
   }
}
//---


int main() {
    n = read(), q = read();
    for(int i = 1; i <= n; i++) w[i] = read();
    for(int i = 1; i < n; i++) {
       int a = read(), b = read();
       addedge(a, b); addedge(b, a);
    }
    Treecut::init();
    while(q--) {
       int opt = read();
       if(opt == 1) {
          int u = read(), k = read();
          Treecut::mdynode(u, k);
       } else {
          int u = read(), v = read();
          printf("%d\n", Treecut::qryroute(u, v));
       }
    }
    return 0;
}