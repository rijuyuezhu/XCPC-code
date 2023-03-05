# P4211 [LNOI2014]LCA & CF757G Can Bash Save the Day? 解题报告

这两道题很有代表性，代表了一种有关lca问题的解法。

## P4211 [LNOI2014]LCA

[链接](https://www.luogu.com.cn/problem/P4211)

题意很清晰，就不转化了。

要求 $\sum_{i=l}^r\mathrm{dep}[\mathrm{lca}(i,z)]$，考虑差分。只要能求 $\sum_{i=1}^x\mathrm{dep}[\mathrm{lca}(i,z)]$ 就行了。

这里用到一个非常巧妙的转化， **lca的深度就是两点到根的重叠部分的长度**。于是，只要将 1 ~ $x$ 到根的路径全部加1，再查询 $z$ 到根的路径上的值即可。这可以用树链剖分完成。

只要离散+树剖线段树维护即可。

```cpp
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
```

## CF757G Can Bash Save the Day

[链接](https://www.luogu.com.cn/problem/CF757G)

一棵 $n$ 个点的树和一个排列 $p_i$，边有边权，支持两种操作：

- `l r x`，询问 $\sum\limits_{i=l}^{r} dis(p_i,x)$。
- `x`，交换 $p_x,p_{x+1}$
- $n,q\le 2\times 10^5$，强制在线。

（题目描述摘自洛谷）

其实这道题和上道题没有太大区别，只是上道题可以离散化，这道题强制在线。

设 $Dis(x)$ 表示 $x$ 到根的距离。这里的根可以随意定。

依然考虑差分，则

 $$\sum\limits_{i=1}^tdis(p_i,x)=\sum\limits_{i=1}^t[Dis(p_i)+Dis(x)-2\cdot Dis(\mathrm{lca}(p_i,x))]$$

$$=\sum\limits_{i=1}^tDis(p_i)+t\cdot Dis(x)-2\sum\limits_{i=1}^tDis(lca(p_i, x))$$

第一项可以前缀和维护，第二项可以直接 $O(1)$ 算出，而第三项可以用类似于上题的方法得到。但是要用可持久化线段树维护。

```cpp
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
const int MAXNODE = 3e7;
int n, q, a[MAXN], head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, dep[MAXN], fa[MAXN], sz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], tim;
ll edg[MAXN << 1], dist[MAXN], suma[MAXN], sw[MAXN], ew[MAXN];
void addedge(int u, int v, ll w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}

void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; son[u] = 0; sz[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i]; 
		dist[v] = dist[u] + edg[i]; ew[v] = edg[i]; dfs1(v, u); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tprt) {
	top[u] = tprt; dfn[u] = ++tim; sw[tim] = sw[tim-1] + ew[u]; if(son[u]) dfs2(son[u], tprt);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa[u] && ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v);
	}
}

int tot, limtot, rt[MAXN];
struct SgtNode {ll v, a; int ls, rs;}e[MAXNODE];
void addrange(int &o, int pre, int l, int r, int x, int y) {
	if(pre <= limtot) o = ++tot, e[o] = e[pre];
	else o = pre;
	if(x <= l && r <= y) {e[o].a ++; e[o].v += sw[r] - sw[l-1]; return;}
	int m = (l + r) >> 1;
	if(x <= m) addrange(e[o].ls, e[pre].ls, l, m, x, y);
	if(y > m) addrange(e[o].rs, e[pre].rs, m+1, r, x, y);
	e[o].v = e[e[o].ls].v + e[e[o].rs].v + e[o].a * (sw[r] - sw[l-1]);
}
ll qryrange(int o, int l, int r, int x, int y) {
	if(x <= l && r <= y) return e[o].v;
	int m = (l + r) >> 1; ll ans = e[o].a * (sw[y] - sw[x-1]);
	if(y <= m) return ans + qryrange(e[o].ls, l, m, x, y);
	else if(x > m) return ans + qryrange(e[o].rs, m+1, r, x, y);
	else return ans + qryrange(e[o].ls, l, m, x, m) + qryrange(e[o].rs, m+1, r, m+1, y);
}
void addroute(int vs, int u, int v, ll k) {
	limtot = tot;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		addrange(rt[vs], rt[vs], 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if(u != v) {
		if(dep[u] > dep[v]) swap(u, v);
		addrange(rt[vs], rt[vs], 1, n, dfn[u]+1, dfn[v]);
	}
}
ll qryroute(int vs, int u, int v) {
	ll ans = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		ans += qryrange(rt[vs], 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if(u != v) {
		if(dep[u] > dep[v]) swap(u, v);
		ans += qryrange(rt[vs], 1, n, dfn[u]+1, dfn[v]);
	}
	return ans;
}

ll lans;
ll getval(ll a) {return (lans % (1 << 30ll)) ^ a;}
ll calc(int vs, int v) {
	return suma[vs] + vs * dist[v] - 2 * qryroute(vs, v, 1);
}
int main() {
	n = read(); q = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(); ll w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	dfs1(1, 0); dfs2(1, 1);
	for(int i = 1; i <= n; i++) suma[i] = suma[i-1] + dist[a[i]];
	for(int i = 1; i <= n; i++) {
		rt[i] = rt[i-1]; 
		addroute(i, a[i], 1, dist[a[i]]);
	}
	for(int i = 1; i <= q; i++) {
		int t = read();
		if(t == 1) {
			int l = getval(read()), r = getval(read()), v = getval(read());
			printf("%lld\n", lans = calc(r, v) - calc(l-1, v));
		} else {
			int x = getval(read());
			swap(a[x], a[x+1]); suma[x] = suma[x-1] + dist[a[x]];
			if(tot < 2.7e7) {
				rt[x] = rt[x-1]; addroute(x, a[x], 1, dist[a[x]]);
			} else {
				tot = 0;
				for(int i = 1; i <= n; i++) {
					rt[i] = rt[i-1];
					addroute(i, a[i], 1, dist[a[i]]);
				}
			}
		}
	}
	return 0;
}
```

