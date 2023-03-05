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
const int MAXN = 2.5e5 + 5;
const int MAXK = 5e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
struct Graph {
	int head[MAXN], ver[MAXN*2], nxt[MAXN*2], cnt;
	ll edg[MAXN*2];
	void addedge(int u, int v, ll w = 0) {
		ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
	}
}g1, g2;
int n, m, sz[MAXN], dfn[MAXN], tim, dep[MAXN], top[MAXN], fa[MAXN], son[MAXN], K, h[MAXN], stk[MAXN], stp, fl[MAXN];
ll wei[MAXN];
void dfs1(int u, int f) {
	sz[u] = 1; dep[u] = dep[f] + 1; fa[u] = f; son[u] = 0;
	for(int i = g1.head[u]; i; i = g1.nxt[i]) {
		int v = g1.ver[i]; if(v == f) continue;
		wei[v] = min(wei[u], g1.edg[i]);
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
	while(stp > 1 && dfn[stk[stp-1]] >= dfn[lca]) g2.addedge(stk[stp-1], stk[stp]), stp--;
	if(lca != stk[stp]) g2.addedge(lca, stk[stp]), stk[stp] = lca;
	stk[++stp] = u;
}
ll dp(int u) {
	if(fl[u]) return wei[u];
	ll sum = 0;
	for(int i = g2.head[u]; i; i = g2.nxt[i]) sum += dp(g2.ver[i]);
	return min(wei[u], sum);
}
void clr_tree(int u) {
	for(int i = g2.head[u]; i; i = g2.nxt[i]) clr_tree(g2.ver[i]);
	fl[u] = 0; g2.head[u] = 0;
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(); ll w = read();
		g1.addedge(u, v, w); g1.addedge(v, u, w);
	}
	wei[1] = INF;
	dfs1(1, 0); dfs2(1, 1);
	int m = read();
	while(m--) {
		K = read();
		for(int i = 1; i <= K; i++) h[i] = read(), fl[h[i]] = 1;
		sort(h + 1, h + 1 + K, cmp);
		stk[stp = 1] = 1;
		for(int i = 1; i <= K; i++) if(h[i] != 1) ins_tree(h[i]);
		while(stp > 0) g2.addedge(stk[stp-1], stk[stp]), stp--;
		printf("%lld\n", dp(1)); clr_tree(1); g2.cnt = 0;
	}
	return 0;
}
