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
const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;
const ll INF = 123456789123456789ll;
int n, m, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, dep[MAXN], fa[MAXN], son[MAXN], sz[MAXN], top[MAXN], dfn[MAXN], bel[MAXN], tim;
ll edg[MAXN << 1], dist[MAXN];
void addedge(int u, int v, ll w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; sz[u] = 1; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i]; dist[v] = dist[u] + edg[i];
		dfs1(v, u); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tprt) {
	top[u] = tprt; dfn[u] = ++tim; bel[tim] = u; if(son[u]) dfs2(son[u], tprt);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa[u] && ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v);
	}
}
int Lca(int u, int v) {
	while(top[u] != top[v]) dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
	return dep[u] > dep[v] ? v : u;
}
#define ls p << 1
#define rs p << 1 | 1
struct Line {ll k, b;}li[MAXM << 5];
int tot, mn[MAXN << 2];
ll val[MAXN << 2];
void upd(int p) {val[p] = min(val[p], min(val[ls], val[rs]));}
ll calc(int id, int i) {return li[id].k * dist[bel[i]] + li[id].b;}
void build(int p, int l, int r) {
	mn[p] = 0; val[p] = min(calc(mn[p], l), calc(mn[p], r));
	if(l == r) return ;
	int m = (l + r) >> 1;
	build(ls, l, m); build(rs, m+1, r);
	upd(p);
}

void mdyrange(int p, int l, int r, int x, int y, int k) {
	if(x <= l && r <= y) {
		val[p] = min(val[p], min(calc(k, l), calc(k, r)));
		ll l1 = calc(k, l), l2 = calc(mn[p], l);
		ll r1 = calc(k, r), r2 = calc(mn[p], r);
		if(l1 <= l2 && r1 <= r2) {mn[p] = k; return;}
		if(l1 >= l2 && r1 >= r2) return ;
		int m = (l + r) >> 1;
		if(calc(k, m) < calc(mn[p], m)) swap(k, mn[p]);
		if(calc(k, l) < calc(mn[p], l)) mdyrange(ls, l, m, x, y, k);
		else mdyrange(rs, m+1, r, x, y, k);
		upd(p);
		return ;
	}
	int m = (l + r) >> 1;
	if(x <= m) mdyrange(ls, l, m, x, y, k);
	if(y > m) mdyrange(rs, m+1, r, x, y, k);
	upd(p);
}
ll qryrange(int p, int l, int r, int x, int y) {
	if(x <= l && r <= y) return val[p];
	int m = (l + r) >> 1;
	ll ans = min(calc(mn[p], x), calc(mn[p], y));
	if(y <= m) return min(ans, qryrange(ls, l, m, x, y));
	else if(x > m) return min(ans, qryrange(rs, m+1, r, x, y));
	else return min(ans, min(qryrange(ls, l, m, x, m), qryrange(rs, m+1, r, m+1, y)));
}
void mdyto(int u, int lca, int k) {
	while(top[u] != top[lca]) {
		mdyrange(1, 1, n, dfn[top[u]], dfn[u], k);
		u = fa[top[u]];
	}
	mdyrange(1, 1, n, dfn[lca], dfn[u], k);
}
ll qryto(int u, int lca) {
	ll ans = INF;
	while(top[u] != top[lca]) {
		ans = min(ans, qryrange(1, 1, n, dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	return min(ans, qryrange(1, 1, n, dfn[lca], dfn[u]));
}
#undef ls
#undef rs
int main() {
	n = read(); m = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(); ll w = read();
		addedge(u, v, w);
		addedge(v, u, w);
	}
	li[0] = Line{0, INF};
	dfs1(1, 0); dfs2(1, 1); build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		int opt = read();
		if(opt == 1) {
			int s = read(), t = read(), lca = Lca(s, t);
			ll a = read(), b = read();
			li[++tot] = (Line){-a, b + a * dist[s]};
			mdyto(s, lca, tot);
			li[++tot] = (Line){a, a * dist[s] - 2 * a * dist[lca] + b};
			mdyto(t, lca, tot);
		} else {
			int s = read(), t = read(), lca = Lca(s, t);
			printf("%lld\n", min(qryto(s, lca), qryto(t, lca)));
		}
	}
	return 0;
}
