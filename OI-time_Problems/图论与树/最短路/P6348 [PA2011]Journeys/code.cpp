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
const int MAXN = 5e5 + 5;
const int MAXM = 1e5 + 5;
const int MAXNODE = 5e6 + 5, MAXEDGE = 3e7 + 5;
int n, m, s, head[MAXNODE], ver[MAXEDGE], edg[MAXEDGE], nxt[MAXEDGE], cnt, num, vis[MAXNODE], dist[MAXNODE], que[MAXNODE * 2], hd, tl;
int in[MAXN << 2], out[MAXN << 2];
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
#define ls p << 1
#define rs p << 1 | 1
void build(int p, int l, int r) {
	in[p] = ++num; out[p] = ++num;
	if(l == r) {
		addedge(in[p], l, 0); addedge(l, out[p], 0);
		return ;
	}
	int m = (l + r) >> 1;
	build(ls, l, m); build(rs, m+1, r);
	addedge(in[p], in[ls], 0); addedge(in[p], in[rs], 0);
	addedge(out[ls], out[p], 0); addedge(out[rs], out[p], 0);
}
void addedgein(int p, int l, int r, int x, int y, int u, int w) {
	if(x <= l && r <= y) {
		addedge(u, in[p], w);
		return ;
	}
	int m = (l + r) >> 1;
	if(x <= m) addedgein(ls, l, m, x, y, u, w);
	if(y > m) addedgein(rs, m+1, r, x, y, u, w);
}
void addedgeout(int p, int l, int r, int x, int y, int v, int w) {
	if(x <= l && r <= y) {
		addedge(out[p], v, w);
		return ;
	}
	int m = (l + r) >> 1;
	if(x <= m) addedgeout(ls, l, m, x, y, v, w);
	if(y > m) addedgeout(rs, m+1, r, x, y, v, w);
}
void bfs(int s) {
	memset(dist, 0x3f, sizeof dist);
	que[hd = tl = MAXNODE] = s; vis[s] = 1; dist[s] = 0;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i];
			if(vis[v]) continue;
			vis[v] = 1;
			if(edg[i] == 0) {
				dist[v] = dist[u];
				que[--hd] = v;
			} else {
				dist[v] = dist[u] + 1;
				que[++tl] = v;
			}
		}
	}
}
int main() {
	n = read(); m = read(); s = read();
	num = n;
	build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		int a = read(), b = read(), c = read(), d = read();
		int x = ++num, y = ++num;
		addedgeout(1, 1, n, a, b, x, 0);
		addedgein(1, 1, n, c, d, y, 0);
		addedge(x, y, 1);
		x = ++num; y = ++num;
		addedgeout(1, 1, n, c, d, x, 0);
		addedgein(1, 1, n, a, b, y, 0);
		addedge(x, y, 1);
	}
	bfs(s);
	for(int i = 1; i <= n; i++) printf("%d\n", dist[i]);

	return 0;
}
