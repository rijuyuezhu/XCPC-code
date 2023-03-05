/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-13 22:00:32
 * @Description: https://www.luogu.com.cn/problem/P4047
 * @Tag: 
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
constexpr int MAXN = 1e3 + 5, MAXM = 1e6 + 5;
int n, k, m;
struct Pnt {
   int x, y;
};
Pnt p[MAXN];
int Dist2(const Pnt &a, const Pnt &b) {
   return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
struct Edge {
   int u, v, d2;
};
Edge e[MAXM];
bool operator < (const Edge &a, const Edge &b) {
   return a.d2 < b.d2;
}
int upto[MAXN];
int getup(int u) {
   return u == upto[u] ? u : upto[u] = getup(upto[u]);
}
int ans2;
void Kruskal() {
   for(int i = 1; i <= n; i++) upto[i] = i;
   sort(e + 1, e + 1 + m);
   int cnt = n;
   for(int i = 1; i <= m; i++) {
      const auto& now = e[i];
      int fu = getup(now.u), fv = getup(now.v);
      if(fu == fv) continue;
      upto[fu] = fv;
      cnt--;
      if(cnt == k-1) {
         ans2 = e[i].d2;
         return;
      }
   }
}
int main() {
   n = read(); k = read();
   for(int i = 1; i <= n; i++) {
      p[i].x = read(); p[i].y = read();
   }
   for(int i = 1; i <= n; i++)
      for(int j = i+1; j <= n; j++)
         e[++m] = {i, j, Dist2(p[i], p[j])};
   Kruskal();
   printf("%.2lf\n", sqrt((db)ans2));
   return 0;
}