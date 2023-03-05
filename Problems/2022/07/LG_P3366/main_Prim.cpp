/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:26:15
 * @Description: https://www.luogu.com.cn/problem/P3366
 * @Tag: 最小生成树，Prim
*/

#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 5e3+5;
const int MAXM = 2e5+5;
const int INF = 1e9;
int n, m;
int e[MAXN][MAXN], dist[MAXN], vis[MAXN], ans;

int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i++)
      for(int j = 1; j <= n; j++)
         e[i][j] = INF;
   for(int i = 1; i <= m; i++) {
      int u, v, w; scanf("%d%d%d", &u, &v, &w);
      e[u][v] = e[v][u] = min(e[u][v], w);
   }
   for(int i = 1; i <= n; i++) dist[i] = INF, vis[i] = 0;
   dist[1] = 0;
   for(int i = 1; i <= n; i++) {
      int now = -1;
      for(int j = 1; j <= n; j++) 
         if(!vis[j] && (now == -1 || dist[j] < dist[now])) 
            now = j;
      if(now == -1 || dist[now] == INF) {
         printf("orz\n");
         return 0;
      }
      ans += dist[now]; vis[now] = 1;
      for(int j = 1; j <= n; j++) 
         if(!vis[j])
            dist[j] = min(dist[j], e[now][j]);
   }
   printf("%d\n", ans);
   return 0;
}