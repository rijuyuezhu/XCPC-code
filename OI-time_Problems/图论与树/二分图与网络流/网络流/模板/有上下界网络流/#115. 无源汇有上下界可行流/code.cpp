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
const int MAXN = 205, MAXM = 10205, MAXNODE = 205, MAXEDGE = 25005;
const int INF = 0x3f3f3f3f;
int n, m, s, t, low[MAXM], addf[MAXM], ans[MAXM], ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], id[MAXEDGE], head[MAXNODE], cnt = 1;
void addedge(int u, int v, int w, int i) {
	ver[++cnt] = v; edg[cnt] = w; id[cnt] = i; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; id[cnt] = i; nxt[cnt] = head[v]; head[v] = cnt;
}
int d[MAXNODE], que[MAXNODE], hd, tl;
bool bfs() {
	hd = 1; tl = 0;
	memset(d, 0x00, sizeof d);
	d[s] = 1; que[++tl] = s;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) if(edg[i] && !d[ver[i]]) {
			int v = ver[i];
			d[v] = d[u] + 1;
			que[++tl] = v;
			if(v == t) return 1;
		}
	}
	return 0;
}
int dfs(int u, int flow) {
	if(u == t) return flow;
	int rest = flow;
	for(int i = head[u]; i && rest; i = nxt[i]) if(edg[i] && d[ver[i]] == d[u] + 1) {
		int v = ver[i];
		int k = dfs(v, min(rest, edg[i]));
		if(!k) d[v] = 0;
		edg[i] -= k; edg[i^1] += k; rest -= k;
	}
	return flow - rest;
}

int dinic() {
	int maxflow = 0, flow;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
	return maxflow;
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); low[i] = read(); int h = read();
		addedge(u, v, h - low[i], i);
		addf[u] -= low[i]; addf[v] += low[i];
	}
	s = 0; t = n+1;
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		if(addf[i] < 0) addedge(i, t, -addf[i], 0);
		if(addf[i] > 0) sum += addf[i], addedge(s, i, addf[i], 0);
	}
	if(dinic() == sum) {
		printf("YES\n");
		for(int u = 1; u <= n; u++)
			for(int i = head[u]; i; i = nxt[i])
				if(i % 2 == 0 && id[i])
					ans[id[i]] = low[id[i]] + edg[i^1];
		for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	} else printf("NO\n");
	return 0;	
}
