# Kruskal重构树 学习笔记

[toc]

## 前言

Kruskal重构树是一种比较冷门的算法，但在解决某些问题时相当好用。

## 例题1 BZOJ3732 Network

[链接](https://darkbzoj.tk/problem/3732#tab-tutorial)

> 在一个 $n$ 点 $m$ 边的无向连通图中多次询问两点间的最长边最小值（即两点间的瓶颈）。

这是一个经典的 Kruskal重构树问题。

这个问题其实也可以直接用最小生成树来解决。因为要最小化最长边，选择最小生成树上的边肯定是不劣的。于是我们可以在最小生成树上倍增得到答案。

而Kruskal重构树则是这样的做的：在用Kruskal合并连通块时，顺便维护一个树的结构。比如要合并连通块 $fu$ 和 $fv$，中间有 权值为 $w$ 的边相连，就新建一个节点作为 **合并后连通块的根**，赋予点权为 $w$，并且设置左右儿子为 $fu$ 和 $fv$。Kruskal做完后，我们就构造了具有以下特征的树：

1. 叶子节点是原图的 $n$ 个点，没有点权。
2. 非叶子节点代表着原图中 **在生成树上的** $n-1$ 条边，点权就是原图的边权。
3. 由于合并时边权有一定次序，我们发现得到的树是个**二叉堆**（不考虑叶子节点）。如果是做最小（大）生成树，得到的是大（小）根堆。
4. 两点于树上的路径上的各点，相当于原图上两点走最小（大）生成树的路径上的各边。

这个树叫做 Kruskal重构树。易得这棵树一共有 $2n-1$ 个点， $2n-2$ 条边。

---

回到这题。很容易知道，我们要找的，就是在 Kruskal 重构树上两点路径中的最长边。或者准确点，两点路径上的点权最大者。别犯浑用倍增做啊！由于 Kruskal 重构树是个堆，点权最大的就是两点的 lca 了。

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
```

## 例题2 [NOI2018] 归程

[链接](https://www.luogu.com.cn/problem/P4768)

这道题与 Kruskal重构树无关的部分我直接写了篇[题解](https://blog.csdn.net/qq_41996523/article/details/112631996)，这里仅提一下这样一个小问题：

> 在一个无向连通图中多次询问，每次给出点 $v$ 和限制 $p$， 请回答仅经过边权 $\le p$ 的边可以到达点的个数。（和原题稍有转化）

这是另一个 Kruskal 重构树的模型。

这个问题似乎不好做，不过有个简单易行的离线做法。按限制把询问升序排序，在做最小生成树的同时回答询问即可。

在线做法？~~我只知道Kruskal重构树，可能是我太菜~~

我们建完Kruskal重构树后，问题就转化为：不经过点权 $>p$ 的点，最多可以到多少个点。然后由于它是一棵树，我们能去的点都在一个子数内。倍增找到深度最小的 点权$\le p$ 的点，询问子树信息即可。