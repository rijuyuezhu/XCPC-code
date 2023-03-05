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
char readc() {
	char ch = getchar();
	for(; ch != 'C' && ch != 'Q'; ch = getchar());
	return ch;
}
const int MAXN = 1e5 + 5;
int n, m, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt;
int w1[MAXN], fa[MAXN], son[MAXN], sz[MAXN], dep[MAXN], top[MAXN], dfn[MAXN], tim, w2[MAXN];

void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
namespace Sgt {
	#define ls p << 1
	#define rs p << 1 | 1
	struct Node {
		int lc, rc, cnt, tag;
		void upd(Node a, Node b) {
			lc = a.lc; rc = b.rc;
			cnt = a.cnt + b.cnt - (a.rc == b.lc);
		}
	}e[MAXN << 2];
	void psdtag(int p, int c) {
		e[p].lc = e[p].rc = e[p].tag = c;
		e[p].cnt = 1;
	}
	void psd(int p) {
		if(e[p].tag) {
			psdtag(ls, e[p].tag); psdtag(rs, e[p].tag);
			e[p].tag = 0;
		}
	}
	void build(int p, int l, int r, int col[]) {
		if(l == r) {
			e[p].lc = e[p].rc = col[l]; e[p].cnt = 1;
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, col); build(rs, m+1, r, col);
		e[p].upd(e[ls], e[rs]);
	}
	void mdyrange(int p, int l, int r, int x, int y, int c) {
		if(x <= l && r <= y) {psdtag(p, c); return ;}
		psd(p);
		int m = (l + r) >> 1;
		if(x <= m) mdyrange(ls, l, m, x, y, c);
		if(y > m) mdyrange(rs, m+1, r, x, y, c);
		e[p].upd(e[ls], e[rs]);
	}
	Node qryrange(int p, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[p];
		psd(p);
		int m = (l + r) >> 1;
		if(y <= m) return qryrange(ls, l, m, x, y);
		else if(x > m) return qryrange(rs, m+1, r, x, y);
		else {
			Node ans; ans.upd(qryrange(ls, l, m, x, y), qryrange(rs, m+1, r, x, y));
			return ans;
		}
	}
	#undef L
	#undef R
}
using namespace Sgt;
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; sz[u] = 1; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i]; dfs1(v, u); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	top[u] = tp; dfn[u] = ++tim; w2[tim] = w1[u];
	if(son[u]) dfs2(son[u], tp);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa[u] && ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v); 
	}
}
int Lca(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}
void mdyto(int u, int lca, int c, int k) {
	while(top[u] != top[lca]) {
		mdyrange(1, 1, n, dfn[top[u]], dfn[u], c);
		u = fa[top[u]];
	}
	if(k == 1) mdyrange(1, 1, n, dfn[lca], dfn[u], c);
	else {
		if(u != lca) mdyrange(1, 1, n, dfn[lca]+1, dfn[u], c);
	}
}
Node qryto(int u, int lca, int k) {
	Node ans = {0};
	while(top[u] != top[lca]) {
		ans.upd(qryrange(1, 1, n, dfn[top[u]], dfn[u]), ans);
		u = fa[top[u]];
	}
	if(k == 1) ans.upd(qryrange(1, 1, n, dfn[lca], dfn[u]), ans);
	else {
		if(u != lca) ans.upd(qryrange(1, 1, n, dfn[lca]+1, dfn[u]), ans);
	}
	return ans;
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) w1[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1); build(1, 1, n, w2);
	for(int i = 1; i <= m; i++) {
		char opt = readc();
		if(opt == 'C') {
			int a = read(), b = read(), c = read(), lca = Lca(a, b);
			mdyto(a, lca, c, 1); mdyto(b, lca, c, 0);
		} else {
			int a = read(), b = read(), lca = Lca(a, b);
			Node ans1 = qryto(a, lca, 1), ans2 = qryto(b, lca, 0);
			printf("%d\n", ans1.cnt + ans2.cnt - (ans1.lc == ans2.lc));
		}
	}
	return 0;
}
