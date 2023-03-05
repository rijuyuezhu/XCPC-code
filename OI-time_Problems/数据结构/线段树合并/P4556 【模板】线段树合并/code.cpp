#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;
const int MAXV = 1e5 + 5;


int n, m;
int head[MAXN], cnt, ver[MAXN * 2], nxt[MAXN * 2];
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}

/*
int mhead[MAXN], mcnt, mnxt[MAXM * 4];
pii mver[MAXM * 4];//c, k
void addmdy(int u, pii v) {
	mver[++mcnt] = v; mnxt[mcnt] = mhead[u]; mhead[u] = mcnt;
}
*/

int fa[MAXN], dep[MAXN], sz[MAXN], son[MAXN];
int top[MAXN];
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; sz[u] = 1; int mxsz = -1;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f) continue;
		dfs1(v, u); sz[u] += sz[v]; if(sz[v] > mxsz) mxsz = sz[v], son[u] = v;
	}
}
void dfs2(int u, int tr) {
	top[u] = tr;
	if(son[u]) dfs2(son[u], tr);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
int lca(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}
void pre() {
	dfs1(1, 0); dfs2(1, 1);
}


namespace SegTree {
	const int MAXNODE = 6e6 + 5;
	#define L e[o].ls
	#define R e[o].rs
	struct Node {
		int ls, rs, val, mt;
	}e[MAXNODE];
	int tot;
	void pushup(int o) {
		e[o].val = max(e[L].val, e[R].val);
		e[o].mt = e[o].val ? (e[L].val >= e[R].val ? e[L].mt : e[R].mt) : 0;//be careful, ">="!!
	}
	void mdypos(int& o, int l, int r, int x, int k) {
		if(!o) e[o = ++tot] = (Node){0, 0, 0, l};
		if(l == r) {e[o].val += k; return ;}
		int m = (l + r) >> 1;
		if(x <= m) mdypos(L, l, m, x, k);
		else mdypos(R, m+1, r, x, k);
		pushup(o);
	}
	int merge(int x, int y, int l, int r) {
		if(!x || !y) return x + y;
		if(l == r) {
			e[x].val += e[y].val;
			return x;
		}
		int m = (l + r) >> 1;
		e[x].ls = merge(e[x].ls, e[y].ls, l, m);
		e[x].rs = merge(e[x].rs, e[y].rs, m+1, r);
		pushup(x);
		return x;
	}//merge y to x;
	#undef L
	#undef R
}
using namespace SegTree;

int ans[MAXN], rt[MAXN]; 
void dfs(int u) {
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == fa[u]) continue;
		dfs(v);
		rt[u] = merge(rt[u], rt[v], 1, MAXV);
	}
	/*for(int i = mhead[u]; i; i = mnxt[i]) {
		pii val = mver[i];
		mdypos(rt[u], 1, MAXV, val.first, val.second);
	}*/
	ans[u] = e[rt[u]].mt;
}

int main() {
	//freopen("code.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	pre();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), val = read();
		int l = lca(u, v);
		/*addmdy(u, pii(val, 1)); addmdy(v, pii(val, 1));
		addmdy(l, pii(val, -1));
		if(fa[l]) addmdy(fa[l], pii(val, -1));
		*/
		mdypos(rt[u], 1, MAXV, val, 1); mdypos(rt[v], 1, MAXV, val, 1);
		mdypos(rt[l], 1, MAXV, val, -1);
		if(fa[l]) mdypos(rt[fa[l]], 1, MAXV, val, -1);
	}
	dfs(1);
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
