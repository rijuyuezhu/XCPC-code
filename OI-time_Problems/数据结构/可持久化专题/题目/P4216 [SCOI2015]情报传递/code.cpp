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
const int MAXQ = 2e5 + 5;
const int INF = 0x3f3f3f3f;
int n, fa[MAXN], rt, ver[MAXN], nxt[MAXN], cnt, head[MAXN], dep[MAXN], sz[MAXN], son[MAXN], top[MAXN], q, sgt[MAXN], val[MAXN], tot;
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
struct Node {int ls, rs, sz;}e[MAXQ << 5];
struct Qry {int k, x, y, c;}qry[MAXQ];
void mdypos(int& p, int pre, int l, int r, int x) {
	p = ++tot; e[p] = e[pre]; e[p].sz++;
	if(l == r) return;
	int m = (l + r) >> 1;
	if(x <= m) mdypos(e[p].ls, e[pre].ls, l, m, x);
	else mdypos(e[p].rs, e[pre].rs, m+1, r, x);
}
int qryrange(int p, int l, int r, int x, int y) {
	if(x <= l && r <= y) return e[p].sz;
	int m = (l + r) >> 1;
	if(y <= m) return qryrange(e[p].ls, l, m, x, y);
	else if(x > m) return qryrange(e[p].rs, m+1, r, x, y);
	else return qryrange(e[p].ls, l, m, x, y) + qryrange(e[p].rs, m+1, r, x, y);
}
void dfs1(int u) {
	dep[u] = dep[fa[u]] + 1; sz[u] = 1; son[u] = 0;
	if(val[u]) mdypos(sgt[u], sgt[fa[u]], 1, q, val[u]);
	else sgt[u] = sgt[fa[u]];
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; dfs1(v); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tprt) {
	top[u] = tprt;
	if(son[u]) dfs2(son[u], tprt);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != son[u]) dfs2(ver[i], ver[i]);
}
int Lca(int u, int v) {
	while(top[u] != top[v]) dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
	return dep[u] > dep[v] ? v : u;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		fa[i] = read(); 
		if(fa[i] == 0) rt = i;
		else addedge(fa[i], i);
	}
	q = read();
	for(int i = 1; i <= q; i++) {
		int k = qry[i].k = read();
		if(k == 1) {
			qry[i].x = read(), qry[i].y = read(), qry[i].c = read();
		} else {
			int t = read();
			if(!val[t]) val[t] = i;
		}
	}
	dfs1(rt); dfs2(rt, rt);
	for(int i = 1; i <= q; i++) if(qry[i].k == 1) {
		int u = qry[i].x, v = qry[i].y, c = qry[i].c, lca = Lca(u, v);
		printf("%d ", dep[u] + dep[v] - dep[lca] - dep[fa[lca]]);
		if(i-c-1 < 1) printf("0\n");
		else printf("%d\n", qryrange(sgt[u], 1, q, 1, i-c-1) + qryrange(sgt[v], 1, q, 1, i-c-1) - qryrange(sgt[lca], 1, q, 1, i-c-1) - qryrange(sgt[fa[lca]], 1, q, 1, i-c-1));
	}
	return 0;
}
