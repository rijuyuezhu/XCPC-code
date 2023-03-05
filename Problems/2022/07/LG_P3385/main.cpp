/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 20:31:52
 * @Description: https://www.luogu.com.cn/problem/P3385
 * @Tag: 负环，最短路，SPFA
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
const int MAXN = 2e3 + 5;
const int MAXM = 3e3 + 5;
const int INF = 0x3f3f3f3f;
int n, m;
struct Edge {int v, w, nxt;}e[MAXM * 2];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
   e[++cnt] = (Edge){v, w, head[u]}; head[u] = cnt;
   if(w >= 0) {
      e[++cnt] = (Edge){u, w, head[v]}; head[v] = cnt;
   }
}

int vis[MAXN], dist[MAXN], num[MAXN];
queue<int> que;

bool spfa() {
   dist[1] = 0; num[1] = 0; vis[1] = 1; que.push(1);
   while(que.size()) {
      int u = que.front(); que.pop(); vis[u] = 0;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v, w = e[i].w; 
         if(dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            num[v] = num[u] + 1;
            if(num[v] >= n) return 1;
            if(!vis[v]) vis[v] = 1, que.push(v);
         }
      }
   }
   return 0;
}

void clear() {
   cnt = 0;
   for(int i = 1; i <= n; i++) head[i] = vis[i] = 0, dist[i] = INF, num[i] = 0;
   que = queue<int>();
}
void work() {
   n = read(), m = read();
   clear();
   for(int i = 1; i <= m; i++) {
      int u = read(), v = read(), w = read();
      addedge(u, v, w);
   }
   if(spfa()) printf("YES\n");
   else printf("NO\n");
}
int main() {
   int T = read();
   while(T--) work();
   return 0;
}