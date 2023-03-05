#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e6 + 5, INF = 0x3f3f3f3f;
int n, m, a[MAXN], cnt, head[MAXN];
struct Edge {int v, nxt;}e[MAXN << 1];
void addedge(int u, int v) {e[++cnt] = (Edge){v, head[u]}; head[u] = cnt;}
int dep[MAXN], fa[MAXN], siz[MAXN], son[MAXN];
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; siz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v; if(v == f) continue;
		dfs1(v, u); 
		siz[u] += siz[v]; if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
int top[MAXN], f[MAXN][2], g[MAXN][2];
void dfs2(int u, int tp) {
	top[u] = tp;
	f[u][0] = g[u][0] = 0; f[u][1] = g[u][1] = a[u];
	if(son[u]) {
		dfs2(son[u], tp);
		f[u][0] += max(f[son[u]][0], f[son[u]][1]);
		f[u][1] += f[son[u]][0];
	}
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v; if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
		g[u][0] += max(f[v][0], f[v][1]);
		g[u][1] += f[v][0];
	}
}
struct Matrix {
	int a, b, c, d;
};
Matrix operator * (const Matrix& x, const Matrix& y) {
	Matrix ret;
	ret.a = max(x.a + y.a, x.b + y.c);
	ret.b = max(x.a + y.b, x.b + y.d);
	ret.c = max(x.c + y.a, x.d + y.c);
	ret.d = max(x.c + y.b, x.d + y.d);
	return ret;
}
namespace Bst {
	struct Node {
		int ls, rs, fa;
		Matrix val, sum;
	}t[MAXN];
	int rt;
	void apply(int p) {t[p].val.a = t[p].val.b = g[p][0], t[p].val.c = g[p][1], t[p].val.d = -INF;}
	void upd(int p) {t[p].sum = t[t[p].ls].sum * t[p].val * t[t[p].rs].sum;}
	int nrt(int p) {return p == t[t[p].fa].ls || p == t[t[p].fa].rs;}
	int id[MAXN], _id;
	int build_tree(int l, int r, int f) {
		if(l > r) return 0;
		int ssz = 0, snow = 0;
		for(int i = l; i <= r; i++) ssz += siz[id[i]] - siz[son[id[i]]];
		for(int i = l; i <= r; i++) {
			snow += siz[id[i]] - siz[son[id[i]]];
			if(snow * 2 >= ssz) {
				int p = id[i];
				t[p].ls = build_tree(l, i-1, p);
				t[p].rs = build_tree(i+1, r, p);
				t[p].fa = f;
				apply(p); upd(p);
				return p;
			}
		}
		return -1;
	}
	int build(int tp) {
		for(int u = tp; u; u = son[u]) {
			for(int i = head[u]; i; i = e[i].nxt) {
				int v = e[i].v; if(v == fa[u] || v == son[u]) continue;
				t[build(v)].fa = u;				
			}
		}
		_id = 0;
		for(int u = tp; u; u = son[u]) id[++_id] = u;
		return build_tree(1, _id, 0);
	}
	void mdypnt(int p, int v) {
		g[p][1] += v - a[p];
		a[p] = v;
		for(; p; p = t[p].fa) {
			int bef[2] = {max(t[p].sum.a, t[p].sum.b), max(t[p].sum.c, t[p].sum.d)};
			apply(p); upd(p);
			int aft[2] = {max(t[p].sum.a, t[p].sum.b), max(t[p].sum.c, t[p].sum.d)};
			if(!nrt(p)) {
				g[t[p].fa][0] += max(aft[0], aft[1]) - max(bef[0], bef[1]);
				g[t[p].fa][1] += aft[0] - bef[0];
			}
		}
	}
} using namespace Bst;
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1);
	t[0].val = t[0].sum = (Matrix){0, -INF, -INF, 0};//be care!!!!!
	rt = build(1); int lans = 0;
	for(int i = 1; i <= m; i++) {
		int u = read() ^ lans, v = read();
		mdypnt(u, v);
		Matrix ans = t[rt].sum;
		printf("%d\n", lans = max(max(max(ans.a, ans.b), ans.c), ans.d));
	}
	return 0;
}
