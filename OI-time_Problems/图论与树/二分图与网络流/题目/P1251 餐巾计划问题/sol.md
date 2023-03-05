# P1251 餐巾计划问题 解题报告

[P1251 餐巾计划问题](https://www.luogu.com.cn/problem/P1251)

## 题意分析

一个餐厅，第 $i$ 天先要 **得到** $r_i$ 块餐巾，然后要 **处理掉** 用掉的餐巾。

一、**得到** 包括三种方式：

1. 用 $p$ 的价格买一块新的。
2. 用之前 **慢洗** 得来的。（见下）
3. 用之前 **快洗** 得来的。（见下）

二、而 **处理掉** 的餐巾有两个来源：

1. 当天用掉的 $r_i$。
2. 昨天延期送洗的餐巾。

三、**处理掉** 餐巾有四种方式：

1. 不处理了，扔掉（其实这是必须存在的）。
2. 送去 **快洗**，可以在 $i+d_1$ 天送到，需要 $w_1$ 的价格。
3. 送去 **慢洗**，可以在 $i+d_2$ 天送到，需要 $w_2$ 的价格。
4. 延期送洗，第 $i+1$ 天送洗。

很容易说明这个转化是和原题意是等价的。

我们建立网络流模型，用流量表示餐巾的流向。

我们可以大致看看边的流向。如果我们把 得到 餐巾的时候叫做 “上午”，处理掉 餐巾的时候叫做“下午”。我们发现有这样一些边：

- 不知哪里来的 $\to$ “上午”。
- “下午” $\to$ 以后的“上午”。
- “下午” $\to$ 以后的“下午”。

我们建立网络流模型，应该要保证图是联通的，即从原点可以到任意一点，任意一点可以到汇点。

我们画出这个拓扑关系，就可以确定连边了。

- 从 $s$ 向 “下午” 连边，容量 $r_i$ 费用 0。这条边限制了要处理的餐巾数。
- 从 $s$ 向 “上午” 连边，容量 $\inf$ 费用 $p$ 。这条边表示买新的。
- 从 “上午”向 $t$ 连边，容量 $r_i$ 费用 0。这条边限制了得到的餐巾数。
- 从 第 $i$ 天“下午”向 第 $i+d_1$ 天“上午”连边，容量 $\inf$ 费用 $w_1$，这表示了洗餐巾。还有一种洗的方式，同理。
- 从 第 $i$ 天“下午”向 第 $i+1$ 天“下午”连边，容量 $\inf$ 费用0，表示延期送洗。

建图后，跑最小费用最大流就是答案。

这里最大流保证了：

1. 每天“上午”得到的餐巾满足需求，即“上午” $\to$ $t$ 的边一定是满流的。
2. 每天“下午”送来的餐巾数不超过 $r_i$。$s$ $\to$ “下午” 的边不一定满流，可能要丢掉一些餐巾。

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
const int MAXN = 2005, MAXNODE = 4015, MAXEDGE = 50005;
ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, s, t, head[MAXNODE], cnt = 1, inq[MAXNODE], pre[MAXNODE];
ll pr, d1, w1, d2, w2, r[MAXN], maxflow, mincost, dist[MAXNODE], incf[MAXNODE];
struct Edge {int v, nxt; ll w, c;}e[MAXEDGE];
void addedge(int u, int v, ll w, ll c) {
	e[++cnt] = (Edge){v, head[u], w, c}; head[u] = cnt;
	e[++cnt] = (Edge){u, head[v], 0, -c}; head[v] = cnt;
}
//1~n: night; n+1~n+n: day;
bool spfa() {
	queue<int> que;
	memset(dist, 0x3f, sizeof dist); memset(inq, 0x00, sizeof inq); incf[s] = INF; que.push(s); inq[s] = 1; dist[s] = 0;
	while(que.size()) {
		int u = que.front(); que.pop();
		inq[u] = 0;
		for(int i = head[u]; i; i = e[i].nxt) if(e[i].w) {
			int v = e[i].v;
			if(dist[v] > dist[u] + e[i].c) {
				dist[v] = dist[u] + e[i].c;
				incf[v] = min(e[i].w, incf[u]);
				pre[v] = i;
				if(!inq[v]) inq[v] = 1, que.push(v);
			}
		}
	}
	return dist[t] != INF;
}
void MCMF() {
	mincost = maxflow = 0;
	while(spfa()) {
		mincost += incf[t] * dist[t]; maxflow += incf[t];
		int now = t;
		while(now != s) {
			int p = pre[now];
			e[p].w -= incf[t]; e[p^1].w += incf[t];
			now = e[p^1].v;
		}
	}
}
int main() {
	n = read(); s = n+n+1, t = n+n+2;
	for(int i = 1; i <= n; i++) r[i] = read();
	pr = read(); d1 = read(); w1 = read(); d2 = read(); w2 = read();
	for(int i = 1; i <= n; i++) {
		addedge(s, i+n, INF, pr); 
		addedge(i+n, t, r[i], 0);
		addedge(s, i, r[i], 0);
		if(i+d1 <= n) addedge(i, i+d1+n, INF, w1);
		if(i+d2 <= n) addedge(i, i+d2+n, INF, w2);
		if(i+1 <= n) addedge(i, i+1, INF, 0);
	}
	MCMF();
	printf("%lld\n", mincost);
	return 0;
}
```

