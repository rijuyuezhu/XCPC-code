#include<cstdio>
#include<cstring>
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
const int MAXN = 105, MAXE = 22005, INF = 0x3f3f3f3f;
int n, s, t, _s, _t, S, T, head[MAXN], cur[MAXN], ver[MAXE], nxt[MAXE], edg[MAXE], addf[MAXN], cnt = 1, d[MAXN], que[MAXN], hd, tl;


void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}
void Addedge(int u, int v, int lo, int hi) {
	addedge(u, v, hi - lo); addf[u] -= lo; addf[v] += lo;
}
bool bfs() {
	memset(d, 0x00, sizeof d);
	memcpy(cur, head, sizeof cur);
	d[S] = 1; que[hd = tl = 1] = S;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) if(edg[i] && !d[ver[i]]) {
			int v = ver[i];
			d[v] = d[u] + 1;
			que[++tl] = v;
			if(v == T) return 1;
		}
	}
	return 0;
}
int dfs(int u, int flow) {
	if(u == T) return flow;
	int rest = flow;
	for(int i = cur[u]; i && rest; i = nxt[i]) {
		cur[u] = i;
		if(edg[i] && d[ver[i]] == d[u] + 1) {
			int v = ver[i];
			int k = dfs(v, min(rest, edg[i]));
			if(!k) d[v] = 0;
			edg[i] -= k; edg[i^1] += k; rest -= k;
		}
	}
	return flow - rest;
}
int dinic() {
	int maxflow = 0, flow;
	while(bfs()) while(flow = dfs(S, INF)) maxflow += flow;
	return maxflow;
}

int main() {
	n = read(); s = n+1; t = n+2; _s = n+3; _t = n+4;
	for(int i = 1; i <= n; i++) Addedge(s, i, 0, INF), Addedge(i, t, 0, INF);
	for(int i = 1; i <= n; i++) {
		int m = read();
		for(int j = 1; j <= m; j++) {
			int v = read();
			Addedge(i, v, 1, INF);
		}
	}
	for(int i = 1; i <= n+2; i++) {
		if(addf[i] < 0) addedge(i, _t, -addf[i]);
		if(addf[i] > 0) addedge(_s, i, addf[i]);
	}
	addedge(t, s, INF);
	S = _s; T = _t;
	dinic();
	int ans = edg[cnt];
	edg[cnt] = edg[cnt^1] = 0;
	S = t; T = s;
	printf("%d\n", ans - dinic());
	return 0;
}
