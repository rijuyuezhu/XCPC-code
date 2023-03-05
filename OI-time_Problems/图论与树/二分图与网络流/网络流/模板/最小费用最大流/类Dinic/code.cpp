#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e3 + 5, MAXM = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, head[MAXN], cnt = 1, ver[MAXM << 1], nxt[MAXM << 1], edg[MAXM << 1], cap[MAXM << 1], dist[MAXN], inq[MAXN], vis[MAXN], cur[MAXN], maxflow, mincost;
void addedge(int u, int v, int w, int c) {
	ver[++cnt] = v; edg[cnt] = w; cap[cnt] = c; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; cap[cnt] = -c; nxt[cnt] = head[v]; head[v] = cnt;
}
bool spfa() {
	queue<int> que;
	memset(dist, 0x3f, sizeof dist), memset(inq, 0x00, sizeof inq); memcpy(cur, head, sizeof head);
	dist[s] = 0; que.push(s); inq[s] = 1;
	while(que.size()) {
		int u = que.front(); que.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i])
			if(edg[i] && dist[ver[i]] > dist[u] + cap[i]) {
				dist[ver[i]] = dist[u] + cap[i];
				if(!inq[ver[i]]) inq[ver[i]] = 1, que.push(ver[i]);
			}
	}
	return dist[t] != INF;
}
int dfs(int u, int flow) {
	if(u == t) return flow;
	vis[u] = 1; int rest = flow;
	for(int i = cur[u]; i && rest; i = nxt[i]) {
		cur[u] = i;
		if(!vis[ver[i]] && edg[i] && dist[ver[i]] == dist[u] + cap[i]) {
			int k = dfs(ver[i], min(rest, edg[i]));
			edg[i] -= k; edg[i^1] += k; rest -= k;
			mincost += cap[i] * k;
		}
	}
	vis[u] = 0;
	return flow - rest;
}
void MCMF() {
	while(spfa()) {
		maxflow += dfs(s, INF);
	}
}
int main() {
	n = read(); m = read(); s = read(); t = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read(), c = read();
		addedge(u, v, w, c);
	}
	MCMF();
	printf("%d %d\n", maxflow, mincost);
	return 0;
}
