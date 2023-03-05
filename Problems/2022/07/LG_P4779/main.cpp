/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 16:25:28
 * @Description: https://www.luogu.com.cn/problem/P4779
 * @Tag: 图论，最短路
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
typedef pair<int, int> pr;
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, s;
struct Edge {
   int v, w, nxt;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
   e[++cnt] = (Edge){v, w, head[u]}; head[u] = cnt;
}

priority_queue<pr, vector<pr>, greater<pr> > pq;
int dist[MAXN], vis[MAXN];

int main() {
   n = read(); m = read(); s = read();
   for(int i = 1; i <= m; i++) {
      int u = read(), v = read(), w = read();
      addedge(u, v, w);
   }
   for(int i = 1; i <= n; i++) dist[i] = INF, vis[i] = 0;
   dist[s] = 0; pq.push(pr(0, s));
   while(pq.size()) {
      int u = pq.top().second; pq.pop();
      if(vis[u]) continue;
      vis[u] = 1;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v, w = e[i].w;
         if(vis[v]) continue;
         if(dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pq.push(pr(dist[v], v));
         }
      }
   }
   for(int i = 1; i <= n; i++) printf("%d ", dist[i]);
   puts("");
   return 0;
}