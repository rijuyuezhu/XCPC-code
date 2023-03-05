# P3554 LUK-Triumphal arch 解题报告

[P3554 [POI2013]LUK-Triumphal arch](https://www.luogu.com.cn/problem/P3554)

## 题目大意

一颗 $n$ 个点的树，点有黑白两种颜色。一开始 1号点是黑色的，A待在 $1$ 号点。重复依次进行以下动作：

1. 选择 $k$ 个点变成黑色。
2. A **随机** 向周围的可直接到达的点走一步。

要使 **无论A怎么走**，他永远不会到白点上。求最小的$k$

## 解题报告

首先，这个 $k$ 显然是可二分答案的东西。

我们可以考虑树上dp。dp最核心的一点，就是要寻找到重复子问题。对于树上dp，就是要在每个子树中的问题一致化。

有这些显然的结论：

1. A往上走不如往下走。往上走相当于耽误时间，更容易完成任务。
2. A直接到达的点一定要染色完全。

但是这样还不够，不能直接判断每点的度数。这是因为可能在之前有“多余”的染色，可以提前把一些点染了。我们发现这个东西很难维护。那怎么做？

~~当然是放进dp状态里~~

我们设 $f_i$ 表示把 $i$ 的子树（不包括 $i$）进行染色，需要“多余染色” 的次数。

有转移方程 $f_i=\max\{0,\sum\limits_{e(i\to j)}(f_j+1)-k\}$。

这个是很好推的吧。

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
const int MAXN = 3e5 + 5;
int n, ver[MAXN << 1], nxt[MAXN << 1], head[MAXN << 1], cnt, k;
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
int dfs(int u, int f) {
	int ans = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i];
		ans += (1 + dfs(v, u));
	}
	return max(0, ans - k);
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	int l = 0, r = n-1, ans = -1;
	while(l <= r) {
		k = (l + r) >> 1;
		if(dfs(1, 0) == 0) {ans = k; r = k-1;}
		else l = k+1;
	}
	printf("%d\n", ans);
	return 0;
}
```

