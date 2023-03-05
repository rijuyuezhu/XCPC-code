#include<cstring>
#include<algorithm>
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
const int MAXN = 2e5 + 5;
int ty, n, q, pm[MAXN];
struct Edge {int v, nxt; ll w;}e[MAXN << 1];
int cnt, head[MAXN], dfn[MAXN], ardfn[MAXN], _dfn, siz[MAXN], fa[MAXN], dep[MAXN], top[MAXN], son[MAXN]; 
ll dist[MAXN], spd[MAXN];
int rt[MAXN];
namespace Sgt {
	int lim, tot;
	struct Node {int ls, rs, a; ll v;} t[20000005];//check the memory!
	ll Dist(int l, int r) {return dist[ardfn[r]] - dist[fa[ardfn[l]]];}
	void upd(int p, int l, int r) {t[p].v = t[t[p].ls].v + t[t[p].rs].v + Dist(l, r) * t[p].a;}
	void setlim() {lim = tot;}
	void addrange(int& p, int l, int r, int x, int y) {
		if(p <= lim) {int pre = p; t[p = ++tot] = t[pre];}
		if(x == l && r == y) {
			t[p].a++; t[p].v += Dist(l, r);
			return ;
		}
		int m = (l + r) >> 1;
		if(y <= m) addrange(t[p].ls, l, m, x, y);
		else if(x > m) addrange(t[p].rs, m+1, r, x, y);
		else addrange(t[p].ls, l, m, x, m), addrange(t[p].rs, m+1, r, m+1, y);
		upd(p, l, r);
	}
	ll query(int p, int l, int r, int x, int y) {
		if(!p) return 0;
		if(x == l && r == y) return t[p].v;
		int m = (l + r) >> 1; ll ans = Dist(x, y) * t[p].a;
		if(y <= m) return ans + query(t[p].ls, l, m, x, y);
		else if(x > m) return ans + query(t[p].rs, m+1, r, x, y);
		else return ans + query(t[p].ls, l, m, x, m) + query(t[p].rs, m+1, r, m+1, y);
	}
} using namespace Sgt;
namespace Graph {
	void addedge(int u, int v, ll w) {
		e[++cnt] = (Edge){v, head[u], w}; head[u] = cnt;
	}
	void dfs1(int u, int f) {
		dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v; if(v == f) continue;
			dist[v] = dist[u] + e[i].w;
			dfs1(v, u); siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		}
	}
	void dfs2(int u, int tp) {
		top[u] = tp; dfn[u] = ++_dfn, ardfn[_dfn] = u;
		if(son[u]) dfs2(son[u], tp);
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v; if(v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	int Lca(int u, int v) {
		while(top[u] != top[v]) dep[top[u]] < dep[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
		return dep[u] < dep[v] ? u : v;
	}
	void addpath(int u, int& Rt) {
		setlim();
		while(u) {
			addrange(Rt, 1, n, dfn[top[u]], dfn[u]);
			u = fa[top[u]];
		}
	}
	ll querypath(int u, int Rt) {
		ll ans = 0;
		while(u) {
			ans += query(Rt, 1, n, dfn[top[u]], dfn[u]);
			u = fa[top[u]];
		}
		return ans;
	}
	void dfs3(int u) {
		rt[u] = rt[fa[u]]; addpath(pm[u], rt[u]); 
		spd[u] = spd[fa[u]] + dist[pm[u]];
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v; if(v == fa[u]) continue;
			dfs3(v);
		}
	}
	ll getans(int u, int k) {
		return spd[u] + dep[u] * dist[k] - 2 * querypath(k, rt[u]);
	}
} using namespace Graph;
int main() {
	ty = read();
	n = read(), q = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(); ll w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	for(int i = 1; i <= n; i++) pm[i] = read();
	dfs1(1, 0); dfs2(1, 1); dfs3(1);
	ll ans = 0;
	for(int i = 1; i <= q; i++) {
		int u = read() ^ (ans * ty), v = read() ^ (ans * ty), k = read() ^ (ans * ty), lca = Lca(u, v);
		ans = getans(u, k) + getans(v, k) - getans(lca, k) - getans(fa[lca], k);
		printf("%lld\n", ans);
	}
	return 0;
}
