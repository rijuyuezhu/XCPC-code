# 有上下界网络流 学习笔记

[toc]

## 前言

（阅读本文章前请确保已经了解 **最大流** 有关内容）

众所周知，网络流是一种解决问题的有效手段。它凭借灵活的建模技巧、得天独厚的图论性质、高效的算法成为了OI的一把利器。有上下界网络流 这一技巧也为网络流的解题创造了更开阔的维界。

十分感谢 **liu_runda** 的博客[有上下界的网络流学习笔记](https://www.cnblogs.com/liu-runda/p/6262832.html)，让我学会了这个算法。

## 例题

主要有四个，代表了有上下界网络流常见的四种模型：

[LOJ#115  无源汇有上下界可行流](https://loj.ac/p/115)

[LOJ#116. 有源汇有上下界最大流](https://loj.ac/p/116)

[LOJ#117. 有源汇有上下界最小流](https://loj.ac/p/117)

[P4043 支线剧情（有源汇有上下界最小费用可行流）](https://www.luogu.com.cn/problem/P4043)

## 模型构建

### 无源汇可行流

>   求一个网络的一个流 $f_i$，使 **所有** 节点满足三大条件（容量限制，斜对称性，流量守恒）。其中容量限制为 $lo_i\le f_i\le hi_i$。

“无源汇”是指这个网络没有源点汇点，所有节点流量守恒，在网络中有流循环地打转。

由于容量限制有一个下界，我们以前学过的最大流是没有下界的，考虑转化成普通的网络最大流处理。

（1）先不管流量守恒这一条件，我们给每条边直接赋予 $lo_i$ 的流量，这样自然能保证流量不会越下界。问题是，这样无法保证每个点流量守恒了。于是我们要进行流量的调整，给每条边适当地补充一些流量。

（2）在残量网络（边的容量为 $hi_i-lo_i$）上要进行流量的补充，补充的量与（1）中每个点的“入流”“出流”（即进入一个点的流和离开一个点的流）有关。具体地说：

-   如果（1）中一个点的入流比出流多 $k$，那么（2）中这个点的入流就会比出流少 $k$
-   如果（1）中一个点的入流比出流少 $k$，那么（2）中这个点的入流就会比出流多 $k$

这样，（1）（2）两部分的流加起来就达到入流=出流的状态了。

怎么达到这个目的呢？可以新建一个源点 $ss$、汇点 $tt$，流动一种“补充流”。如果某个点入流要比出流少 $k$，那么就从 $ss$ 向 $k$ 连一条容量为 $k$ 的边，分担掉一部分入流；如果入流要比出流多 $k$，那么就从 $k$ 向 $tt$ 连一条容量为 $k$ 的边，承接一部分。

为了达成目的，这个补充流 **必须** 达到满流。跑网络最大流即可。

最后每条边的流量就是 $lo_i+$残量网络跑完最大流后的流量。

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
const int MAXN = 205, MAXM = 10205, MAXNODE = 205, MAXEDGE = 25005;
const int INF = 0x3f3f3f3f;
int n, m, s, t, low[MAXM], addf[MAXM], ans[MAXM], ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], id[MAXEDGE], head[MAXNODE], cnt = 1;
void addedge(int u, int v, int w, int i) {
	ver[++cnt] = v; edg[cnt] = w; id[cnt] = i; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; id[cnt] = i; nxt[cnt] = head[v]; head[v] = cnt;
}
int d[MAXNODE], que[MAXNODE], hd, tl;
bool bfs() {
	hd = 1; tl = 0;
	memset(d, 0x00, sizeof d);
	d[s] = 1; que[++tl] = s;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) if(edg[i] && !d[ver[i]]) {
			int v = ver[i];
			d[v] = d[u] + 1;
			que[++tl] = v;
			if(v == t) return 1;
		}
	}
	return 0;
}
int dfs(int u, int flow) {
	if(u == t) return flow;
	int rest = flow;
	for(int i = head[u]; i && rest; i = nxt[i]) if(edg[i] && d[ver[i]] == d[u] + 1) {
		int v = ver[i];
		int k = dfs(v, min(rest, edg[i]));
		if(!k) d[v] = 0;
		edg[i] -= k; edg[i^1] += k; rest -= k;
	}
	return flow - rest;
}

int dinic() {
	int maxflow = 0, flow;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
	return maxflow;
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); low[i] = read(); int h = read();
		addedge(u, v, h - low[i], i);
		addf[u] -= low[i]; addf[v] += low[i];
	}
	s = 0; t = n+1;
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		if(addf[i] < 0) addedge(i, t, -addf[i], 0);
		if(addf[i] > 0) sum += addf[i], addedge(s, i, addf[i], 0);
	}
	if(dinic() == sum) {
		printf("YES\n");
		for(int u = 1; u <= n; u++)
			for(int i = head[u]; i; i = nxt[i])
				if(i % 2 == 0 && id[i])
					ans[id[i]] = low[id[i]] + edg[i^1];
		for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	} else printf("NO\n");
	return 0;	
}
```

### 有源汇可行流

> 大致和无源汇可行流一致，但存在两点 $s$，$t$ 不满足流量守恒。其中 $s$ 可以无限度地流出流量， $t$ 可以无限度地接受流量。网络的流量定义为流出 $s$ 的流量（亦即流入 $t$ 的流量）

**注意：** 后文中$ss$ 与 $s$ 不同， $tt$ 与 $t$ 不同！

只要建一条 $t\to s$ ，容量为 $[0,\inf]$ 的边即可。由于流出 $s$ 的流量和流入 $t$ 的流量理应相等，这样就可以保证 $s$ 与 $t$ 可以通过这条边进行流量的“转移”达到守恒。接下来只要跑无源汇可行流即可。值得注意的是，流过 $t\to s$ 的流量就是网络的流量。

### 有源汇最大流

> 求一支可行流，使得网络流量尽量大。

先构建出一条可行流。为了使流量尽可能大，我们在 $s$ 到 $t$ 的残量网络中跑尽所有增广路，就得到了最终答案。

具体地说：

1. 删去与 $ss$ 和 $tt$ 关联的边。
2. 删去边 $t\to s$。
3. 从 $s$ 到 $t$ 跑最大流，最后答案就是 （可行流）+（现在跑出的最大流）

**TIP**

- 步骤1.是不必要的。经过 $ss$ 和 $tt$ 不可能有增广路。
- 有源汇最大流还有另一种跑法。不要删边，先跑一次 $ss$ 到 $tt$ 的最大流后，再跑一次 $s$ 到 $t$ 的最大流，得到的流量就是答案。这是因为 $t\to s$ 的反向边（一条从 $s\to t$，残量就是可行流的边）一定会被增广。可惜的是有源汇最小流不能这样做。

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
const int MAXN = 205, MAXM = 10005, MAXNODE = 215, MAXEDGE = 30005, INF = 0x3f3f3f3f;
int n, m, s, t, _s, _t, lo[MAXM], hi[MAXM], head[MAXN], addf[MAXM], ver[MAXEDGE], nxt[MAXEDGE], edg[MAXEDGE], cnt = 1, d[MAXNODE], que[MAXNODE], hd, tl, ans;

void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}
bool bfs() {
	memset(d, 0x00, sizeof d); hd = 1; tl = 0;
	d[s] = 1; que[++tl] = s;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) if(edg[i] && !d[ver[i]]) {
			int v = ver[i];
			d[v] = d[u] + 1;
			que[++tl] = v;
			if(v == t) return 1;
		}
	}
	return 0;
}
int dfs(int u, int flow) {
	if(u == t) return flow;
	int rest = flow;
	for(int i = head[u]; i && rest; i = nxt[i]) if(d[ver[i]] == d[u] + 1 && edg[i]) {
		int v = ver[i];
		int k = dfs(v, min(rest, edg[i]));
		if(!k) d[v] = 0;
		edg[i] -= k; rest -= k; edg[i^1] += k;
	}
	return flow - rest;
}
int dinic() {
	int maxflow = 0, flow;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
	return maxflow;
}
int main() {
	n = read(); m = read(); s = read(); t = read();
	_s = n+1; _t = n+2;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); lo[i] = read(); hi[i] = read();
		addedge(u, v, hi[i] - lo[i]);
		addf[u] -= lo[i]; addf[v] += lo[i];
	}
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		if(addf[i] < 0) addedge(i, _t, -addf[i]);
		if(addf[i] > 0) sum += addf[i], addedge(_s, i, addf[i]);
	}
	addedge(t, s, INF);
	swap(s, _s); swap(t, _t);
	if(dinic() != sum) {
		printf("please go home to sleep\n");
		return 0;
	}
	swap(s, _s); swap(t, _t);
	printf("%d\n", dinic());
	return 0;
}
```

