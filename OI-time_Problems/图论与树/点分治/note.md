# 点分治 学习笔记

2021/2/18: 终于重拾点分治。

## 点分治概述

点分治采用层层分治的方法，以点为分治中心，能较好地完成无根树上的链（或者说点对）的统计任务。但由于点分治的特性（它重构了树），它无法相当有效地完成与有根树的祖孙结构（比如子树）有关的统计任务。

## 树的重心

### 定义

有两个相互等价的定义：

**定义1：** 若树上存在一点，使得该点删去后形成若干个连通块，每个连通块的点数都 $\le \left \lfloor \dfrac n 2\right \rfloor$ ，则该点称为树的重心。

**定义2：**  删去树上一点，使得形成的若干连通块中最大的那个的大小最小化的点称为树的重心。

### 性质

奇数点数的树有且仅有一个重心，偶数点数的树有 一个重心 或 相邻的两个重心。



## 点分治重构树（点分树）

### 定义

![picture](D:%5COneDrive%20-%20UOTAGO%5C%E7%AC%94%E8%AE%B0%5C%E7%AC%94%E8%AE%B0%E5%9B%BE%E7%89%87%5C20210219090330309.png)

如图，2（红点） 是整个树的重心，称作第一级重心；4,6,7（蓝点）是删去第一级重心形成的三个连通块分别的重心，称作第二级重心；同理，黑点是第三级重心。

我们把树的 **各级重心** 找到，重新连边，就形成了点分治重构树（点分树）。

### 性质

我们把点分树上两点记为 $x,y$，它们在点分树上的 lca 为 $z$。

则：

1. 原树中的路径 $(x,y)$ 一定经过 $z$。
2. 点分树的树高为 $O(\log n)$。

## 点分治

点分治的最基本思想为：枚举点分树上的每个点，统计其子树的信息。

一般来说，点分治有两种实现方式，下面以一道例题呈现。

[P4178 Tree](https://www.luogu.com.cn/problem/P4178)

>  给定一棵 $n$ 个节点的树，每条边有边权，求出树上两点距离小于等于 $k$ 的点对数量。



### 实现方式1

![picture](D:%5COneDrive%20-%20UOTAGO%5C%E7%AC%94%E8%AE%B0%5C%E7%AC%94%E8%AE%B0%E5%9B%BE%E7%89%87%5C20210219090330309.png)

我们在重构树上 dfs，对每个节点 $x$ 统计 **经过** $x$ 的路径数量。

我们暂且不考虑以 $x$ 为端点的路径，只考虑 $(y,z)$ 这样的路径（其中 $\mathrm{lca}(y,z)=x$）。形式化地，若 $x$ 的所有子树为 $y_1,y_2,\cdots,y_k$，我们依次考虑 $y_i(1\le i\le k)$ 子树和之前的 $y_1,y_2,\cdots,y_{i-1}$ 棵子树之间形成的路径，用数据维护统计，统计完后再把 $y_i$ 的信息并入。那么如何统计以 $x$ 为端点的路径呢？大部分时候可以直接以一种数据结构初始化的形式（比如一开始插入一个值等）得到。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
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
const int MAXN = 4e4 + 5, INF = 0x3f3f3f3f;
int n, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, edg[MAXN << 1], k, sz[MAXN], mxsz[MAXN], tsz, rt, vis[MAXN], ans, tree, d[MAXN], dnum;
namespace Treap {
    //平衡树
	struct Node{int ls, rs, v, s, c, k;}e[MAXN];
	int tot;
	void upd(int p) {e[p].s = e[e[p].ls].s + e[e[p].rs].s + e[p].c;}
	void lturn(int& p) {int s = e[p].rs; e[p].rs = e[s].ls; upd(p); e[s].ls = p; upd(s); p = s;}
	void rturn(int& p) {int s = e[p].ls; e[p].ls = e[s].rs; upd(p); e[s].rs = p; upd(s); p = s;}
	void ins(int& p, int v) {
		if(!p) e[p = ++tot] = (Node){0, 0, v, 1, 1, rand()};
		else if(e[p].v == v) e[p].c++, upd(p);
		else if(e[p].v > v)
			ins(e[p].ls, v), e[p].k > e[e[p].ls].k ? rturn(p) : upd(p);
		else
			ins(e[p].rs, v), e[p].k > e[e[p].rs].k ? lturn(p) : upd(p);
	}
	int le(int p, int v) {
		if(!p) return 0;
		else if(e[p].v == v) return e[e[p].ls].s + e[p].c;
		else if(e[p].v > v) return le(e[p].ls, v);
		else return e[e[p].ls].s + e[p].c + le(e[p].rs, v);
	}
}
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
void getrt(int u, int f) {
    //求重心
	sz[u] = 1; mxsz[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getrt(v, u); sz[u] += sz[v]; mxsz[u] = max(mxsz[u], sz[v]);
	}
	mxsz[u] = max(mxsz[u], tsz - sz[u]);
	if(mxsz[u] < mxsz[rt]) rt = u;
}
void getdis(int u, int f, int w) {
    //得到一个子树内的距离信息
	d[++dnum] = w;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getdis(v, u, w + edg[i]);
	}
}
void calc(int u) {
	tree = Treap::tot = 0;
	Treap::ins(tree, 0);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		dnum = 0;
		getdis(v, u, edg[i]);
		for(int i = 1; i <= dnum; i++) ans += Treap::le(tree, k - d[i]);//统计信息
		for(int i = 1; i <= dnum; i++) Treap::ins(tree, d[i]);//合并信息
	}
}

