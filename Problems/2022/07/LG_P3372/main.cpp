/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-28 07:43:28
 * @Description: https://www.luogu.com.cn/problem/P3372
 * @Tag: 线段树，序列操作，数据结构
*/
#include<cstdio>
typedef long long ll;
const int MAXN = 1e5 + 5;
int n, m;
ll a[MAXN];
namespace Sgt {
   #define ls o << 1
   #define rs o << 1 | 1
   ll val[MAXN << 2], tag[MAXN << 2];
   void pushup(int o) {
      val[o] = val[ls] + val[rs];
   }
   void build(int o, int l, int r, ll a[]) {
      if(l == r) {
         val[o] = a[l]; tag[o] = 0;
         return ;
      }
      int m = (l + r) >> 1;
      build(ls, l, m, a);
      build(rs, m+1, r, a);
      pushup(o);
   }
   void addpoint(int o, int l, int r, ll v) {
      val[o] += (r-l+1) * v; tag[o] += v;
   }
   void pushdown(int o, int l, int r) {
      if(tag[o]) {
         int m = (l + r) >> 1;
         addpoint(ls, l, m, tag[o]);
         addpoint(rs, m+1, r, tag[o]);
         tag[o] = 0;
      }
   }
   void addrange(int o, int l, int r, int x, int y, ll v) {
      if(x <= l && r <= y) {
         addpoint(o, l, r, v);
         return ;
      }
      pushdown(o, l, r);
      int m = (l + r) >> 1;
      if(x <= m) addrange(ls, l, m, x, y, v);
      if(y > m) addrange(rs, m+1, r, x, y, v);
      pushup(o);
   }
   ll sumrange(int o, int l, int r, int x, int y) {
      if(x <= l && r <= y) return val[o];
      pushdown(o, l, r);
      int m = (l + r) >> 1;
      if(y <= m) return sumrange(ls, l, m, x, y);
      else if(x > m) return sumrange(rs, m+1, r, x, y);
      else return sumrange(ls, l, m, x, m) + sumrange(rs, m+1, r, m+1, y);
   }
   #undef ls
   #undef rs
}
int main() {
   #ifdef LOCAL
   freopen("main.in", "r", stdin);
   #endif
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
   Sgt::build(1, 1, n, a);
   for(int i = 1; i <= m; i++) {
      int opt, x, y;
      scanf("%d%d%d", &opt, &x, &y);
      if(opt == 1) {
         ll v; scanf("%lld", &v);
         Sgt::addrange(1, 1, n, x, y, v);
      } else {
         printf("%lld\n", Sgt::sumrange(1, 1, n, x, y));
      }
   }
   return 0;
}