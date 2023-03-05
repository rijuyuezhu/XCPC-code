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
const int MAXN = 2e4 + 5;
const int MAXM = 1e5 + 5;
int n, m, upto[MAXN], num, head[MAXN], val[MAXM], nxt[MAXM], ver[MAXM], cnt;
struct Ed{int u, v, w;}ed[MAXM];
bool operator < (const Ed& a, const Ed& b) {return a.w > b.w;}
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void Kruskal() {
	num = n;
	for(int i = 1; i <= n; i++) upto[i] = i;
	sort(ed + 1, ed + 1 + m);
	for(int i = 1; i <= m; i++) {
		int fu = getup(ed[i].u), fv = getup(ed[i].v);
		if(fu == fv) continue;
		++num; upto[num] = upto[fu] = upto[fv] = num; val[num] = ed[i].w;
		addedge(fu, num); addedge(num, fu);
		addedge(fv, num); addedge(num, fv);
	}
}

int dep[MAXN], fa[MAXN], sz[MAXN], son[MAXN], top[MAXN];
void dfs1(int u, int f) {
	dep[u] = dep[f] + 1; fa[u] = f; sz[u] = 1; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i];	dfs1(v, u);	sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tprt) {
	top[u] = tprt; if(son[u]) dfs2(son[u], tprt);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa[u] && ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v);
	}
}
int lca(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] > dep[v] ? v : u;
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= m; i++) ed[i].u = read(), ed[i].v = read(), ed[i].w = read();
	Kruskal();
	for(int i = 1; i <= num; i++)
		if(!sz[i]) {
			int f = getup(i);
			dfs1(f, 0); dfs2(f, f);
		}
	int q = read();
	while(q--) {
		int u = read(), v = read();
		if(getup(u) != getup(v)) {
			printf("-1\n");
		} else {
			int l = lca(u, v);
			printf("%d\n", val[l]);
		}
	}
	return 0;
}
