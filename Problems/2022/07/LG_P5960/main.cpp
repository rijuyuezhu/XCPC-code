/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-30 06:30:25
 * @Description: https://www.luogu.com.cn/problem/P5960
 * @Tag: 图论，最短路，差分约束
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 5e3 + 5;
const int MAXM = 5e3 + 5;
const int INF = 0x3f3f3f3f;
int n, m;
struct Edge {
   int v, w, nxt;
}e[MAXN + MAXM];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
   e[++cnt] = (Edge){v, w, head[u]}; head[u] = cnt;
}
int dist[MAXN], vis[MAXN], num[MAXN];
queue<int> que;
bool spfa() {
   for(int i = 0; i <= n; i++) dist[i] = -INF, vis[i] = 0, num[i] = 0;
   dist[0] = 0; num[0] = 0; vis[0] = 1; que.push(0);
   while(que.size()) {
      int u = que.front(); que.pop(); vis[u] = 0;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v, w = e[i].w;
         if(dist[v] < dist[u] + w) {
            dist[v] = dist[u] + w;
            num[v] = num[u] + 1;
            if(num[v] >= n+1) return 1;
            if(!vis[v]) {
               vis[v] = 1; que.push(v);
            }
         }
      }
   }
   return 0;
}
int main() {
   n = read(), m = read();
   for(int i = 1; i <= m; i++) {
      int u = read(), v = read(), w = read();
      addedge(u, v, -w);
   }
   for(int i = 1; i <= n; i++) addedge(0, i, 0);
   if(spfa()) {
      printf("NO\n");
   } else {
      for(int i = 1; i <= n; i++) printf("%d ", dist[i]);
      printf("\n");
   }
   return 0;
}