### 有源汇最小流

> 求一支可行流，使得网络流量尽量小。

同样先跑出可行流。删除不要的边后，从 $t$ 到 $s$ 跑一次最大流。最终答案就是 （可行流）-（现在跑出的最大流）。

这是因为反过来增广相当于“压榨”反向边的流量，也就是减少网络的流量。

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
const int MAXN = 50015, MAXM = 125015, MAXNODE = 50015, MAXEDGE = 400005;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, s, t, _s, _t, ver[MAXEDGE], nxt[MAXEDGE], cnt = 1, cur[MAXNODE], head[MAXNODE], d[MAXNODE], que[MAXNODE], hd, tl;
ll edg[MAXEDGE], addf[MAXNODE], ans;
void addedge(int u, int v, ll w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}

bool bfs() {
	memset(d, 0x00, sizeof d); hd = 1; tl = 0;
	memcpy(cur, head, sizeof cur);
	d[s] = 1; que[++tl] = s;
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = head[u]; i; i = nxt[i]) if(!d[ver[i]] && edg[i]) {
			int v = ver[i];
			d[v] = d[u] + 1;
			que[++tl] = v;
			if(v == t) return 1;
		}
	}
	return 0;
}
ll dfs(int u, ll flow) {
	if(u == t) return flow;
	ll rest = flow;
	for(int i = cur[u]; i && rest; i = nxt[i]) {
		cur[u] = i;
		if(edg[i] && d[ver[i]] == d[u] + 1) {
			int v = ver[i];
			ll k = dfs(v, min(rest, edg[i]));
			if(!k) d[v] = 0;
			edg[i] -= k; rest -= k; edg[i^1] += k;
		}
	}
	return flow - rest;
}
ll dinic() {
	ll maxflow = 0, flow;
	while(bfs()) while(flow = dfs(s, INF)) maxflow += flow;
	return maxflow;
}
int main() {
	n = read(); m = read(); s = read(); t = read();
	_s = n+1; _t = n+2;
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(); ll lo = read(), hi = read();
		addedge(u, v, hi - lo); addf[u] -= lo; addf[v] += lo;
	}
	ll sum = 0;
	for(int i = 1; i <= n; i++) {
		if(addf[i] < 0) addedge(i, _t, -addf[i]);
		if(addf[i] > 0) addedge(_s, i, addf[i]), sum += addf[i];
	}
	addedge(t, s, INF);
	swap(s, _s); swap(t, _t);
	if(dinic() != sum) {
		printf("please go home to sleep\n");
		return 0;
	}
	ans = edg[cnt];
	edg[cnt] = edg[cnt^1] = 0;
	swap(s, _t); swap(t, _s);
	printf("%lld\n", ans - dinic());
	 
	return 0;
}
```

### 有源汇最小费用可行流

> 求一支可行流，使其费用最小。这里的费用同费用流里的费用。

其实很简单，求可行流的时候用 spfa 增广即可。最后的答案就是 所有下界的流量的费用（$lo_i\times c_i$）+最小费用最大流的费用。

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
const int MAXN = 315, MAXE = 14005, INF = 0x3f3f3f3f;
int n, s, t, _s, _t, S, T, addf[MAXN], head[MAXN], edg[MAXE], nxt[MAXE], cap[MAXE], ver[MAXE], cnt = 1, maxflow, mincost, incf[MAXN], pre[MAXN], dist[MAXN], inq[MAXN], ans;
void addedge(int u, int v, int w, int c) {
	ver[++cnt] = v; edg[cnt] = w; cap[cnt] = c; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; cap[cnt] = -c; nxt[cnt] = head[v]; head[v] = cnt;
}
void Addedge(int u, int v, int lo, int hi, int c) {
	addedge(u, v, hi - lo, c);
	addf[u] -= lo; addf[v] += lo; ans += c * lo;
}
bool spfa() {
	memset(dist, 0x3f, sizeof dist); memset(inq, 0x00, sizeof inq);
	incf[S] = INF; inq[S] = 1; dist[S] = 0;
	queue<int> que; que.push(S);
	while(que.size()) {
		int u = que.front(); que.pop(); inq[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) if(edg[i]) {
			int v = ver[i];
			if(dist[v] > dist[u] + cap[i]) {
				dist[v] = dist[u] + cap[i];
				pre[v] = i;
				incf[v] = min(incf[u], edg[i]);
				if(!inq[v]) inq[v] = 1, que.push(v);
			}
		}
	}
	return dist[T] != INF;
}
void MCMF() {
	mincost = maxflow = 0;
	while(spfa()) {
		int now = T;
		maxflow += incf[T]; mincost += incf[T] * dist[T];
		while(now != S) {
			int p = pre[now];
			edg[p] -= incf[T]; edg[p^1] += incf[T];
			now = ver[p^1];
		}
	}
}
int main() {
	n = read();	s = 1; t = n+1; _s = n+2; _t = n+3;
	for(int i = 1; i <= n; i++) {
		int k = read();
		for(int j = 1; j <= k; j++) {
			int b = read(), t = read();
			Addedge(i, b, 1, INF, t);
		}
		Addedge(i, t, 0, INF, 0);
	}
	for(int i = 1; i <= n+1; i++) {
		if(addf[i] < 0) addedge(i, _t, -addf[i], 0);
		if(addf[i] > 0) addedge(_s, i, addf[i], 0);
	}
	addedge(t, s, INF, 0);
	S = _s; T = _t;
	MCMF();
	printf("%d\n", ans + mincost);
	return 0;
}
```





## 后记

这篇文章历时两天完成，中途因为一次断电导致存档尽失。

只好说受益颇多吧。这几个板子让我找出了许多问题。比如发现我的 Dinic 当前弧优化是假的。细心观察的同学会发现我最小流中 dinic 的写法不太一样。

完结撒花。