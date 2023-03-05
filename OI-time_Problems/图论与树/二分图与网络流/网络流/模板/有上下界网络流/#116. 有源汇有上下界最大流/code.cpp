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
const int MAXN = 205, MAXM = 10005, MAXNODE = 215, MAXEDGE = 30005, INF = 0x3f3f3f3f;
int n, m, s, t, _s, _t, lo[MAXM], hi[MAXM], head[MAXN], addf[MAXM], ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], cnt = 1, d[MAXNODE], que[MAXNODE], hd, tl, ans;

void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}
bool bfs() {
	memset(d, 0x00, sizeof d); hd = 1; tl = 0;
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
	for(int i = head[u]; i && rest; i = nxt[i]) if(d[ver[i]] == d[u] + 1 && edg[i]) {
		int v = ver[i];
		int k = dfs(v, min(rest, edg[i]));
		if(!k) d[v] = 0;
		edg[i] -= k; rest -= k; edg[i^1] += k;
	}
	return flow - rest;
}
int dinic() {
	int maxflow = 0, flow;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
	return maxflow;
}
int main() {
	n = read(); m = read(); s = read(); t = read();
	_s = n+1; _t = n+2;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); lo[i] = read(); hi[i] = read();
		addedge(u, v, hi[i] - lo[i]);
		addf[u] -= lo[i]; addf[v] += lo[i];
	}
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		if(addf[i] < 0) addedge(i, _t, -addf[i]);
		if(addf[i] > 0) sum += addf[i], addedge(_s, i, addf[i]);
	}
	addedge(t, s, INF);
	swap(s, _s); swap(t, _t);
	if(dinic() != sum) {
		printf("please go home to sleep\n");
		return 0;
	}
	swap(s, _s); swap(t, _t);
	printf("%d\n", dinic());
	return 0;
}
