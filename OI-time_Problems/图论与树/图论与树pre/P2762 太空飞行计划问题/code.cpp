#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
/*char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)*/
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 55, MAXNODE = 105, MAXEDGE = 10005, INF = 0x3f3f3f3f;
int m, n, s, t, ans;
int nxt[MAXEDGE], ver[MAXEDGE], cnt = 1, edg[MAXEDGE], head[MAXNODE];
char tools[10000];
void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}
/*1~m;m+1~m+n;m+n+1;m+n+2*/


int que[MAXN], d[MAXN], hd, tl;

bool bfs() {
	memset(d, 0x00, sizeof d);
	hd = 1; tl = 0;
	que[++tl] = s; d[s] = 1;
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
	for(int i = head[u]; i && rest; i = nxt[i]) if(d[ver[i]] == d[u] + 1 && edg[i]) {
		int v = ver[i], w = edg[i];
		int k = dfs(v, min(rest, w));
		if(!k) d[v] = 0;
		edg[i] -= k;
		edg[i^1] += k;
		rest -= k;
	}
	return flow - rest;
}
int dinic() {
	int ans = 0, flow;
	while(bfs()) {
		while(flow = dfs(s, INF))
			ans += flow;
	}
	return ans;
}
int main() {
	m = read(), n = read();
	s = m+n+1, t = m+n+2;
	for(int i = 1; i <= m; i++) {
		int w = read(); ans += w;
		addedge(s, i, w);
		memset(tools, 0x00, sizeof tools);
		cin.getline(tools, 10000);
		int ulen = 0, tool;
		while(sscanf(tools + ulen, "%d", &tool) == 1) {
			addedge(i, tool + m, INF);
			if(tool == 0) ulen++;
			else {
				while(tool) {
					tool /= 10;
					ulen++;
				}
			}
			ulen++;
		}
	}
	for(int i = 1; i <= n; i++) {
		int w = read();
		addedge(i+m, t, w);
	}
	ans -= dinic();
	for(int i = 1; i <= m; i++)
		if(d[i]) printf("%d ", i);
	printf("\n");
	for(int i = 1; i <= n; i++) 
		if(d[i+m]) printf("%d ", i);
	printf("\n%d\n", ans);

	return 0;
}
