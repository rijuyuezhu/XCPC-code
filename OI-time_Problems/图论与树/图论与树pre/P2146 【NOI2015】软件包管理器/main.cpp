//https://www.luogu.com.cn/problem/P2146
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
int n, q;
//Graph
struct Edge {
   int v, nxt;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {
   e[++cnt].v = v;
   e[cnt].nxt = head[u];
   head[u] = cnt;
}
int fa[MAXN];
//------
//Segment tree
struct Segtree {
   #define ls (o<<1)
   #define rs (o<<1|1)
   int val[MAXN << 2];//区间中装了的个数
   int la[MAXN << 2];//0不改，1全改为0（即未安装），2全改为1（即已安装）
   void pushup(int o) {
      val[o] = val[ls] + val[rs];
   }
   void mdypoint(int o, int l, int r, int k) {
      val[o] = (r - l + 1) * (k - 1);
      la[o] = k;
   }
   void pushdown(int o, int l, int r) {
      if(la[o] != 0) {
         int m = (l + r) >> 1;
         mdypoint(ls, l, m, la[o]);
         mdypoint(rs, m+1, r, la[o]);
         la[o] = 0;
      }
   }
   void mdyrange(int o, int l, int r, int x, int y, int k) {
      if(x <= l && r <= y) {
         mdypoint(o, l, r, k);
         return;
      }
      pushdown(o, l, r);
      int m = (l + r) >> 1;
      if(x <= m) mdyrange(ls, l, m, x, y, k);
      if(y > m) mdyrange(rs, m+1, r, x, y, k);
      pushup(o);
   }
   int qryrange(int o, int l, int r, int x, int y) {
      if(x <= l && r <= y) return val[o];
      pushdown(o, l, r);
      int m = (l + r) >> 1, ans = 0;
      if(x <= m) ans += qryrange(ls, l, m, x, y);
      if(y > m) ans += qryrange(rs, m+1, r, x, y);
      return ans;
   }
   #undef ls
   #undef rs
};
//------
//Treecut
namespace Treecut {
   int dep[MAXN], son[MAXN], sz[MAXN];
   void dfs1(int u) {
      dep[u] = dep[fa[u]] + 1;
      sz[u] = 1;
      son[u] = 0;
      int maxsz = -1;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v;
         dfs1(v);
         sz[u] += sz[v];
         if(sz[v] > maxsz) maxsz = sz[v], son[u] = v;
      }
   }
   int dfn[MAXN], tim, top[MAXN];
   void dfs2(int u, int tprt) {
      dfn[u] = ++tim;
      top[u] = tprt;
      if(!son[u]) return;
      dfs2(son[u], tprt);
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v;
         if(v == son[u]) continue;
         dfs2(v, v);
      }
   }
   Segtree tr;
   void init() {
      dfs1(1);
      dfs2(1, 1);
   }
   int qryroute(int u, int v = 1) {//返回从u到根有多少个未安装的包
      int ans = 0;
      while(top[u] != top[v]) {
         if(dep[top[u]] < dep[top[v]]) swap(u, v);
         ans += (dfn[u] - dfn[top[u]] + 1) - tr.qryrange(1, 1, n, dfn[top[u]], dfn[u]);
         u = fa[top[u]];
      }
      if(dep[u] < dep[v]) swap(u, v);
      ans += (dfn[u] - dfn[v] + 1) - tr.qryrange(1, 1, n, dfn[v], dfn[u]);
      return ans;
   }
   void mdyroute(int u, int v = 1) {
      while(top[u] != top[v]) {
         if(dep[top[u]] < dep[top[v]]) swap(u, v);
         tr.mdyrange(1, 1, n, dfn[top[u]], dfn[u], 2);
         u = fa[top[u]];
      }
      if(dep[u] < dep[v]) swap(u, v);
      tr.mdyrange(1, 1, n, dfn[v], dfn[u], 2);
   }
   int qrysbt(int u) {
      return tr.qryrange(1, 1, n, dfn[u], dfn[u] + sz[u] - 1);
   }
   void mdysbt(int u) {
      tr.mdyrange(1, 1, n, dfn[u], dfn[u] + sz[u] - 1, 1);
   }
}
//------
int main() {
   //所有编号+1
    n = read();
    for(int i = 2; i <= n; i++) {
       int f = read() + 1;
       addedge(f, i);
       fa[i] = f;
    }
    Treecut::init();
    int q = read();
    while(q--) {
       char s[15];
       scanf("%s", s);
       int x = read() + 1;
       if(s[0] == 'i') {
          printf("%d\n", Treecut::qryroute(x));
          Treecut::mdyroute(x);
       } else {
          printf("%d\n", Treecut::qrysbt(x));
          Treecut::mdysbt(x);
       }
    }
    return 0;
}