# P2469 [SDOI2010]星际竞速 解题报告

这可能是我人生中的第一道费用流（模板除外）

[toc]

## 题目链接

https://www.luogu.com.cn/problem/P2469

## 题目大意

（稍加转化）

给定一个带权有向无环图，要求 “经过” **恰好** 一次每个点。

这里的 “经过” 是一种路径覆盖操作，具体地说：

1. 选定一个 **出发点** $i$，这需要花费你 额外 $a_i$ 钱。
2. 走过一条以 $i$ 为出发点的路径（包括 $i$ ），路经权值和为你要花的钱。

最少要花多少钱？

- 点数 $n\le 800$, 边数 $m\le 15000$

## 解题思路

看到这个问题，我们会想到最大流/二分图中的最小路径覆盖问题。于是我们套路性地拆点，套路性地连边，套路性地定义一条流代表两个点之间的“路径合并”。由于边带权，可以想到可能是一道费用流。

### 解法1

连边为:

 $s\to u$，容量1费用0。

$u\to v'$，容量1费用为边权。

$v'\to t$，容量1费用0。

考虑 $a_i$ 怎么表现出来。

我们发现，进入每个点有两种情况，而且必须二选一：

1. 从另外一个点进入。
2. 从全局进入。

那么只需要连边 $s\to v'$，容量1费用 $a_i$，它与许许多多的 $u\to v'$ 边“并联”。由于 $v'\to t$ 的边容量为1，这代表着只有一条边可以被选择，正好符合定义。

稍加思虑发现，只需要求 **最小费用最大流** 即可。

### 解法2

同样考虑 $a_i$ 怎么表现出来。

我们考虑图上没有 “路径合并” 的时的状态。这时相当于每个路径仅覆盖一个点，总代价为 $\sum a_i$。

为了更优，我们 **在这基础上** 进行路径合并。如果 $(u,v)$ 被选上，那么我们需要多出 $w(u,v)$ 的权值，但会减少 $a_v$ 的权值。于是可以这样建图：

 $s\to u$，容量1费用0。

$u\to v'$，容量1费用为边权。

$v'\to t$，容量1费用 $-a_{v}$。

在上面跑 **最小费用可行流**，最后答案就是 $\sum a_i +\mathrm{mincost}$。



## 代码

### 解法1

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
const int MAXN = 805;
const int MAXM = 15005;
const int MAXNODE = 1705;
const int MAXEDGE = 50005;
const int INF = 0x3f3f3f3f;
int n, m, s, t, a[MAXN], ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], cap[MAXEDGE], head[MAXNODE], cnt = 1;

void addedge(int u, int v, int w, int c) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; cap[cnt] = c; head[u] = cnt;
	ver[++cnt] = u; nxt[cnt] = head[v]; edg[cnt] = 0; cap[cnt] = -c; head[v] = cnt;
}
//s:2*n+1, t:2*n+2
//u:1~n
//u':n+1~n+n

int inq[MAXNODE], dist[MAXNODE], incf[MAXNODE], pre[MAXNODE], maxflow, mincost;
bool spfa() {
	memset(inq, 0x00, sizeof inq); memset(dist, 0x3f, sizeof dist);
	queue<int> que;
	que.push(s); inq[s] = 1; dist[s] = 0; incf[s] = INF;
	while(que.size()) {
		int u = que.front(); que.pop(); inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(dist[v] > dist[u] + cap[i]) {
				dist[v] = dist[u] + cap[i];
				incf[v] = min(incf[u], edg[i]);
				pre[v] = i;
				if(!inq[v]) que.push(v), inq[v] = 1;
			}
		}
	}
	return dist[t] != INF;
}
void upd() {
	int now = t;
	while(now != s) {
		int p = pre[now];
		edg[p] -= incf[t]; edg[p^1] += incf[t];
		now = ver[p^1];
	}
	maxflow += incf[t]; mincost += incf[t] * dist[t];
}
void MCMF() {
	while(spfa()) upd();
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	s = n+n+1, t = n+n+2;
	for(int i = 1; i <= n; i++) addedge(s, i, 1, 0);
	for(int i = n+1; i <= n+n; i++) addedge(i, t, 1, 0);
	for(int i = 1; i <= n; i++) addedge(s, i+n, 1, a[i]);
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		if(u > v) swap(u, v);
		addedge(u, v+n, 1, w);
	}
	MCMF();
	printf("%d\n", mincost);
	return 0;
}
```

### 解法2

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
const int MAXN = 805, MAXM = 15005;
const int MAXNODE = 17005, MAXEDGE = 40005;
const int INF = 0x3f3f3f3f;
int n, m, s, t, ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], cap[MAXEDGE], head[MAXNODE], cnt = 1, ans;
void addedge(int u, int v, int w, int c) {
	ver[++cnt] = v; edg[cnt] = w; cap[cnt] = c; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; cap[cnt] = -c; nxt[cnt] = head[v]; head[v] = cnt;
}
int ansflow, mincost, inq[MAXNODE], dist[MAXNODE], incf[MAXNODE], pre[MAXNODE]; 
bool spfa() {
	memset(dist, 0x3f, sizeof dist); memset(inq, 0x00, sizeof inq);
	queue<int> que;
	dist[s] = 0; inq[s] = 1;
	que.push(s);
	incf[s] = INF;
	while(que.size()) {
		int u = que.front(); que.pop(); inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(dist[v] > dist[u] + cap[i]) {
				dist[v] = dist[u] + cap[i];
				if(!inq[v]) que.push(v), inq[v] = 1;
				pre[v] = i; incf[v] = min(incf[u], edg[i]);
			}
		}
	}
	return dist[t] < 0;
}
void MCMF() {
	while(spfa()) {
		int now = t;
		ansflow += incf[t]; mincost += incf[t] * dist[t];
		while(now != s) {
			int p = pre[now];
			edg[p] -= incf[t]; edg[p^1] += incf[t];
			now = ver[p^1];
		}
	}
}


int main() {
	n = read(); m = read();
	s = n+n+1, t = n+n+2;
	for(int i = 1; i <= n; i++) {
		int c = read();
		addedge(s, i, 1, 0);
		addedge(i+n, t, 1, -c);
		ans += c;
	}
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), c = read();
		if(u > v) swap(u, v);
		addedge(u, v+n, 1, c);
	}
	MCMF();
	printf("%d\n", ans + mincost);

	return 0;
}
```







