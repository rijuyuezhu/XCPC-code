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

const int MAXN = 1e6 + 5;
const ll INF = 1e16;
int n, fa[MAXN], dep[MAXN], son[MAXN], sz[MAXN], top[MAXN], dfn[MAXN], tim, siz[MAXN], h[MAXN], K, stk[MAXN], stp;
ll ansd, mind, maxd, dist[MAXN], mn[MAXN], mx[MAXN];
struct Graph {
	int head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt;
	void addedge(int u, int v) {
		ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
	}
}g1, g2;
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; sz[u] = 1; son[u] = 0;
	for(int i = g1.head[u]; i; i = g1.nxt[i]) {
		int v = g1.ver[i]; if(v == f) continue;
		dfs1(v, u); sz[u] += sz[v]; 
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	dfn[u] = ++tim; top[u] = tp; if(son[u]) dfs2(son[u], tp);
	for(int i = g1.head[u]; i; i = g1.nxt[i]) {
		int v = g1.ver[i]; if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
int Lca(int u, int v) {
	while(top[u] != top[v]) dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
	return dep[u] > dep[v] ? v : u;
}
bool cmp(int a, int b) {return dfn[a] < dfn[b];}
void ins_tree(int u) {
	int lca = Lca(u, stk[stp]);
	while(stp > 1 && dfn[lca] <= dfn[stk[stp-1]]) g2.addedge(stk[stp-1], stk[stp]), stp--;
	if(lca != stk[stp]) g2.addedge(lca, stk[stp]), stk[stp] = lca;
	stk[++stp] = u;
}
void dfs3(int u) {
	dist[u] = 0; mn[u] = siz[u] ? 0 : INF; mx[u] = siz[u] ? 0 : -INF;
	for(int i = g2.head[u]; i; i = g2.nxt[i]) {
		int v = g2.ver[i]; dfs3(v);
		ll d = dep[v] - dep[u];
		ansd += dist[u] * siz[v] + d * siz[u] * siz[v] + dist[v] * siz[u];
		mind = min(mind, mn[u] + mn[v] + d);
		maxd = max(maxd, mx[u] + mx[v] + d);
		siz[u] += siz[v];
		dist[u] += dist[v] + d * siz[v];
		mn[u] = min(mn[u], mn[v] + d);
		mx[u] = max(mx[u], mx[v] + d);
	}
}
void del_tree(int u) {
	for(int i = g2.head[u]; i; i = g2.nxt[i]) del_tree(g2.ver[i]);
	g2.head[u] = 0; siz[u] = 0;
}
int main() {
	n = read(); 
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		g1.addedge(u, v); g1.addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1);
	int q = read();
	while(q--) {
		K = read();
		for(int i = 1; i <= K; i++) h[i] = read(), siz[h[i]] = 1;
		sort(h + 1, h + 1 + K, cmp);

		stk[stp = 1] = 1;
		for(int i = 1; i <= K; i++) if(h[i] != 1) ins_tree(h[i]);
		while(stp > 1) g2.addedge(stk[stp-1], stk[stp]), stp--;
		
		ansd = 0; mind = INF; maxd = -INF;
		dfs3(1);
		printf("%lld %lld %lld\n", ansd, mind, maxd);
		del_tree(1); g2.cnt = 0;
	}
	return 0;
}
