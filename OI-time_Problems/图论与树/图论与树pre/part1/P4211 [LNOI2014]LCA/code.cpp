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
const int MAXN = 50005, MAXM = 50005, P = 201314;
int n, q, fa[MAXN], ver[MAXN], nxt[MAXN], cnt, head[MAXN], tot, dfn[MAXN], tim, sz[MAXN], son[MAXN], top[MAXN], dep[MAXN];
ll ans[MAXM];
struct Qry {int u, z, id, k;}qry[MAXM << 1];
bool operator < (const Qry& a, const Qry& b) {return a.u < b.u;}

void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
//Segment_tree
#define ls o << 1
#define rs o << 1 | 1
struct SgtNode {ll v, a;}e[MAXN << 2];
void pushup(int o) {e[o].v = e[ls].v + e[rs].v;}
void addpoint(int o, int l, int r, ll k) {e[o].v += (r-l+1)*k; e[o].a += k;}
void pushdown(int o, int l, int r) {
	if(e[o].a) {
		int m = (l + r) >> 1;
		addpoint(ls, l, m, e[o].a); addpoint(rs, m+1, r, e[o].a);
		e[o].a = 0;
	}
}
void addrange(int o, int l, int r, int x, int y, ll k) {
	if(x <= l && r <= y) {addpoint(o, l, r, k); return ;}
	pushdown(o, l, r);
	int m = (l + r) >> 1;
	if(x <= m) addrange(ls, l, m, x, y, k);
	if(y > m) addrange(rs, m+1, r, x, y, k);
	pushup(o);
}
ll qryrange(int o, int l, int r, int x, int y) {
	if(x <= l && r <= y) return e[o].v;
	pushdown(o, l, r);
	int m = (l + r) >> 1;
	if(y <= m) return qryrange(ls, l, m, x, y);
	else if(x > m) return qryrange(rs, m+1, r, x, y);
	else return qryrange(ls, l, m, x, y) + qryrange(rs, m+1, r, x, y);
}
#undef ls 
#undef rs
//Tree cut
void dfs1(int u) {
	dep[u] = dep[fa[u]] + 1; sz[u] = 1; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; dfs1(v); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tprt) {
	top[u] = tprt; dfn[u] = ++tim; if(son[u]) dfs2(son[u], tprt);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v);
	}
}
void addroute(int u, int v, ll k) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		addrange(1, 1, n, dfn[top[u]], dfn[u], k);
		u = fa[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	addrange(1, 1, n, dfn[v], dfn[u], k);
}
ll qryroute(int u, int v) {
	ll ans = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		ans += qryrange(1, 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	ans += qryrange(1, 1, n, dfn[v], dfn[u]);
	return ans;
}


int main() {
	n = read(); q = read();
	for(int i = 2; i <= n; i++) {
		fa[i] = read()+1; addedge(fa[i], i);//father to son
	}
	for(int i = 1; i <= q; i++) {
		int l = read()+1, r = read()+1, z = read()+1;
		qry[++tot] = (Qry){r, z, i, 1}; 
		if(l != 1) qry[++tot] = (Qry){l-1, z, i, -1};
	}
	sort(qry + 1, qry + 1 + tot);
	dfs1(1); dfs2(1, 1);
	int cur = 1;
	for(int i = 1; i <= n && cur <= tot; i++) {
		addroute(i, 1, 1);
		for(; cur <= tot && qry[cur].u <= i; cur++) {
			ans[qry[cur].id] += qry[cur].k * qryroute(qry[cur].z, 1);
		}
	}
	for(int i = 1; i <= q; i++)
		printf("%lld\n", ans[i] % P);
	return 0;
}
