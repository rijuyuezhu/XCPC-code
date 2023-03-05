/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-11 22:06:03
 * @Description: https://www.luogu.com.cn/problem/P1875  
 * @Tag: 最短路
*/
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
using ll = long long;
using db = double;
using pr = pair<ll, int>;
using pri_q = priority_queue<pr, vector<pr>, greater<pr> >;
constexpr int MAXN = 1005;
int n;
int head[MAXN], cnt;
int vis[MAXN];
ll dist[MAXN], ways[MAXN];
vector<pr> G[MAXN];//<b, c>
pri_q pq;
int main() {
   scanf("%d", &n);
   for(int i = 0; i < n; i++) {
      scanf("%lld", &dist[i]);
      ways[i] = 1;
      pq.push(pr(dist[i], i));
   }
   while(1) {
      int a, b, c;
      if(scanf("%d%d%d", &a, &b, &c) != 3)
         break;
      G[a].push_back(pr(b, c));
      if(a != b) G[b].push_back(pr(a, c));
   }
   while(pq.size()) {
      int u = pq.top().second; pq.pop();
      if(vis[u]) continue;
      vis[u] = 1;
      for(auto it : G[u]) {// (u, v) -> w
         int v = it.first, w = it.second;
         if(!vis[v]) continue;
         if(dist[w] > dist[u] + dist[v]) {
            dist[w] = dist[u] + dist[v];
            ways[w] = ways[u] * ways[v];
            pq.push(pr(dist[v], v));
         } else if(dist[w] == dist[u] + dist[v]) {
            ways[w] += ways[u] * ways[v];
         }
      }
   }
   printf("%lld %lld\n", dist[0], ways[0]);
   return 0;
}