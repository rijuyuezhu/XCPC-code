#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
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
const int MAXN = 5e3 + 5;
const int MAXM = 1e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, s, t, nxt[MAXM], ver[MAXM], head[MAXN], cnt = 1;
ll edg[MAXM], cap[MAXM];
void addedge(int u, int v, ll w, ll c) {
	ver[++cnt] = v; edg[cnt] = w; cap[cnt] = c; nxt[cnt] = head[u], head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; cap[cnt] = -c; nxt[cnt] = head[v], head[v] = cnt;
}

queue<int> que;
int inq[MAXN], pre[MAXN];
ll dist[MAXN], incf[MAXN], maxflow, mincost;
bool spfa() {
	memset(dist, 0x3f, sizeof dist); memset(inq, 0x00, sizeof inq);
	incf[s] = INF;
	dist[s] = 0, inq[s] = 1, que.push(s);
	while(!que.empty()) {
		int u = que.front(); que.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(dist[v] > dist[u] + cap[i]) {
				dist[v] = dist[u] + cap[i];
				pre[v] = i;
				incf[v] = min(incf[u], edg[i]);
				if(!inq[v]) que.push(v), inq[v] = 1;
			}
		}
	}
	return dist[t] != INF;
}
void upd() {
	int now = t;
	while(now != s) {
		int p = pre[now];
		edg[p] -= incf[t];
		edg[p^1] += incf[t];
		now = ver[p^1];
	}
	maxflow += incf[t];
	mincost += incf[t] * dist[t];
}
void MCMF() {
	while(spfa()) upd();
}
int main() {
	n = read(); m = read(); s = read(); t = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll w = read(), c = read();
		addedge(u, v, w, c);
	}
	MCMF();
	printf("%lld %lld\n", maxflow, mincost);
	return 0;
}
