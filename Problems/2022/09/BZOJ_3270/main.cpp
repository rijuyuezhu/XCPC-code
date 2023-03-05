/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-03 11:50:51
 * @Description: https://darkbzoj.cc/problem/3270
 * @Tag: 期望，数学
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
constexpr int MAXN = 405;
constexpr db eps = 1e-8;
int n, m, s, t;
// Graph
int head[MAXN], cnt, deg[MAXN], tot;
struct Edge {
   int v, nxt;
}e[MAXN * 2];
void addedge(int u, int v) {
   e[++cnt] = {v, head[u]}; head[u] = cnt;
}
//others
db p[MAXN], a[MAXN][MAXN];
int get_num(int x, int y) {
   return (x - 1) * n + y;
}
void Guass(int tot) {
   for(int i = 1; i <= tot; i++) {
      int num = i;
      for(int j = num+1; j <= tot; j++)
         if(abs(a[j][i]) > abs(a[num][i]))
            num = j;
      if(num != i) 
         for(int j = i; j <= tot+1; j++)
            swap(a[i][j], a[num][j]);
      for(int j = i+1; j <= tot; j++) {
         db t = a[j][i] / a[i][i];
         for(int k = i; k <= tot+1; k++)
            a[j][k] -= t * a[i][k];
      }
   }
   for(int i = tot; i >= 1; i--) {
      for(int j = i+1; j <= tot; j++)
         a[i][tot+1] -= a[j][tot+1] * a[i][j];
      a[i][tot+1] /= a[i][i];
   }
}
int main() {
   n = read(), m = read(), s = read(), t = read();
   for(int i = 1; i <= m; i++) {
      int x = read(), y = read();
      addedge(x, y);
      addedge(y, x);
      deg[x]++; deg[y]++;
   }
   for(int i = 1; i <= n; i++) 
      scanf("%lf", &p[i]);
   tot = n * n;
   for(int x = 1; x <= n; x++)
      for(int y = 1; y <= n; y++) {
         int now = get_num(x, y);
         a[now][get_num(x,y)] = 1;
         if(x != y)
            a[now][get_num(x, y)] -= p[x] * p[y];
         for(int i = head[x]; i; i = e[i].nxt) {
            int px = e[i].v;
            if(px != y)
               a[now][get_num(px, y)] -= ((1 - p[px]) / deg[px]) * p[y];
         }
         for(int j = head[y]; j; j = e[j].nxt) {
            int py = e[j].v;
            if(x != py)
               a[now][get_num(x, py)] -= p[x] * ((1 - p[py]) / deg[py]);
         }
         for(int i = head[x]; i; i = e[i].nxt) {
            int px = e[i].v;
            for(int j = head[y]; j; j = e[j].nxt) {
               int py = e[j].v;
               if(px != py)
                  a[now][get_num(px, py)] -= ((1 - p[px]) / deg[px]) * ((1 - p[py]) / deg[py]);
            }
         }
         if(x == s && y == t)
            a[now][tot+1] = 1;
      }
   Guass(tot);
   for(int i = 1; i <= n; i++)
      printf("%.6lf ", a[get_num(i, i)][tot+1]);
   printf("\n");
   return 0;
}