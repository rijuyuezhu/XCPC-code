/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-12 09:34:14
 * @Description: https://www.luogu.com.cn/problem/P1265 
 * @Tag: 最小生成树，Prim
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
constexpr int MAXN = 5005;
constexpr db INF = 1e20;
int n;
struct Pnt {
   int x, y;
};
Pnt p[MAXN];
db dist(const Pnt &a, const Pnt &b) {
   return sqrt(db(a.x - b.x) * (a.x - b.x) + db(a.y - b.y) * (a.y - b.y));
}
db dis[MAXN];
int vis[MAXN];
int main() {
   n = read();
   for(int i = 1; i <= n; i++) {
      p[i].x = read();
      p[i].y = read();
   }
   db ans = 0.0;
   for(int i = 1; i <= n; i++)
      dis[i] = INF, vis[i] = 0;
   dis[1] = 0;
   for(int i = 1; i <= n; i++) {
      int num = 0;
      for(int j = 1; j <= n; j++)
         if(!vis[j])
            if(!num || dis[num] > dis[j])
               num = j;
      vis[num] = 1;
      ans += dis[num];
      for(int j = 1; j <= n; j++)
         if(!vis[j])
            dis[j] = min(dis[j], dist(p[num], p[j]));
   }
   printf("%.2lf\n", ans);
   return 0;
}