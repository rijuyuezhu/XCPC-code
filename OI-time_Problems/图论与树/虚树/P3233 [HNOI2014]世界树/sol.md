# P3233 [HNOI2014]世界树 解题报告

[link](https://www.luogu.com.cn/problem/P3233)

## 题目大意

给出一棵 $n$ 个节点的树，边权为1。$q$ 次询问，每次询问给出 $m$ 个点（称为特殊点）。树上每个点的管辖点定义为离它最近的特殊点（若有多个，取编号最小者）。求每个特殊点管辖的点的数量。

$1\le n\le 3\times 10 ^ 5, \sum_{i=1}^q m_i\le 3\times 10 ^ 5$.

## 解题思路

看到这个问法，就知道这题肯定要建虚树。

如何求虚树上每个点的管辖点？可以两次树形dp完成（一次自下而上，一次自上而下），也可以暴力一点直接跑 dijkstra，不影响复杂度。

求出了虚树上每个点的管辖点后，就要统计答案了。只要在每个 $(u,fa_u)$ （$fa_u$ 是虚树上 $u$ 的父亲）的原树路径上倍增求出分界点就可以得到答案。小心统计虚子树！

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
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
const int MAXN = 3e5 + 5, INF = 0x3f3f3f3f;
struct Graph {
	int head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt;
	void addedge(int u, int v) {
		ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
	}
}g1, g2;
struct Val{int d, rt;};
bool operator < (const Val& A, const Val& B) {
	return A.d == B.d ? A.rt < B.rt : A.d < B.d;
}
Val operator + (const Val& A, const int& k) {
	return (Val){A.d + k, A.rt};
}
struct QN {Val v; int u;};
bool operator < (const QN& A, const QN& B) {
	return B.v < A.v;
}
int n, m, fa[MAXN][20], dfn[MAXN], tim, dep[MAXN], sz[MAXN], h[MAXN], seq[MAXN], stk[MAXN], fl[MAXN], stp, vis[MAXN], szt[MAXN], ans[MAXN];
Val dist[MAXN];
priority_queue<QN> pq;
void dfs(int u, int f) {
	fa[u][0] = f; dep[u] = dep[f] + 1; sz[u] = 1; dfn[u] = ++tim;
	for(int k = 1; k <= 19; k++) fa[u][k] = fa[fa[u][k-1]][k-1];
	for(int i = g1.head[u]; i; i = g1.nxt[i]) {
		int v = g1.ver[i]; if(v == f) continue;
		dfs(v, u); sz[u] += sz[v];
	}
}
int Lca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int k = 19; k >= 0; k--) if(dep[fa[u][k]] >= dep[v]) u = fa[u][k];
	if(u == v) return u;
	for(int k = 19; k >= 0; k--)
		if(fa[u][k] != fa[v][k])
			u = fa[u][k], v = fa[v][k];
	return fa[u][0];
}
int Dist(int u, int v) {return abs(dep[u] - dep[v]);}
void ins_tree(int u) {
	int lca = Lca(u, stk[stp]);
	while(stp > 1 && dfn[stk[stp-1]] >= dfn[lca]) g2.addedge(stk[stp], stk[stp-1]), g2.addedge(stk[stp-1], stk[stp]), stp--;
	if(lca != stk[stp]) g2.addedge(lca, stk[stp]), g2.addedge(stk[stp], lca), stk[stp] = lca;
	stk[++stp] = u;
}
bool cmp(int a, int b) {return dfn[h[a]] < dfn[h[b]];}
void init_tree(int u, int f) {
	vis[u] = 0; dist[u] = (Val){INF, 0}; ans[u] = 0;
	for(int i = g2.head[u]; i; i = g2.nxt[i]) {
		int v = g2.ver[i]; if(v == f) continue;
		init_tree(v, u);
	}
}
void dfs1(int u, int f) {
	szt[u] = sz[u];
	for(int i = g2.head[u]; i; i = g2.nxt[i]) {
		int v = g2.ver[i]; if(v == f) continue;
		dfs1(v, u); szt[u] -= szt[v];
	}
	int t = u;
	for(int k = 19; k >= 0; k--) {
		int ft = fa[t][k];
		if(dep[ft] > dep[f] && min(dist[u] + Dist(u, ft), dist[f] + Dist(f, ft)).rt == dist[u].rt)
			t = ft;
	}
	int lf = u;
	for(int k = 19; k >= 0; k--)
		if(dep[fa[lf][k]] > dep[f]) lf = fa[lf][k];
	ans[dist[u].rt] += sz[t] - sz[u] + szt[u];
	ans[dist[f].rt] += sz[lf] - sz[t];
	szt[u] = sz[lf];
}
void solve() {
	init_tree(1, 0);
	pq = priority_queue<QN>();
	for(int i = 1; i <= m; i++) dist[h[i]] = (Val){0, h[i]}, pq.push((QN){dist[h[i]], h[i]});
	while(pq.size()) {
		int u = pq.top().u; pq.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = g2.head[u]; i; i = g2.nxt[i]) {
			int v = g2.ver[i], w = Dist(u, v);
			if(dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.push((QN){dist[v], v});
			}
		}
	}
	dfs1(1, 0);	
}
void del_tree(int u, int f) {
	for(int i = g2.head[u]; i; i = g2.nxt[i]) {
		int v = g2.ver[i]; if(v == f) continue;
		del_tree(v, u);
	}
	g2.head[u] = 0; fl[u] = 0;
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		g1.addedge(u, v); g1.addedge(v, u);
	}
	dfs(1, 0);
	int q = read();
	while(q--) {
		m = read();
		for(int i = 1; i <= m; i++) h[i] = read(), fl[h[i]] = 1, seq[i] = i;
		sort(seq + 1, seq + 1 + m, cmp);
		stk[stp = 1] = 1;
		for(int i = 1; i <= m; i++) if(h[seq[i]] != 1) ins_tree(h[seq[i]]);
		while(stp > 1) g2.addedge(stk[stp], stk[stp-1]), g2.addedge(stk[stp-1], stk[stp]), stp--;
		solve();
		for(int i = 1; i <= m; i++) printf("%d ", ans[h[i]]);
		printf("\n");
		del_tree(1, 0); g2.cnt = 0;
	}
	return 0;
}
```

