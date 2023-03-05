/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:27:56
 * @Description: https://www.luogu.com.cn/problem/P3374
 * @Tag: 树状数组
*/

#include<cstdio>

const int MAXN = 5e5 + 5;
int n, m, a[MAXN], s[MAXN];
namespace BIT {
   int t[MAXN];
   int lb(int x) {return x & -x;}
   void build() {
      for(int i = 1; i <= n; i++) t[i] = s[i] - s[i - lb(i)];
   }
   void add(int x, int v) {
      for(int i = x; i <= n; i += lb(i)) t[i] += v;
   }
   int sum(int x) {
      int s = 0;
      for(int i = x; i; i -= lb(i)) s += t[i];
      return s;
   }
   int sum(int x, int y) {
      return sum(y) - sum(x-1);
   }
}
using BIT::build; using BIT::sum; using BIT::add;
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      s[i] = s[i-1] + a[i];
   }
   build();
   for(int i = 1; i <= m; i++) {
      int opt; scanf("%d", &opt);
      if(opt == 1) {
         int x, k; scanf("%d%d", &x, &k);
         add(x, k);
      } else {
         int x, y; scanf("%d%d", &x, &y);
         printf("%d\n", sum(x, y));
      }
   }
   return 0;
}