/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-14 12:09:07
 * @Description: https://www.luogu.com.cn/problem/P1260  
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
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
constexpr int MAXN = 1005;
constexpr int MAXM = 5005;
constexpr int INF = 1e9;
int n, m;
struct Edge {
   int v, nxt, w;
}e[MAXM + MAXN];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
   e[++cnt] = {v, head[u], w}; head[u] = cnt;
}
queue<int> q;
int inq[MAXN], stp[MAXN], dist[MAXN];
bool spfa() {
   for(int i = 1; i <= n; i++) dist[i] = -INF;
   q.push(0); inq[0] = 1; stp[0] = 0; dist[0] = 0;
   while(q.size()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      for(int i = head[u]; i; i = e[i].nxt) {
         int v = e[i].v, w = e[i].w; 
         if(dist[v] < dist[u] + w) {
            dist[v] = dist[v] + w;
            stp[v] = stp[u] + 1;
            if(stp[v] >= n+1) return 1;
            if(!inq[v]) {
               q.push(v);
               inq[v] = 1;
            }
         }
      }
   }
   return 0;
}
int main() {
   n = read();
   m = read();
   for(int i = 1; i <= m; i++) {
      int u = read(), v = read(), b = read();
      addedge(u, v, -b);
   }
   for(int i = 1; i <= n; i++) addedge(0, i, 0);
   //Watch out that the graph has n+1 nodes
   if(spfa()) {
      printf("NO SOLUTION\n");
   } else {
      for(int i = 1; i <= n; i++)
         printf("%d\n", dist[i]);
   }
   return 0;
}