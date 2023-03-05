# 二分图最大权匹配（KM算法） 学习笔记

[toc]

## 学习资料

[匈牙利与KM算法](https://www.luogu.com.cn/blog/suxxsfe/xiong-ya-li-suan-fa)

[二分图最大权匹配——OI Wiki](https://oi-wiki.org/graph/graph-matching/bigraph-weight-match/)

[题解 P6577【模板】二分图最大权完美匹配](https://www.luogu.com.cn/blog/SingerCoder/solution-p6577)

<https://www.cnblogs.com/zhltao/p/12549489.html	>

## KM算法

[P6577 【模板】二分图最大权完美匹配](https://www.luogu.com.cn/problem/P6577)

KM算法用来求一类特殊二分图的最大权完美匹配。这个特殊指：

1. **每对** 左右部点间都有边
2. 左右部的节点数量相同。

其实没有关系。我们只要这样做，就可以推至普适情况：

1. 原来没有边的左右部点间连权值为 0 / $-\inf$的边（通常直接用邻接矩阵实现。连 0 还是连 $-\inf$ 取决于是否要求一定要完美匹配）。
2. 往少的那一部补一些点使之相等。

所以我们说，KM算法适用于普遍的二分图的**最大权匹配**。

## 定义

**顶标**

我们给每个节点设置一个 “顶标”。为了方便，左部节点的顶标叫做 $lx_i$，右部节点的顶标叫做 $ly_i$。

> 顶标的性质：
>
> 任意时刻，对于图中任意一条边 (u,v,w)，有 $lx_u+ly_v\ge w$。

**相等子图**

相等子图 **包括原二分图中的所有节点（即一个生成子图）**，而边集却是原图中满足 $lx_u+ly_v=w$ 的边 (u,v,w) 构成的。也就是把那些 $lx_u+ly_v=w$ 的边搞出来的一个生成子图。

> 相等子图的性质：
>
> 1. 相等子图若存在完美匹配，则完美匹配的权和就是顶标和。
> 2. 相等子图若存在完美匹配，则同时也是原图的最大权完美匹配。

于是我们只要增广一个相等子图，使之具有完美匹配即可。

## 算法流程

1. 赋予一个顶标初始值，比如 $lx_u=\max\{w|(u,v,w)\},ly_i=0$
2. 选一个未匹配点，从它那里开始在 **相等子图** 中增广。
3. 调整顶标，给在交错树中的左部的节点减去一个值，给在交错树中的右部的节点加上一个值。这是为了让更多的节点加进相等子图。

我们详细地说说“调整顶标”。

### 调整顶标

比如我们要进行调整的变化值为 $a$，即让所有在交错树中的点的 $lx_u$ 减 $a$，$ly_v$ 加 $a$。

于是：

若假设 $u,v$ 分别是交错树上任意的两个左、右部点，$u',v'$ 分别是交错树外任意的两个左、右节点。

1.  $(u, v)$ 仍在交错树上。
2. $(u',v')$ 仍不在交错树上。
3. $(u,v')$ 由于顶标和减少，**有可能** 进入相等子图。
4. $(u',v)$ 顶标和增加，更不可能进入相等子图。

所以我们要增广，关键看第3种情况。

为了维护顶标的性质，并且让第3种情况的边加入， $a$ 值应选择为：

$a=\min\{(lx_u+ly_{v'}-w)|\forall(u,v',w)\}$。

于是，我们可以先写出个dfs版本的KM算法。可惜的是，它的时间复杂度可能卡到 $O(n^4)$，无法通过模板题。

## 代码(Dfs)

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
const int MAXN = 505;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, match[MAXN], vx[MAXN], vy[MAXN];
ll e[MAXN][MAXN], slack[MAXN], lx[MAXN], ly[MAXN];
bool dfs(int u) {
	vx[u] = 1;
	for(int v = 1; v <= n; v++) if(!vy[v]) {
		if(lx[u] + ly[v] == e[u][v]) {
			vy[v] = 1;
			if(!match[v] || dfs(match[v])) {
				match[v] = u;
				return 1;
			}
		} else slack[v] = min(slack[v], lx[u] + ly[v] - e[u][v]);
	}
	return 0;
}
void KM() {
	for(int i = 1; i <= n; i++) lx[i] = -INF, ly[i] = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) lx[i] = max(lx[i], e[i][j]);
	for(int i = 1; i <= n; i++)
		while(1) {
			for(int j = 1; j <= n; j++) vx[j] = vy[j] = 0, slack[j] = INF;
			if(dfs(i)) break;
			ll d = INF;
			for(int j = 1; j <= n; j++) if(!vy[j]) d = min(d, slack[j]);
			for(int j = 1; j <= n; j++) {
				if(vx[j]) lx[j] -= d;
				if(vy[j]) ly[j] += d;
			}
		}
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = -INF;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll w = read();
		e[u][v] = max(e[u][v], w);
	}
	KM();
	ll ans = 0;
	for(int i = 1; i <= n; i++) ans += lx[i] + ly[i];
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i++) printf("%d ", match[i]);
	return 0;
}
```

那么怎么办呢？只要换用bfs写法就好啦。这样就不会每次从头增广。

时间复杂度 $O(n^3)$

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int MAXN = 505;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, vx[MAXN], vy[MAXN], px[MAXN], py[MAXN], pre[MAXN];
ll e[MAXN][MAXN], lx[MAXN], ly[MAXN], slack[MAXN];
queue<int> que;
void aug(int v) {
	while(v) {
		int t = px[pre[v]];
		px[pre[v]] = v;
		py[v] = pre[v];
		v = t;
	}
}
void bfs(int s) {
	for(int i = 1; i <= n; i++) vx[i] = vy[i] = 0, slack[i] = INF;
	que = queue<int>();
	que.push(s);
	while(1) {
		while(que.size()) {
			int u = que.front(); que.pop();
			vx[u] = 1;
			for(int v = 1; v <= n; v++) if(!vy[v]) {
				if(lx[u] + ly[v] - e[u][v] < slack[v]) {
					slack[v] = lx[u] + ly[v] - e[u][v];
					pre[v] = u;
					if(slack[v] == 0) {
						vy[v] = 1;
						if(!py[v]) {aug(v); return ;}
						else que.push(py[v]);
					}
				}
			}
		}
		ll d = INF;
		for(int i = 1; i <= n; i++) if(!vy[i]) d = min(d, slack[i]);
		for(int i = 1; i <= n; i++) {
			if(vx[i]) lx[i] -= d;
			if(vy[i]) ly[i] += d;
			else slack[i] -= d;
		}
		for(int i = 1; i <= n; i++) if(!vy[i]) {
			if(slack[i] == 0) {
				vy[i] = 1;
				if(!py[i]) {aug(i); return ;}
				else que.push(py[i]);
			}
		}
	}
}
void KM() {
	for(int i = 1; i <= n; i++) lx[i] = -INF, ly[i] = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) lx[i] = max(lx[i], e[i][j]);
	for(int i = 1; i <= n; i++) bfs(i);
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) e[i][j] = -INF;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll w = read();
		e[u][v] = max(e[u][v], w);
	}
	KM();
	ll ans = 0;
	for(int i = 1; i <= n; i++) ans += lx[i] + ly[i];
	printf("%lld\n", ans);
	for(int i = 1; i <= n; i++) printf("%d ", py[i]);
	return 0;
}
```