#include<cstring>
#include<algorithm>
#include<assert.h>
#include<cstdio>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 2e5 + 5, INF = 0x3f3f3f3f;
int n, m, a[MAXN];
struct Edge {int v, nxt;}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {e[++cnt] = (Edge){v, head[u]}; head[u] = cnt;}
int dep[MAXN], siz[MAXN], fa[MAXN], son[MAXN], g[MAXN][2], f[MAXN][2], top[MAXN], len[MAXN], dfn[MAXN], bel[MAXN], tim;
namespace Sgt {
#define ls p << 1
#define rs p << 1 | 1
	struct Node {
		int a, b, c, d;
		void apply(int g0, int g1) {
			a = b = g0; c = g1; d = -INF;
		}
		void merge(const Node& x, const Node& y) {
			a = max(x.a + y.a, x.b + y.c);
			b = max(x.a + y.b, x.b + y.d);
			c = max(x.c + y.a, x.d + y.c);
			d = max(x.c + y.b, x.d + y.d);
		}
	}e[MAXN << 2];
	void build(int p, int l, int r) {
		if(l == r) {
			e[p].apply(g[bel[l]][0], g[bel[l]][1]);
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m); build(rs, m+1, r);
		e[p].merge(e[ls], e[rs]);
	}
	Node query(int p, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[p];
		int m = (l + r) >> 1;
		if(y <= m) return query(ls, l, m, x, y);
		else if(x > m) return query(rs, m+1, r, x, y);
		else {
			Node ans; ans.merge(query(ls, l, m, x, m), query(rs, m+1, r, m+1, y));
			return ans;
		}
	}
	void mdypnt(int p, int l, int r, int x) {
		if(l == r) {
			e[p].apply(g[bel[x]][0], g[bel[x]][1]);
			return ;
		}
		int m = (l + r) >> 1;
		if(x <= m) mdypnt(ls, l, m, x);
		else mdypnt(rs, m+1, r, x);
		e[p].merge(e[ls], e[rs]);
	}
#undef ls
#undef rs
}
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; siz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v; if(v == f) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	dfn[u] = ++tim; bel[tim] = u;
	top[u] = tp; len[tp]++;
	g[u][0] = f[u][0] = 0, g[u][1] = f[u][1] = a[u];
	if(son[u]) {
		dfs2(son[u], tp);
		f[u][0] += max(f[son[u]][0], f[son[u]][1]);
		f[u][1] += f[son[u]][0];
	}
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v; if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
		g[u][0] += max(f[v][0], f[v][1]);
		g[u][1] += f[v][0];
	}
}
void updroute(int u, int v) {
	using namespace Sgt;
	g[u][1] += v - a[u];
	a[u] = v;
	while(u) {
		Node bef = query(1, 1, n, dfn[top[u]], dfn[top[u]] + len[top[u]] - 1);
		mdypnt(1, 1, n, dfn[u]);
		Node aft = query(1, 1, n, dfn[top[u]], dfn[top[u]] + len[top[u]] - 1);
		u = fa[top[u]];
		if(!u) break;
		g[u][0] += max(aft.a, aft.c) - max(bef.a, bef.c);
		g[u][1] += aft.a - bef.a;
	}
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1); Sgt::build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		int x = read(), y = read();
		updroute(x, y);
		Sgt::Node ans = Sgt::query(1, 1, n, dfn[1], dfn[1] + len[1] - 1);
		printf("%d\n", max(ans.a, ans.c));
	}
	return 0;
}
