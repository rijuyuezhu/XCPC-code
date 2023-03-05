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
const int MAXN = 30005;
const int MAXM = 60005;
int n, m, k, num, upto[MAXN], val[MAXN], head[MAXN], ver[MAXM], nxt[MAXM], cnt, dep[MAXN], sz[MAXN], fa[MAXN], son[MAXN], top[MAXN];
struct Edge {int u, v, w;}e[MAXM];
bool cmp(const Edge& a, const Edge& b) {return a.w < b.w;}
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
void addedge(int u, int v) {ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;}
void Kruskal() {
	num = n;
	sort(e + 1, e + 1 + m, cmp);
	for(int i = 1; i <= n; i++) upto[i] = i;
	for(int i = 1; i <= m; i++) {
		int fu = getup(e[i].u), fv = getup(e[i].v);
		if(fu == fv) continue;
		val[++num] = e[i].w; upto[num] = upto[fu] = upto[fv] = num;
		addedge(fu, num); addedge(num, fu); addedge(fv, num); addedge(num, fv);
	}
}
void dfs1(int u, int f) {
	dep[u] = dep[f] + 1; sz[u] = 1; fa[u] = f; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i]; dfs1(v, u); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tprt) {
	top[u] = tprt; if(son[u]) dfs2(son[u], tprt);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa[u] && ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v);
	}
}
int Lca(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] > dep[v] ? v : u;
}
int main() {
	n = read(); m = read(); k = read();
	for(int i = 1; i <= m; i++) e[i].u = read(), e[i].v = read(), e[i].w = read();
	Kruskal();
	int rt = getup(1);
	dfs1(rt, 0); dfs2(rt, rt);
	for(int i = 1; i <= k; i++) {
		int a = read(), b = read();
		printf("%d\n", val[Lca(a, b)]);
	}
	return 0;
}
