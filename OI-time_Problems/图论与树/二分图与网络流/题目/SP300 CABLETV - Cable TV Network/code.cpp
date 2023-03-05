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
const int MAXN = 55, MAXM = 5005, MAXNODE = 115, MAXEDGE = 1e4 + 505, INF = 0x3f3f3f3f;
int n, m, head[MAXNODE], cnt = 1, ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], d[MAXNODE], cur[MAXNODE], s, t, maxflow;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
	ver[++cnt] = u; nxt[cnt] = head[v]; edg[cnt] = 0; head[v] = cnt;
}
struct Ed {int u, v;}e[MAXM];
bool bfs() {
	static int que[MAXNODE];
	int hd = 1, tl = 1; que[1] = s;
	memset(d, 0x00, sizeof d);
	memcpy(cur, head, sizeof cur);
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
			int k = dfs(v, min(edg[i], rest));
			if(!k) d[v] = 0;
			edg[i] -= k; edg[i^1] += k; rest -= k;
		}
	}
	return flow - rest;
}
void dinic() {
	int flow = 0;
	while(bfs()) while(flow = dfs(s, INF)) {
		maxflow += flow;
		if(maxflow >= INF) {maxflow = INF; return;}
	}
}
void work() {
	n = read(); m = read();	
	for(int i = 1; i <= m; i++) e[i].u = read()+1, e[i].v = read()+1;
	int ans = INF;
	for(s = 1; s <= n; s++)
		for(t = 1; t <= n; t++)
			if(s != t) {
				memset(head, 0x00, sizeof head); cnt = 1;
				for(int i = 1; i <= n; i++)
					if(i == s || i == t) addedge(i, i+n, INF);
					else addedge(i, i+n, 1);

				for(int i = 1; i <= m; i++) {
					addedge(e[i].u+n, e[i].v, INF);
					addedge(e[i].v+n, e[i].u, INF);
				}
				maxflow = 0;
				dinic();
				ans = min(ans, maxflow);
			}
	if(ans == INF || n <= 1) ans = n;
	printf("%d\n", ans);
}
int main() {
	int t = read();
	while(t--) work();
	return 0;
}
