# [HNOI2016]矿区 解题报告

## 题目链接

[P3249 HNOI2016 矿区 - 洛谷](https://www.luogu.com.cn/problem/P3249)

## 前置知识

图论基础概念， 平面图、对偶图的相关概念。

推荐博客：

1.  [平面图转换成对偶图的应用 - GFY](https://www.cnblogs.com/qzqzgfy/p/5578785.html)
2.  [网络流小结（平面图转对偶图） ](https://zybuluo.com/ysner/note/1098815)
3.  [关于平面图到对偶图的转化_Le Petit Prince](https://blog.csdn.net/maxmercer/article/details/77976666)

本篇文章的主要内容**不是概念的介绍与证明**，而是**代码实现**。众所周知平面图转对偶图的代码很难写，所以我写一份注释详细的代码来解释解释。

## 平面图转对偶图

我们先不讲这题，而是先说说怎么把平面图转成对偶图。一般有以下几个步骤:

1.  把每条无向边拆成两条有向边，那么全部的边**属于且仅属于**一个面。
2.  对于每个有向边，找到**下一条边**，即一条起点是它的终点，并且中间没有“跨越”其它边的边。
3.  遍历一条有向边的“下一条边”，形成了一个环。那么这个环中的所有有向边围成了一个面。值得注意的是，无穷面的确定可以使用**面积**为负来判断。
4.  再遍历每条无向边（当然具体实现有所差异），在它所属的两个面之间连边。

## 本题思路

最好看看这个内容，不然有些代码还看不懂。。

平面图中的面相当于对偶图中的点。于是我们把 $s$ 和 $s^2$ 视为点权。询问的是一个“连通面”内的值，转化为对偶图就是某个“连通块”的权值。我们可以在对偶图中找棵生成树，把这个问题转化为子树和的问题。

## 具体代码（重要）

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 2e5 + 5;
const int MAXM = 1.2e6 + 5;
const db eps = 1e-10;
int n, m, Q;

struct Point {ll x, y;}p[MAXN];
//点 or 向量的坐标
Point vec(const Point& A, const Point& B) {return (Point){B.x - A.x, B.y - A.y};}
//获取向量AB
ll operator * (const Point& A, const Point& B) {return A.x * B.y - A.y * B.x;}
//计算A叉B（正表示逆时针转，负表示顺时针转）

struct Edge {int u, v, id; db ang;}e[MAXM];
//存边。表示边(u->v), 编号为id, 相对u的极角是ang
bool operator < (const Edge& A, const Edge& B) {return fabs(A.ang - B.ang) < eps ? A.v < B.v : A.ang < B.ang;}
//按极角排序
int cnt = 1; vector<Edge> G[MAXN];
//这里cnt初始化为1是用了一种异或存储无向边的技巧。假如(u,v)的编号为i，那么(v,u)的编号就是i^1
//G是平面图
void addedge(int u, int v) {
	cnt++; e[cnt] = (Edge){u, v, cnt, atan2(p[v].y - p[u].y, p[v].x - p[u].x)};
	G[u].push_back(e[cnt]);
}//存边。

int nxt[MAXM], pos[MAXM], num, rt;
//nxt便是“下一条边”，pos表示一条边所属的面的编号，num是当前面的编号，rt表示外部面的编号
ll S[MAXM], Sq[MAXM];
//S表示面积，Sq表示面积的平方。当然这两个值为了计算的方便都会乘上一个倍数
vector<Edge> g[MAXM];
//g是对偶图
void buildGraph() {
	for(int i = 1; i <= n; i++) sort(G[i].begin(), G[i].end());//极角排序
	for(int i = 2; i <= cnt; i++) {
		int v = e[i].v; vector<Edge>::iterator _e = lower_bound(G[v].begin(), G[v].end(), e[i ^ 1]);
		if(_e == G[v].begin()) _e = G[v].end();
		_e--; nxt[i] = _e->id;
		/* 
		 * 对于每一条边(u,v)如何求出它的“下一条边”？
		 * 首先找到它的反向边(v,u)。这里用lower_bound方便地找到了(v,u)。这里的*_e就是(v,u)
		 * 然后再稍微把这条边的极角减小一下，即顺时针转一下便可得到“下一条边”
		 * 画画图就会发现，这个下一条边就是(u,v)逆时针转过最小的角度的那条边。这为我们叉乘求面积提供了方便
		 */
	}
	for(int i = 2; i <= cnt; i++) {
		if(pos[i]) continue;
		pos[i] = pos[nxt[i]] = ++num;
		for(int j = nxt[i]; e[j].v != e[i].u; j = nxt[j], pos[j] = num)
			S[num] += (vec(p[e[i].u], p[e[j].u])) * (vec(p[e[i].u], p[e[j].v]));
		if(S[num] <= 0) rt = num;
		/*
		 * 此处遍历了一条边的下一条边，形成了一个环。环中的所有边都属于同一个面。
		 * 值得注意的是，面积小于0的那个面即是外部面
		 */
	}
	for(int i = 2; i <= cnt; i++)
		g[pos[i]].push_back((Edge){pos[i], pos[i ^ 1], i, 0});
		//建立对偶图。
}

bool vis[MAXM], iste[MAXM];
//vis表示当前点（对偶图中的点）是否访问过；iste即is tree edge表示是否是树生成树中的边
int fa[MAXM];
//记录每个点的父亲
void dfs(int u) {
	Sq[u] = S[u] * S[u]; S[u] *= 2; vis[u] = 1;
	//这里面积、面积的平方都变为了实际值的四倍。
	for(int i = 0, up = g[u].size(); i < up; i++) {
		int v = g[u][i].v; if(vis[v]) continue;
		iste[g[u][i].id] = iste[g[u][i].id ^ 1] = 1;
		fa[v] = u; dfs(v); S[u] += S[v]; Sq[u] += Sq[v];
	}
}

ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
ll ans1, ans2;//存储答案的分子分母
int qry[MAXN];
int main() {
	n = read(), m = read(), Q = read();
	for(int i = 1; i <= n; i++) {
		ll x = read(), y = read(); p[i] = (Point){x, y};
	}
	for(int i = 1; i <= m; i++) {
		int a = read(), b = read(); addedge(a, b); addedge(b, a);
	}
	buildGraph(); //建对偶图
	dfs(rt);//跑出对偶图的一棵生成树，并求好子树和
	while(Q--) {
		int d = (read() + ans1) % n + 1;
		for(int i = 1; i <= d; i++) qry[i] = (read() + ans1) % n + 1;
		qry[d+1] = qry[1]; ans1 = 0, ans2 = 0;
		for(int i = 1; i <= d; i++) {
			int u = qry[i], v = qry[i+1];
			Edge ed = (Edge){u, v, 0, atan2(p[v].y - p[u].y, p[v].x - p[u].x)};
			vector<Edge>::iterator _e = lower_bound(G[u].begin(), G[u].end(), ed);
			int j = _e->id; if(!iste[j]) continue;
			if(fa[pos[j]] == pos[j ^ 1]) ans1 += Sq[pos[j]], ans2 += S[pos[j]];
			else ans1 -= Sq[pos[j ^ 1]], ans2 -= S[pos[j ^ 1]];
		}
		ll tmp = gcd(ans1, ans2);
		ans1 /= tmp; ans2 /= tmp;
		printf("%lld %lld\n", ans1, ans2);
		/*
		 * 这一段挺好理解的
		 */
	}
	return 0;
}
```

