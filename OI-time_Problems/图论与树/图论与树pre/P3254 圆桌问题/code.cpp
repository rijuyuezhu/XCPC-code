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
const int MAXM = 155, MAXN = 275, MAXNODE = MAXM + MAXN + 2, MAXEDGE = (MAXM + MAXN + MAXM * MAXN) * 2;
const int INF = 0x3f3f3f3f;
int m, n, r[MAXM], c[MAXN], ver[MAXEDGE], edg[MAXEDGE], nxt[MAXEDGE], cnt = 1, head[MAXNODE], s, t;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}

int d[MAXNODE], que[MAXNODE], hd, tl;
bool bfs() {
	hd = 1, tl = 0;
	memset(d, 0x00, sizeof(int) *(m+n+5));
	d[s] = 1; que[++tl] = s;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) if(!d[ver[i]] && edg[i]) {
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
	for(int i = head[u]; i && rest; i = nxt[i]) {
		int v = ver[i];
		if(d[v] == d[u] + 1 && edg[i]) {
			int k = dfs(v, min(flow, edg[i]));
			if(!k) d[v] = 0;
			rest -= k;
			edg[i] -= k;
			edg[i^1] += k;
		}
	}
	return flow - rest;
}
void dinic() {
	while(bfs()) {
		while(dfs(s, INF));
	}
}
int main() {
	m = read(), n = read();
	for(int i = 1; i <= m; i++) r[i] = read();
	for(int i = 1; i <= n; i++) c[i] = read();
	/*
	 * 1~m;m+1~m+n;m+n+1;m+n+2
	 */
	s = m+n+1, t = m+n+2;
	for(int i = 1; i <= m; i++) addedge(s, i, r[i]);
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			addedge(i, j+m, 1);
	for(int i = 1; i <= n; i++) addedge(i+m, t, c[i]);
	dinic();
	for(int i = head[s]; i; i = nxt[i])
		if((i & 1) == 0 && edg[i]) {
			printf("0\n");
			return 0;
		}
	printf("1\n");
	for(int u = 1; u <= m; u++) {
		for(int i = head[u]; i; i = nxt[i])
			if((i & 1) == 0 && !edg[i]) printf("%d ", ver[i] - m);
		printf("\n");
	}

	return 0;
}
