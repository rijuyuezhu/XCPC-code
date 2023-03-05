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
const int MAXN = 315, MAXE = 14005, INF = 0x3f3f3f3f;
int n, s, t, _s, _t, S, T, addf[MAXN], head[MAXN], edg[MAXE], nxt[MAXE], cap[MAXE], ver[MAXE], cnt = 1, maxflow, mincost, incf[MAXN], pre[MAXN], dist[MAXN], inq[MAXN], ans;
void addedge(int u, int v, int w, int c) {
	ver[++cnt] = v; edg[cnt] = w; cap[cnt] = c; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; cap[cnt] = -c; nxt[cnt] = head[v]; head[v] = cnt;
}
void Addedge(int u, int v, int lo, int hi, int c) {
	addedge(u, v, hi - lo, c);
	addf[u] -= lo; addf[v] += lo; ans += c * lo;
}
bool spfa() {
	memset(dist, 0x3f, sizeof dist); memset(inq, 0x00, sizeof inq);
	incf[S] = INF; inq[S] = 1; dist[S] = 0;
	queue<int> que; que.push(S);
	while(que.size()) {
		int u = que.front(); que.pop(); inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(dist[v] > dist[u] + cap[i]) {
				dist[v] = dist[u] + cap[i];
				pre[v] = i;
				incf[v] = min(incf[u], edg[i]);
				if(!inq[v]) inq[v] = 1, que.push(v);
			}
		}
	}
	return dist[T] != INF;
}
void MCMF() {
	mincost = maxflow = 0;
	while(spfa()) {
		int now = T;
		maxflow += incf[T]; mincost += incf[T] * dist[T];
		while(now != S) {
			int p = pre[now];
			edg[p] -= incf[T]; edg[p^1] += incf[T];
			now = ver[p^1];
		}
	}
}
int main() {
	n = read();	s = 1; t = n+1; _s = n+2; _t = n+3;
	for(int i = 1; i <= n; i++) {
		int k = read();
		for(int j = 1; j <= k; j++) {
			int b = read(), t = read();
			Addedge(i, b, 1, INF, t);
		}
		Addedge(i, t, 0, INF, 0);
	}
	for(int i = 1; i <= n+1; i++) {
		if(addf[i] < 0) addedge(i, _t, -addf[i], 0);
		if(addf[i] > 0) addedge(_s, i, addf[i], 0);
	}
	addedge(t, s, INF, 0);
	S = _s; T = _t;
	MCMF();
	printf("%d\n", ans + mincost);
	return 0;
}
