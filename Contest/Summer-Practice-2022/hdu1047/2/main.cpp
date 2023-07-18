/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-28 12:02:00
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1047&pid=1002
 * @Tag: 
*/

#include<cstdio>
#include<queue>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pr;
const int MAXN = 2e5 + 5;
const int MAXM = 3e5 + 5;
const ll INF = 1e17;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}

struct Edge {int v, e, p, nxt;}ed[MAXM], ed2[MAXM], ed3[MAXM];
int head[MAXN], cnt, head2[MAXN], cnt2, head3[MAXN], cnt3;
int n, m;
void addedge(int u, int v, int e, int p) {
   ed[++cnt] = (Edge){v, e, p, head[u]}; head[u] = cnt;
}
void addedge2(int u, int v, int e, int p) {
   ed2[++cnt2] = (Edge){v, e, p, head2[u]}; head2[u] = cnt2;
}
void addedge3(int u, int v, int e, int p) {
   ed3[++cnt3] = (Edge){v, e, p, head3[u]}; head3[u] = cnt3;
}
//Dijkstra
ll dist[MAXN];
int vis[MAXN];
void Dij() {
   priority_queue<pr, vector<pr>, greater<pr> > pq;
   for(int i = 1; i <= n; i++) dist[i] = INF, vis[i] = 0;
   dist[1] = 0;
   pq.push(pr(0, 1));
   while(pq.size()) {
      int u = pq.top().second; pq.pop();
      if(vis[u]) continue;
      vis[u] = 1;
      for(int i = head[u]; i; i = ed[i].nxt) {
         int v = ed[i].v, w = ed[i].e; 
         if(vis[v]) continue;
         if(dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pq.push(pr(dist[v], v));
         }
      }
   }
}

int scc[MAXN], _scc, dfn[MAXN], low[MAXN], _dfn, ins[MAXN], st[MAXN], _st;
void tarjan(int u) {
   dfn[u] = low[u] = ++_dfn; ins[u] = 1; st[++_st] = u;
   for(int i = head[u]; i; i = ed[i].nxt) {
      int v = ed[i].v, w = ed[i].e;
      if(dist[v] != dist[u] + w) continue;
      if(!dfn[v]) {
         tarjan(v);
         low[u] = min(low[u], low[v]);
      } else if(ins[v])
         low[u] = min(low[u], dfn[v]);
   }
   if(low[u] == dfn[u]) {
      _scc++;
      int t;
      do {
         t = st[_st--]; ins[t] = 0;
         scc[t] = _scc;
      }while(t != u);
   }
}

ll scc_val[MAXN], f[MAXN];
int tag[MAXN];

void dfs1(int u) {
   if(tag[u]) return;
   tag[u] = 1;
   for(int i = head3[u]; i; i = ed3[i].nxt) {
      int v = ed3[i].v;
      dfs1(v);
   }
}
ll dfs2(int u) {
   if(!tag[u]) return -INF;
   if(~f[u]) return f[u];
   f[u] = scc_val[u];
   for(int i = head2[u]; i; i = ed2[i].nxt) {
      int v = ed2[i].v, p = ed2[i].p;
      f[u] = max(f[u], scc_val[u] + dfs2(v) + p);
   }
   return f[u];
}

void work() {
   n = read(), m = read();
   for(int i = 1; i <= n; i++) head[i] = head2[i] = head3[i] = 0;
   for(int i = 1; i <= n; i++) dfn[i] = low[i] = scc[i] = ins[i] = scc_val[i] = tag[i] = 0, f[i] = -1;
   _st = _dfn = cnt = cnt2 = cnt3 = 0;
   for(int i = 1; i <= m; i++) {
      int u = read(), v = read(), e = read(), p = read();
      addedge(u, v, e, p);
   }
   Dij();
   for(int i = 1; i <= n; i++)
      if(!dfn[i])
         tarjan(i);
   for(int u = 1; u <= n; u++)
      for(int i = head[u]; i; i = ed[i].nxt) {
         int v = ed[i].v, w = ed[i].e, p = ed[i].p;
         if(dist[v] != dist[u] + w) continue;
         if(scc[u] == scc[v]) scc_val[scc[u]] += p;
         else {
            addedge2(scc[u], scc[v], w, p);//正
            addedge3(scc[v], scc[u], w, p);//反
         }
      }
   dfs1(scc[n]);
   printf("%lld %lld\n", dist[n], dfs2(scc[1]));
}
int main() {
   int t = read();
   while(t--) work();
   return 0;
}