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
const int MAXN = 255, MAXNODE = 505, MAXEDGE = 1.3e5, INF = 0x3f3f3f3f;
int n, m, k, a[MAXN][MAXN], head[MAXNODE], cur[MAXNODE], ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], cnt, s, t, maxflow, que[MAXNODE], hd, tl, dep[MAXNODE];
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
	ver[++cnt] = u; nxt[cnt] = head[v]; edg[cnt] = 0; head[v] = cnt;
}
bool bfs() {
	for(int i = 1; i <= t; i++) cur[i] = head[i], dep[i] = 0;
	dep[s] = 1; que[hd = tl = 1] = s;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i];
			if(edg[i] && !dep[v]) {
				dep[v] = dep[u] + 1;
				if(v == t) return 1;
				que[++tl] = v;
			}
		}
	}
	return 0;
}
int dfs(int u, int flow) {
	if(u == t) return flow;
	int rest = flow;
	for(int i = cur[u]; i && rest; i = nxt[i]) {
		cur[u] = i;
		int v = ver[i];
		if(edg[i] && dep[v] == dep[u] + 1) {
			int k = dfs(v, min(rest, edg[i]));
			if(!k) dep[v] = 0;
			edg[i] -= k;
			rest -= k;
			edg[i^1] += k;
		}
	}
	return flow - rest;
}
void dinic() {
	int flow = 0;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
}
bool check(int v) {
	cnt = 1; s = n + m + 1, t = n + m + 2;
	for(int i = 1; i <= t; i++) head[i] = 0;
	for(int i = 1; i <= n; i++) addedge(s, i, 1);
	for(int i = 1; i <= m; i++) addedge(i+n, t, 1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(a[i][j] <= v) addedge(i, j+n, 1);
	maxflow = 0;
	dinic();
	return maxflow >= n - k + 1;
}
int main() {
	n = read(); m = read(); k = read();	 	
	int l = 1e9, r = 0, ans = -1;
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= m; j++)
			a[i][j] = read(), l = min(l, a[i][j]), r = max(r, a[i][j]);
	while(l <= r) {
		int m = (l + r) >> 1;
		if(check(m)) ans = m, r = m-1;
		else l = m+1;
	}
	printf("%d\n", ans);
	return 0;
}
