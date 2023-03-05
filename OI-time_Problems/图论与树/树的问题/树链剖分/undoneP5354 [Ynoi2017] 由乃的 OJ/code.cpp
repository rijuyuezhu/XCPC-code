#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
ull readu() {
	ull x = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar());
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return x;
}
const int MAXN = 2e5 + 5;
int n, m, k, opt[MAXN], head[MAXN], ver[MAXN], nxt[MAXN], cnt, fa[MAXN], top[MAXN], sz[MAXN], son[MAXN], dep[MAXN], dfn[MAXN], bel[MAXN], tim;
ull val[MAXN], U;
namespace Sgt {
#define ls p << 1
#define rs p << 1 | 1
	struct Val {
		ull a0, a1;
		void apply(int opt, ull v) {
			if(opt == 1) {
				a0 = 0; a1 = v;
			} else if(opt == 2) {
				a0 = v; a1 = U;
			} else {
				a0 = v; a1 = U ^ v;
			}
		}
		void merge(const Val& x, const Val& y) {
			a0 = (~x.a0 & y.a0) | (x.a0 & y.a1);
			a1 = (~x.a1 & y.a0) | (x.a1 & y.a1);
		}
		void setU() {
			a0 = 0; a1 = U;
		}
	};
	struct Node {
		Val f, g;
		//f:left to right(up to down on the tree)
		//g:right to left(down to up on the tree)
		void apply(int opt, ull v) {
			f.apply(opt, v);
			g.apply(opt, v);
		}
		void merge(const Node& a, const Node& b) {
			f.merge(a.f, b.f);
			g.merge(b.g, a.g);
		}
		void setU() {
			f.setU(); g.setU();
		}
	}e[MAXN << 2];
	void build(int p, int l, int r) {
		if(l == r) {
			e[p].apply(opt[bel[l]], val[bel[l]]);
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m); build(rs, m+1, r);
		e[p].merge(e[ls], e[rs]);
	}
	void mdypos(int p, int l, int r, int x, int opt, ull v) {
		if(l == r) {
			e[p].apply(opt, x);
			return ;
		}
		int m = (l + r) >> 1;
		if(x <= m) mdypos(ls, l, m, x, opt, v);
		else mdypos(rs, m+1, r, x, opt, v);
		e[p].merge(e[ls], e[rs]);
	}
	Node qryrange(int p, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[p];
		int m = (l + r) >> 1;
		if(y <= m) return qryrange(ls, l, m, x, y);
		else if(x > m) return qryrange(rs, m+1, r, x, y);
		else {
			Node ans;
			ans.merge(qryrange(ls, l, m, x, m), qryrange(rs, m+1, r, m+1, y));
			return ans;
		}
	}
#undef ls
#undef rs
}
using namespace Sgt;
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; son[u] = 0; sz[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f) continue;
		dfs1(v, u); sz[u] += sz[v]; if(sz[son[u]] < sz[v]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	top[u] = tp; dfn[u] = ++tim; bel[tim] = u;
	if(son[u]) dfs2(son[u], tp);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
int Lca(int u, int v) {
	while(top[u] != top[v]) dep[top[u]] < dep[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
	return dep[u] < dep[v] ? u : v;
}
Node qryto(int u, int f, int t) {//t = 1: include f
	Node ans; ans.setU();
	while(top[u] != top[f]) {
		ans.merge(qryrange(1, 1, n, dfn[top[u]], dfn[u]), ans);
		u = fa[top[u]];
	}
	if(t) ans.merge(qryrange(1, 1, n, dfn[f], dfn[u]), ans);
	else if(u != f)
		ans.merge(qryrange(1, 1, n, dfn[f]+1, dfn[u]), ans);
	return ans;
}
int getbit(ull x, int i) {return (x >> i) & 1;}
int main() {
	n = read(), m = read(), k = read();
	U = (k == 64 ? ~0ull : (1ull << k) - 1);
	for(int i = 1; i <= n; i++) {
		opt[i] = read(); val[i] = readu();
	}
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1);
	build(1, 1, n);
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read(), y = read(); ull z = readu();
		if(opt == 1) {
			int lca = Lca(x, y);
			Node a = qryto(x, lca, 1), b = qryto(y, lca, 0);
			Val ret; ret.merge(a.g, b.f);
			ull ans = 0;
			int lim = 1;
			for(int j = k-1; j >= 0; j--) {
				if(getbit(ret.a0, j) == 1) {// choose 0
					ans |= 1ull << j;
					lim = lim && (getbit(z, j) == 0);
				} else if(getbit(ret.a1, j) == 1 && (!lim || getbit(z, j) == 1)) {//choose 1
					ans |= 1ull << j;
				} else {
					lim = lim && (getbit(z, j) == 0);//choose 0
				}
			}
			printf("%llu\n", ans);
		} else {
			mdypos(1, 1, n, dfn[x], y, z);
		}
	}
	return 0;
}
