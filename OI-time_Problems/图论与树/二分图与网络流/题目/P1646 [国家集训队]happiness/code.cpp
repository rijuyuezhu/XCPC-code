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
const int MAXN = 105, MAXNODE = 5e4 + 15, MAXEDGE = 3e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, head[MAXNODE], ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], cnt = 1, Nnum, ans, d[MAXNODE], cur[MAXNODE], maxflow;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
	ver[++cnt] = u; nxt[cnt] = head[v]; edg[cnt] = 0; head[v] = cnt;
}
int num(int x, int y) {return (x-1) * m + y;}
bool bfs() {
	static int que[MAXNODE];
	int hd = 1, tl = 1; que[tl] = s;
	memset(d, 0x00, sizeof d); d[s] = 1;
	memcpy(cur, head, sizeof cur);
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(!d[v]) {
				d[v] = d[u] + 1;
				que[++tl] = v;
				if(v == t) return 1;
			}
		}
	}
	return 0;
}
int dfs(int u, int flow) {
	if(u == t) return flow;
	int rest = flow;
	for(int i = cur[u]; i && rest; i = nxt[i]) {
		cur[u] = i; int v = ver[i];
		if(d[v] == d[u] + 1 && edg[i]) {
			int k = dfs(v, min(rest, edg[i]));
			if(!k) d[v] = 0;
			edg[i] -= k; edg[i^1] += k; rest -= k;
		}
	}
	return flow - rest;
}
void dinic() {
	int flow = 0;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
}
int main() {
	n = read(); m = read();	
	Nnum = n*m;
	s = ++Nnum; t = ++Nnum;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			int w = read(); ans += w;
			addedge(s, num(i, j), w);
		}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			int w = read(); ans += w;
			addedge(num(i, j), t, w);
		}
	for(int i = 1; i < n; i++)
		for(int j = 1; j <= m; j++) {
			int w = read(); ans += w;
			Nnum++;
			addedge(s, Nnum, w); addedge(Nnum, num(i, j), INF); addedge(Nnum, num(i+1, j), INF);
		}
	for(int i = 1; i < n; i++)
		for(int j = 1; j <= m; j++) {
			int w = read(); ans += w;
			Nnum++;
			addedge(Nnum, t, w); addedge(num(i, j), Nnum, INF); addedge(num(i+1, j), Nnum, INF);
		}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < m; j++) {
			int w = read(); ans += w;
			Nnum++;
			addedge(s, Nnum, w); addedge(Nnum, num(i, j), INF); addedge(Nnum, num(i, j+1), INF);
		}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < m; j++) {
			int w = read(); ans += w;
			Nnum++;
			addedge(Nnum, t, w); addedge(num(i, j), Nnum, INF); addedge(num(i, j+1), Nnum, INF);
		}
	dinic();
	printf("%d\n", ans - maxflow);
	return 0;
}
