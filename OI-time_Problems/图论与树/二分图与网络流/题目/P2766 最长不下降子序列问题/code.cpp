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
const int MAXN = 505, MAXNODE = 1015, MAXEDGE = 3e5 + 5, INF = 0x3f3f3f3f;
int n, a[MAXN], f[MAXN], mx, ver[MAXEDGE], nxt[MAXEDGE], cnt = 1, head[MAXNODE], edg[MAXEDGE], s, t, cur[MAXNODE], d[MAXNODE], maxflow;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
	ver[++cnt] = u; nxt[cnt] = head[v]; edg[cnt] = 0; head[v] = cnt;
}


bool bfs() {
	static int que[MAXNODE];
	int hd = 1, tl = 0; que[++tl] = s;
	memcpy(cur, head, sizeof cur);
	memset(d, 0x00, sizeof d);
	d[s] = 1;
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
	n = read();
	/*if(n == 1) {
		printf("1\n1\n1\n");
		return 0;
	}*/
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) {
		f[i] = 1;
		for(int j = 1; j < i; j++)
			if(a[j] <= a[i]) f[i] = max(f[i], f[j]+1);
	}
	for(int i = 1; i <= n; i++) mx = max(mx, f[i]);
	printf("%d\n", mx);

	/*
	 * in:1~n
	 * out:n+1~n+n
	 *
	 */
	s = n+n+1; t = n+n+2;
	for(int i = 1; i <= n; i++) {
		addedge(i, i+n, 1);
		if(f[i] == 1) addedge(s, i, 1);
		if(f[i] == mx) addedge(i+n, t, 1);
	}
	for(int i = 1; i <= n; i++)
		for(int j = i+1; j <= n; j++)
			if(a[i] <= a[j] && f[j] == f[i] + 1)
				addedge(i+n, j, 1);
	dinic();
	printf("%d\n", maxflow);
	addedge(1, 1+n, INF);
	addedge(n, n+n, INF);
	if(f[1] == 1) addedge(s, 1, INF);
	if(f[n] == mx) addedge(n+n, t, INF);
	dinic();
	printf("%d\n", maxflow);
	return 0;
}
