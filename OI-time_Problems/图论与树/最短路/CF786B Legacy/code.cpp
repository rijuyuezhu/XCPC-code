#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
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
const int MAXN = 1e5 + 5, MAXNODE = 1e6 + 5, MAXEDGE = 6e6 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, q, s, num, head[MAXNODE], cnt, ver[MAXEDGE], nxt[MAXEDGE], vis[MAXNODE];
ll edg[MAXEDGE], dist[MAXNODE];
struct QNode{int u; ll d;};
bool operator < (QNode a, QNode b) {return a.d > b.d;}
priority_queue<QNode> pq;
int in[MAXN << 2], out[MAXN << 2];
void addedge(int u, int v, ll w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
#define ls p << 1
#define rs p << 1 | 1
void build(int p, int l, int r) {
	in[p] = ++num; out[p] = ++num;
	if(l == r) {
		addedge(in[p], l, 0); addedge(l, out[p], 0);
		return;
	}
	int m = (l + r) >> 1;
	build(ls, l, m); build(rs, m+1, r);
	addedge(in[p], in[ls], 0); addedge(in[p], in[rs], 0);
	addedge(out[ls], out[p], 0); addedge(out[rs], out[p], 0);
}
void addedgein(int p, int l, int r, int x, int y, int u, ll w) {
	if(x <= l && r <= y) {
		addedge(u, in[p], w);
		return ;
	}
	int m = (l + r) >> 1;
	if(x <= m) addedgein(ls, l, m, x, y, u, w);
	if(y > m) addedgein(rs, m+1, r, x, y, u, w);
}
void addedgeout(int p, int l, int r, int x, int y, int v, ll w) {
	if(x <= l && r <= y) {
		addedge(out[p], v, w);
		return ;
	}
	int m = (l + r) >> 1;
	if(x <= m) addedgeout(ls, l, m, x, y, v, w);
	if(y > m) addedgeout(rs, m+1, r, x, y, v, w);
}
#undef ls
#undef rs
void dijkstra(int s) {
	memset(dist, 0x3f, sizeof dist);
	memset(vis, 0x00, sizeof vis);
	dist[s] = 0; pq.push((QNode){s, 0});
	while(pq.size()) {
		int u = pq.top().u; pq.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i];
			if(dist[v] > dist[u] + edg[i]) {
				dist[v] = dist[u] + edg[i];
				pq.push((QNode){v, dist[v]});
			}
		}
	}
}
int main() {
	n = read(); q = read(); s = read();
	num = n;
	build(1, 1, n);
	for(int i = 1; i <= q; i++) {
		int opt = read();
		if(opt == 1) {
			int u = read(), v = read(); ll w = read();
			addedge(u, v, w);
		} else if(opt == 2) {
			int u = read(), l = read(), r = read(); ll w = read();
			addedgein(1, 1, n, l, r, u, w);
		} else {
			int v = read(), l = read(), r = read(); ll w = read();
			addedgeout(1, 1, n, l, r, v, w);
		}
	}
	dijkstra(s);
	for(int i = 1; i <= n; i++)
		if(dist[i] == INF) printf("-1 ");
		else printf("%lld ", dist[i]);
	printf("\n");
	return 0;
}
