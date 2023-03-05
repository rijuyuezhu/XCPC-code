/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-12 14:16:03
 * @Description: https://www.luogu.com.cn/problem/P1991
 * @Tag: 图论，最小生成树
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
using ll = long long;
using db = double;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
constexpr int MAXN = 505;
int n, s;
struct Pnt {int x, y;};
Pnt p[MAXN];
int dist2(const Pnt &a, const Pnt &b) {
   return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
struct Edge {
   int u, v, d2;
};
Edge e[MAXN * MAXN];
int m;
bool operator < (const Edge &a, const Edge &b) {
   return a.d2 < b.d2;
}
int upto[MAXN];
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
int main() {
   s = read(); n = read();
   for(int i = 1; i <= n; i++) {
      p[i].x = read();
      p[i].y = read();
   }
   for(int i = 1; i <= n; i++)
      for(int j = i+1; j <= n; j++)
         e[++m] = {i, j, dist2(p[i], p[j])};
   sort(e + 1, e + 1 + m);
   int cnt = n;
   if(cnt <= s) {
      printf("0.00\n");
      return 0;
   }
   for(int i = 1; i <= n; i++) {
      upto[i] = i;
   }
   for(int i = 1; i <= m; i++) {
      auto now = e[i];
      int fu = getup(now.u), fv = getup(now.v);
      if(fu == fv) continue;
      upto[fu] = fv; --cnt;
      if(cnt == 1 || cnt <= s) {
         printf("%.2lf\n", sqrt(now.d2));
         return 0;
      }
   }
   return 0;
}