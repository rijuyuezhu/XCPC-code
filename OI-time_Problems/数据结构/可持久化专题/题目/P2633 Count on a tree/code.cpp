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
int n, m, a[MAXN], lans, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt;
int dep[MAXN], fa[MAXN], sz[MAXN], son[MAXN], top[MAXN], rt[MAXN], lsh[MAXN], tot; 
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void LSH() {
	sort(lsh + 1, lsh + 1 + tot);
	tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}
namespace Sgt {
	int tot;
	struct Node{int ls, rs, sz;}e[MAXN << 5];
	void mdypos(int& p, int pre, int l, int r, int x) {
		p = ++tot; e[p] = e[pre]; e[p].sz++;
		if(l == r) return ;
		int m = (l + r) >> 1;
		if(x <= m) mdypos(e[p].ls, e[pre].ls, l, m, x);
		else mdypos(e[p].rs, e[pre].rs, m+1, r, x);
	}
	int calc(int a, int b, int c, int d) {return e[a].sz + e[b].sz - e[c].sz - e[d].sz;}
	int qry(int a, int b, int c, int d, int l, int r, int k) {
		if(l == r) return l;
		int m = (l + r) >> 1, val = calc(e[a].ls, e[b].ls, e[c].ls, e[d].ls);
		if(k <= val) return qry(e[a].ls, e[b].ls, e[c].ls, e[d].ls, l, m, k);
		else return qry(e[a].rs, e[b].rs, e[c].rs, e[d].rs, m+1, r, k - val);
	}
}
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; sz[u] = 1; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i]; dfs1(v, u); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	top[u] = tp; Sgt::mdypos(rt[u], rt[fa[u]], 1, n, LSH(a[u]));
	if(son[u]) dfs2(son[u], tp);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa[u] && ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v);
	}
}
int Lca(int u, int v) {
	while(top[u] != top[v]) dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
	return dep[u] > dep[v] ? v : u;
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) a[i] = lsh[++tot] = read();
	LSH();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1);
	for(int i = 1; i <= m; i++) {
		int u = read() ^ lans, v = read(), k = read(), lca = Lca(u, v);
		printf("%d\n", lans = lsh[Sgt::qry(rt[u], rt[v], rt[lca], rt[fa[lca]], 1, n, k)]);
	}
	return 0;
}
