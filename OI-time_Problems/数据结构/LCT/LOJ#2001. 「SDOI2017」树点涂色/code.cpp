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
int n, m, head[MAXN], ver[MAXN], nxt[MAXN], cnt;
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
namespace Tree {
	int sz[MAXN], fa[MAXN], dep[MAXN], top[MAXN], son[MAXN], dfn[MAXN], bel[MAXN], tim;
	void dfs1(int u, int f) {
		fa[u] = f; dep[u] = dep[f] + 1; sz[u] = 1; son[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i]; if(v == f) continue;
			dfs1(v, u); sz[u] += sz[v]; if(sz[v] > sz[son[u]]) son[u] = v;
		}
	}
	void dfs2(int u, int tp) {
		dfn[u] = ++tim; bel[tim] = u; top[u] = tp; if(son[u]) dfs2(son[u], tp);
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i]; if(v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	int Lca(int u, int v) {
		while(top[u] != top[v]) dep[top[u]] < dep[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
		return dep[u] < dep[v] ? u : v;
	}
}
using namespace Tree;
namespace Sgt {
	#define ls p << 1
	#define rs p << 1 | 1
	struct Node {int v, a;}e[MAXN << 2];
	void upd(int p) {e[p].v = max(e[ls].v, e[rs].v);}
	void build(int p, int l, int r) {
		e[p].a = 0;
		if(l == r) {
			e[p].v = dep[bel[l]];
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m); build(rs, m+1, r);
		upd(p);
	}
	void psdadd(int p, int v) {
		e[p].a += v; e[p].v += v;
	}
	void psd(int p) {
		if(e[p].a) {
			psdadd(ls, e[p].a);
			psdadd(rs, e[p].a);
			e[p].a = 0;
		}
	}
	void addrange(int p, int l, int r, int x, int y, int v) {
		if(x <= l && r <= y) {
			psdadd(p, v);
			return ;
		}
		psd(p);
		int m = (l + r) >> 1;
		if(x <= m) addrange(ls, l, m, x, y, v);
		if(y > m) addrange(rs, m+1, r, x, y, v);
		upd(p);
	}
	int qryrange(int p, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[p].v;
		psd(p);
		int m = (l + r) >> 1;
		if(y <= m) return qryrange(ls, l, m, x, y);
		else if(x > m) return qryrange(rs, m+1, r, x, y);
		else return max(qryrange(ls, l, m, x, m), qryrange(rs, m+1, r, m+1, y));
	}
	#undef ls
	#undef rs
}
namespace Lct {
	#define ls ch[0]
	#define rs ch[1]
	struct Node{int ch[2], fa;}e[MAXN];
	void init() {
		for(int i = 1; i <= n; i++) e[i] = (Node){{0, 0}, fa[i]};
	}
	int nrt(int p) {return p == e[e[p].fa].ls || p == e[e[p].fa].rs;}
	int idy(int p) {return p == e[e[p].fa].rs;}
	void rtt(int p) {
		int y = e[p].fa, z = e[y].fa, k = idy(p), s = e[p].ch[k^1];
		e[p].fa = z; if(nrt(y)) e[z].ch[idy(y)] = p;
		e[y].fa = p; e[p].ch[k^1] = y;
		e[s].fa = y; e[y].ch[k] = s;
	}
	void splay(int p) {
		for(int y = e[p].fa; nrt(p); rtt(p), y = e[p].fa)
			if(nrt(y)) rtt(idy(p) == idy(y) ? y : p);
	}
	int getrt(int p) {while(e[p].ls) p = e[p].ls; return p;}
	void access(int p) {
		for(int y = 0; p; y = p, p = e[p].fa) {
			splay(p);
			if(e[p].rs) {
				int u = getrt(e[p].rs);
				Sgt::addrange(1, 1, n, dfn[u], dfn[u] + sz[u] - 1, 1);
			} 
			e[p].rs = y;
			if(e[p].rs) {
				int u = getrt(e[p].rs);
				Sgt::addrange(1, 1, n, dfn[u], dfn[u] + sz[u] - 1, -1);
			}
		}
	}
	#undef ls
	#undef rs
}
int main() {
	n = read(); m = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v);
		addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1);
	Sgt::build(1, 1, n);
	Lct::init();
	for(int i = 1; i <= m; i++) {
		int opt = read();
		if(opt == 1) {
			int x = read();
			Lct::access(x);
		} else if(opt == 2) {
			int x = read(), y = read(), l = Lca(x, y);
			printf("%d\n", Sgt::qryrange(1, 1, n, dfn[x], dfn[x]) + Sgt::qryrange(1, 1, n, dfn[y], dfn[y]) - 2 * Sgt::qryrange(1, 1, n, dfn[l], dfn[l]) + 1);
		} else {
			int x = read();
			printf("%d\n", Sgt::qryrange(1, 1, n, dfn[x], dfn[x] + sz[x] - 1));
		}
		//printf("print:\n");
		//for(int j = 1; j <= n; j++) printf("%d ", Sgt::qryrange(1, 1, n, dfn[j], dfn[j]));
		//printf("\n");
	}
	return 0;
}
