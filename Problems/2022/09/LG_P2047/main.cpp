/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-12 09:11:43
 * @Description: https://www.luogu.com.cn/problem/P2047
 * @Tag: 图论，最短路
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
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
constexpr int MAXN = 105, MAXM = 4505, INF = 0x3f3f3f3f;
int n, m;
int dis[MAXN][MAXN];
ll ways[MAXN][MAXN];
int main() {
   n = read(), m = read();
   for(int i = 1; i <= n; i++)
      for(int j = 1; j <= n; j++)
         dis[i][j] = INF, ways[i][j] = 0;
   for(int i = 1; i <= m; i++) {
      int u = read(), v = read();
      dis[u][v] = dis[v][u] = read();
      ways[u][v] = ways[v][u] = 1;
   }
   for(int k = 1; k <= n; k++)
      for(int i = 1; i <= n; i++)
         for(int j = 1; j <= n; j++)
            if(i != j && j != k && i != k) {
               if(dis[i][k] + dis[k][j] < dis[i][j]) {
                  dis[i][j] = dis[i][k] + dis[k][j];
                  ways[i][j] = ways[i][k] * ways[k][j];
               } else if(dis[i][k] + dis[k][j] == dis[i][j]) {
                  ways[i][j] += ways[i][k] * ways[k][j];
               }
            }
   for(int k = 1; k <= n; k++) {
      db ans = 0.0;
      for(int i = 1; i <= n; i++)   
         for(int j = 1; j <= n; j++)
            if(i != k && j != k && i != j)
               if(dis[i][j] == dis[i][k] + dis[k][j])
                  ans += (db)ways[i][k] * ways[k][j] / ways[i][j];
      printf("%.3lf\n", ans);
   }
   return 0;
}