void solve(int u) {
	vis[u] = 1; calc(u);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		tsz = sz[v]; mxsz[rt = 0] = INF;
        /*
        水平较高的同学可能发现这个 tsz 可能是错误的，那么不妨看看这篇博客：
        https://liu-cheng-ao.blog.uoj.ac/blog/2969
        */
		getrt(v, u); solve(rt);
	}
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(), w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	k = read();
	tsz = n; mxsz[rt = 0] = INF;
	getrt(1, 0); solve(rt);
	printf("%d\n", ans);
	return 0;
}
```

### 实现方式2

我们在重构树上 dfs，对每个节点 $x$ 统计 **经过** $x$ 的路径数量。

考虑怎么统计。我们采用一种容斥的思路。我们用 $calc(x)$ 表示统计 $x$ 的子树的信息。这里的统计是点对统计，即
$$
calc(x)=\sum_{u,v\in subtree(x)}[(u,v)符合条件]
$$
问题是这样可能会导致 $u,v$ 的 lca 不为 $x$（当 $u,v$ 在 $x$ 的同一子树中），于是根据容斥原理，我们要把这样的信息减掉。

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
const int MAXN = 4e4 + 5, INF = 0x3f3f3f3f;
int n, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, edg[MAXN << 1], k, sz[MAXN], mxsz[MAXN], tsz, rt, vis[MAXN], d[MAXN], dnum, ans;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
void getrt(int u, int f) {
	sz[u] = 1; mxsz[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getrt(v, u); sz[u] += sz[v]; mxsz[u] = max(mxsz[u], sz[v]);
	}
	mxsz[u] = max(mxsz[u], tsz - sz[u]);
	if(mxsz[u] < mxsz[rt]) rt = u;
}
void getdis(int u, int f, int dis) {
	d[++dnum] = dis;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getdis(v, u, dis + edg[i]);
	}
}
int calc(int u, int dis) {
    //统计 u 的子树的信息，注意这里的 dis ，是为了保证容斥时（减去子树的信息时）得到的子树信息与原来统计时一致。
	int ans = 0; dnum = 0;
	getdis(u, 0, dis);
	sort(d + 1, d + 1 + dnum);
	for(int i = 1, j = dnum; i <= n && i <= j; i++) {
		while(d[i] + d[j] > k) j--;
		if(i <= j) ans += j - i;
	}
	return ans;
}
void solve(int u) {
	vis[u] = 1; ans += calc(u, 0);//加上 u 的信息。
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		ans -= calc(v, edg[i]);//容斥，减去 u 的每棵子树内部的信息。
		tsz = sz[v]; mxsz[rt = 0] = INF;
		getrt(v, u); solve(rt);
	}
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(), w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	k = read();
	tsz = n; mxsz[rt = 0] = INF;
	getrt(1, 0); solve(rt);
	printf("%d\n", ans);
	return 0;
}
```

### 对比

第一种实现方式普适性很强，不仅可以维护可减的信息，还可以维护最值等不可减信息。

第二种实现方式较为巧妙，代码相对好写，但只能维护可以容斥（可减）的信息。

如果有多组询问，不妨建立点分树，这样的话，可以减小常数。如果将各个点的信息进行存储（见下），则可以将单次询问的复杂度优化（去掉一个 $n$）。

## 动态点分治

如果树信息加上修改，怎么办呢？可以建立点分树，用数据结构维护每个点的信息。由于点分树最多有 $\log n$ 层，若在每个节点存点分树上子树内的节点信息，空间是 $O(n\log n)$ 的。这样，在查询/修改一个点的信息时，其实只要在点分树上跳父亲即可。一般来说，基于容斥（第二种实现方式）的比较好做。第一种实现方式为保证复杂度，需要限制每个点的度数（添加虚点，多叉树转二叉树）。

[P6329 【模板】点分树 | 震波](https://www.luogu.com.cn/problem/P6329)

