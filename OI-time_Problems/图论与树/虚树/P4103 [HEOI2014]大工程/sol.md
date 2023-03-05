# P4103 [HEOI2014]大工程 解题报告

[link](https://www.luogu.com.cn/problem/P4103)

## 题目大意

给一棵 $n$ 个点的边权为 1 的树，$q$ 次询问，每次给出 $k$ 个特殊点 $h_i(1\le i\le k)$，求：

1. 这 $h_i$ 个点之间形成的 $\left(\begin{matrix}k \\ 2\end{matrix}\right)$ 条路径的长度之和
2.  这 $h_i$ 个点之间形成的 $\left(\begin{matrix}k \\ 2\end{matrix}\right)$ 条路径中长度的最小值。
3. 这 $h_i$ 个点之间形成的 $\left(\begin{matrix}k \\ 2\end{matrix}\right)$ 条路径中长度的最大值。

$1\le n\le 10^6,\sum_{i=1}^q k_i\le 2n$。

## 解题报告

首先显然要建虚树，在虚树上dp。

考虑怎么求路径长度之和。这里用了类似于求 树的直径 的方法。设 $dist(u)$ 表示 $u$ 子树内所有特殊点到 $u$ 的距离之和，$siz(u)$ 表示 $u$ 子树内特殊点的数量，我们考虑如何合并子树的答案。

假设现在合并了前 $k$ 棵子树（我们把这 $k$ 棵子树以及根 $u$ 的集合体叫做 $lst$），要加入第 $k+1$ 棵子树（把这棵子树叫做 $v$，不妨把子树的根也叫做 $v$），考虑答案会新增多少。
$$
ans\gets\sum_{x\in lst}\sum_{y\in v}Dist(x,y)\\
=\sum_{x\in lst}\sum_{y\in v}[Dist(x,u)+Dist(u,v)+Dist(v,y)]
\\
=\sum_{x\in lst}Dist(x,y)\sum_{y\in v}1+Dist(u,v)\sum_{x\in lst}1\sum_{y\in v}1+\sum_{y\in v}Dist(v,y)\sum_{x\in lst}1
\\
=dist(lst)\cdot siz(v)+ Dist(u,v)\cdot siz(lst)\cdot siz(v)+dist(v)\cdot siz(u)
$$
类似于树形dp求树的直径，我们可以巧妙地改变转移顺序来完成这项工作。其它两个操作是类似的。

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

const int MAXN = 1e6 + 5;
const ll INF = 1e16;
int n, fa[MAXN], dep[MAXN], son[MAXN], sz[MAXN], top[MAXN], dfn[MAXN], tim, siz[MAXN], h[MAXN], K, stk[MAXN], stp;
ll ansd, mind, maxd, dist[MAXN], mn[MAXN], mx[MAXN];
struct Graph {
	int head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt;
	void addedge(int u, int v) {
		ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
	}
}g1, g2;
void dfs1(int u, int f) {
	fa[u] = f; dep[u] = dep[f] + 1; sz[u] = 1; son[u] = 0;
	for(int i = g1.head[u]; i; i = g1.nxt[i]) {
		int v = g1.ver[i]; if(v == f) continue;
		dfs1(v, u); sz[u] += sz[v]; 
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	dfn[u] = ++tim; top[u] = tp; if(son[u]) dfs2(son[u], tp);
	for(int i = g1.head[u]; i; i = g1.nxt[i]) {
		int v = g1.ver[i]; if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
int Lca(int u, int v) {
	while(top[u] != top[v]) dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
	return dep[u] > dep[v] ? v : u;
}
bool cmp(int a, int b) {return dfn[a] < dfn[b];}
void ins_tree(int u) {
	int lca = Lca(u, stk[stp]);
	while(stp > 1 && dfn[lca] <= dfn[stk[stp-1]]) g2.addedge(stk[stp-1], stk[stp]), stp--;
	if(lca != stk[stp]) g2.addedge(lca, stk[stp]), stk[stp] = lca;
	stk[++stp] = u;
}
void dfs3(int u) {
	dist[u] = 0; mn[u] = siz[u] ? 0 : INF; mx[u] = siz[u] ? 0 : -INF;
	for(int i = g2.head[u]; i; i = g2.nxt[i]) {
		int v = g2.ver[i]; dfs3(v);
		ll d = dep[v] - dep[u];
		ansd += dist[u] * siz[v] + d * siz[u] * siz[v] + dist[v] * siz[u];
		mind = min(mind, mn[u] + mn[v] + d);
		maxd = max(maxd, mx[u] + mx[v] + d);
		siz[u] += siz[v];
		dist[u] += dist[v] + d * siz[v];
		mn[u] = min(mn[u], mn[v] + d);
		mx[u] = max(mx[u], mx[v] + d);
	}
}
void del_tree(int u) {
	for(int i = g2.head[u]; i; i = g2.nxt[i]) del_tree(g2.ver[i]);
	g2.head[u] = 0; siz[u] = 0;
}
int main() {
	n = read(); 
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		g1.addedge(u, v); g1.addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1);
	int q = read();
	while(q--) {
		K = read();
		for(int i = 1; i <= K; i++) h[i] = read(), siz[h[i]] = 1;
		sort(h + 1, h + 1 + K, cmp);

		stk[stp = 1] = 1;
		for(int i = 1; i <= K; i++) if(h[i] != 1) ins_tree(h[i]);
		while(stp > 1) g2.addedge(stk[stp-1], stk[stp]), stp--;
		
		ansd = 0; mind = INF; maxd = -INF;
		dfs3(1);
		printf("%lld %lld %lld\n", ansd, mind, maxd);
		del_tree(1); g2.cnt = 0;
	}
	return 0;
}
```

