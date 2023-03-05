# P3227 [HNOI2013]切糕 解题报告

网络流，最小割。

## 题目链接

https://www.luogu.com.cn/problem/P3227

## 题目大意

给定一个价值函数 $w(x,y,z)\ (1\le x \le P, 1\le y \le Q, 1\le z\le R)$ 的取值，请构造一个二元函数 $f(x,y)\ (1\le x \le P,1\le y \le Q)$ 满足以下条件：

1. 对任意 $x\in[1,P],y\in[1,Q]$， 有 $1\le f(x,y) \le R$
2. 对任意 $x_1,x_2\in[1,P],y_1,y_2\in [1,Q],|x_1-x_2|+|y_1-y_2|=1$，有 $|f(x_1,y_1)-f(x_2,y_2)|\le D$，其中 $D$ 是一个给定参数。

求 $\sum_{(i,j)}w(i,j,f(i,j))$的最小值。

- $1\le P, Q, R\le 40, 0\le D\le R$

~~感觉更玄乎了~~

## 解题思路

考虑没有第二个限制怎么做。

一种思路是对于每个 $(x,y)$， 寻找 $w(x,y,i)$ 的最小值。但是没有拓展性。

另一种拓展性更高的方法是最小割。把选择一条边看成代价，于是在 $(x,y,k)$ 和 $(x,y,k+1)$ 之间连接 $w(x,y,k)$ 的边，设置超源和超汇，直接跑最小割。

 那么顺着这种思路，加上第二个限制怎么办？第二种限制告诉我们，如果相邻的 $(x,y)$ 选择的 $f(x,y)$ 相差超过 $D$ 就是不合法的，在网络中表示就是要删去两条边后图仍然联通。发现直接在 $(x_1,y_1,k)$ 和 $(x_2, y_2, k-D)$ 之间连边就可以了。

## 代码

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
const int MAXN = 45, MAXNODE = 70005, MAXEDGE = MAXNODE * 10;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
const int INF = 0x3f3f3f3f;
int P, Q, R, D, val[MAXN][MAXN][MAXN], id[MAXN][MAXN][MAXN], num, s, t, nxt[MAXEDGE], edg[MAXEDGE], head[MAXNODE], ver[MAXEDGE], cnt = 1;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; edg[cnt] = w; nxt[cnt] = head[u]; head[u] = cnt;
	ver[++cnt] = u; edg[cnt] = 0; nxt[cnt] = head[v]; head[v] = cnt;
}

int que[MAXNODE], hd, tl, d[MAXNODE];
bool bfs() {
	memset(d, 0x00, sizeof d);
	que[hd = tl = 1] = s; d[s] = 1;
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
int dfs(int u, int flow) {
	if(u == t) return flow;
	int rest = flow;
	for(int i = head[u]; i && rest; i = nxt[i])
		if(d[ver[i]] == d[u] + 1 && edg[i]) {
			int v = ver[i], w = edg[i];
			int k = dfs(v, min(w, rest));
			if(!k) d[v] = 0;
			edg[i] -= k;
			edg[i^1] += k;
			rest -= k;
		}
	return flow - rest;
}

int dinic() {
	int ans = 0, flow;
	while(bfs()) {
		while(flow = dfs(s, INF)) 
			ans += flow;
	}
	return ans;
}
int main() {
	P = read(), Q = read(), R = read(), D = read();
	s = ++num; t = ++num;
	for(int k = 1; k <= R; k++)
		for(int i = 1; i <= P; i++)
			for(int j = 1; j <= Q; j++)
				val[i][j][k] = read(), id[i][j][k] = ++num;
	for(int i = 1; i <= P; i++)
		for(int j = 1; j <= Q; j++)
			addedge(s, id[i][j][1], INF);
	for(int k = 1; k < R; k++)
		for(int i = 1; i <= P; i++)
			for(int j = 1; j <= Q; j++)
				addedge(id[i][j][k], id[i][j][k+1], val[i][j][k]);
	for(int i = 1; i <= P; i++)
		for(int j = 1; j <= Q; j++)
			addedge(id[i][j][R], t, val[i][j][R]);
	for(int k = D+1; k <= R; k++)
		for(int i = 1; i <= P; i++)
			for(int j = 1; j <= Q; j++) {
				for(int p = 0; p < 4; p++) {
					int nx = i + dx[p], ny = j + dy[p];
					if(nx >= 1 && nx <= P && ny >= 1 && ny <= Q) {
						addedge(id[i][j][k], id[nx][ny][k - D], INF);
					}
				}
			}
	printf("%d\n", dinic());
	return 0;
}
```

