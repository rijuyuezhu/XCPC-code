#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 370, MAXM = 1005;
const int MAXNODE = 1405, MAXEDGE = 230005;
const int INF = 0x3f3f3f3f;
int n, m, s, t, _s, _t, S, T, head[MAXNODE], cur[MAXNODE], addf[MAXNODE], edg[MAXEDGE], ver[MAXEDGE], nxt[MAXEDGE], cnt = 1, d[MAXNODE], que[MAXNODE], hd, tl;
void clear() {
	memset(head, 0x00, sizeof head); cnt = 1; 
	memset(addf, 0x00, sizeof addf);
}
void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}
void Addedge(int u, int v, int lo, int hi) {
	addedge(u, v, hi - lo); addf[u] -= lo; addf[v] += lo;
}
bool bfs() {
	memset(d, 0x00, sizeof d); hd = 1; tl = 0; 
	memcpy(cur, head, sizeof cur);
	d[S] = 1; que[++tl] = S;
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
			edg[i] -= k; rest -= k; edg[i^1] += k;
		}
	}
	return flow - rest;
}
int dinic() {
	int maxflow = 0, flow;
	while(bfs()) while(flow = dfs(S, INF)) maxflow += flow;
	return maxflow;
}
void work() {
	clear();
	s = n+m+1; t = n+m+2; _s = n+m+3; _t = n+m+4;
	for(int i = 1; i <= m; i++) {
		int G = read();
		Addedge(i+n, t, G, INF);
	}
	for(int i = 1; i <= n; i++) {
		int C = read(), D = read();
		Addedge(s, i, 0, D);
		for(int j = 1; j <= C; j++) {
			int T = read()+1, L = read(), R = read();
			Addedge(i, T+n, L, R);
		}
	}
	int sum = 0;
	for(int i = 1; i <= n+m+2; i++) {
		if(addf[i] < 0) addedge(i, _t, -addf[i]);
		if(addf[i] > 0) addedge(_s, i, addf[i]), sum += addf[i];
	}
	addedge(t, s, INF);
	S = _s; T = _t;
	if(dinic() != sum) {
		printf("-1\n\n");
		return;
	}
	S = s; T = t;
	printf("%d\n\n", dinic());
}
int main() {
	while(scanf("%d%d", &n, &m) != EOF) work();
	return 0;
}
