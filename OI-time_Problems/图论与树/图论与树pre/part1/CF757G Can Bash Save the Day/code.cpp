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

const int MAXN = 2e5 + 5;
const int MAXNODE = 3e7;
int n, q, a[MAXN], head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, dep[MAXN], fa[MAXN], sz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], tim;
ll edg[MAXN << 1], dist[MAXN], suma[MAXN], sw[MAXN], ew[MAXN];
void addedge(int u, int v, ll w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}

void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; son[u] = 0; sz[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i]; 
		dist[v] = dist[u] + edg[i]; ew[v] = edg[i]; dfs1(v, u); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tprt) {
	top[u] = tprt; dfn[u] = ++tim; sw[tim] = sw[tim-1] + ew[u]; if(son[u]) dfs2(son[u], tprt);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa[u] && ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v);
	}
}

int tot, limtot, rt[MAXN];
struct SgtNode {ll v, a; int ls, rs;}e[MAXNODE];
void addrange(int &o, int pre, int l, int r, int x, int y) {
	if(pre <= limtot) o = ++tot, e[o] = e[pre];
	else o = pre;
	if(x <= l && r <= y) {e[o].a ++; e[o].v += sw[r] - sw[l-1]; return;}
	int m = (l + r) >> 1;
	if(x <= m) addrange(e[o].ls, e[pre].ls, l, m, x, y);
	if(y > m) addrange(e[o].rs, e[pre].rs, m+1, r, x, y);
	e[o].v = e[e[o].ls].v + e[e[o].rs].v + e[o].a * (sw[r] - sw[l-1]);
}
ll qryrange(int o, int l, int r, int x, int y) {
	if(x <= l && r <= y) return e[o].v;
	int m = (l + r) >> 1; ll ans = e[o].a * (sw[y] - sw[x-1]);
	if(y <= m) return ans + qryrange(e[o].ls, l, m, x, y);
	else if(x > m) return ans + qryrange(e[o].rs, m+1, r, x, y);
	else return ans + qryrange(e[o].ls, l, m, x, m) + qryrange(e[o].rs, m+1, r, m+1, y);
}
void addroute(int vs, int u, int v, ll k) {
	limtot = tot;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		addrange(rt[vs], rt[vs], 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if(u != v) {
		if(dep[u] > dep[v]) swap(u, v);
		addrange(rt[vs], rt[vs], 1, n, dfn[u]+1, dfn[v]);
	}
}
ll qryroute(int vs, int u, int v) {
	ll ans = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		ans += qryrange(rt[vs], 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if(u != v) {
		if(dep[u] > dep[v]) swap(u, v);
		ans += qryrange(rt[vs], 1, n, dfn[u]+1, dfn[v]);
	}
	return ans;
}

ll lans;
ll getval(ll a) {return (lans % (1 << 30ll)) ^ a;}
ll calc(int vs, int v) {
	return suma[vs] + vs * dist[v] - 2 * qryroute(vs, v, 1);
}
int main() {
	n = read(); q = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(); ll w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	dfs1(1, 0); dfs2(1, 1);
	for(int i = 1; i <= n; i++) suma[i] = suma[i-1] + dist[a[i]];
	for(int i = 1; i <= n; i++) {
		rt[i] = rt[i-1]; 
		addroute(i, a[i], 1, dist[a[i]]);
	}
	for(int i = 1; i <= q; i++) {
		int t = read();
		if(t == 1) {
			int l = getval(read()), r = getval(read()), v = getval(read());
			printf("%lld\n", lans = calc(r, v) - calc(l-1, v));
		} else {
			int x = getval(read());
			swap(a[x], a[x+1]); suma[x] = suma[x-1] + dist[a[x]];
			if(tot < 2.7e7) {
				rt[x] = rt[x-1]; addroute(x, a[x], 1, dist[a[x]]);
			} else {
				tot = 0;
				for(int i = 1; i <= n; i++) {
					rt[i] = rt[i-1];
					addroute(i, a[i], 1, dist[a[i]]);
				}
			}
		}
	}
	return 0;
}
