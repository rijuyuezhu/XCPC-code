# P2542 [AHOI2005] 航线规划 解题报告

[题目链接](https://www.luogu.com.cn/problem/P2542)

## 题目大意

维护一个无向图，有以下两种操作：

1. 删边。
2. 询问两点间路径的必须边的条数。

保证任意时刻两点联通。

## 解题思路

删边显然不好弄，我们离线，反转时间变成加边。

两种思路：

### 一、树链剖分

我们先找出一颗生成树，我们看看加一条边会发生什么。由于保证时刻两点连通，这一条边一定会使一条链缩成一个点。其实我们可以直接使用边权来维护这个过程。一开始所有树上边的边权为1。要把一条链缩成一个点，就把这条路径上的所有的边权改为0。那查询就只要查询两点间路径和即可。

深入思考：如果没有保证任何时刻两点联通如何？

有这两种方法：

1. 改为用LCT维护边权
2. 其实按时间倒序地选边构成一颗生成树即可。还未加入的边的边权设为0。

### 二、LCT动态维护边双

LCT可以结合并查集动态维护边双。这里的维护有两种操作：

1. 维护边双之间的信息。
2. 动态 **加边**，完成缩点。

（在边双缩点图里减边怎么样也不好做，因为合成边双时信息丢失地厉害）。

这种方法里，我们真正意义上把一条链缩成了一个点。

我们看看怎么完成这个操作：我们使这条链上所有的点的并查集数组 $upto(i)$ 指向辅助树的根。然后断开这个根与其子树的链接。但是，access要稍作修改来保证信息传递的正确性。

```cpp
#include<cstdio>
#include<cstring>
#include<map>
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
typedef pair<int, int> pii;
const int MAXN = 3e4 + 5;
const int MAXM = 1e5 + 5;
const int MAXQ = 4e4 + 5;
struct Edge {int u, v;}ed[MAXM];
struct Qry {int op, u, v;}q[MAXQ];
map<pii, int> mp;
int n, m, dty[MAXM], q_num, upto[MAXN], ans[MAXQ];
int getup(int p) {return upto[p] == p ? p : upto[p] = getup(upto[p]);}
namespace LCT {
#define ls ch[0]
#define rs ch[1]
	struct Node {int ch[2], fa, rev, sz;}e[MAXN];
	int nrt(int p) {return e[e[p].fa].ls == p || e[e[p].fa].rs == p;}
	int idy(int p) {return e[e[p].fa].rs == p;}
	void psdrev(int p) {if(p) swap(e[p].ls, e[p].rs), e[p].rev ^= 1;}
	void psd(int p) {if(e[p].rev) e[p].rev = 0, psdrev(e[p].ls), psdrev(e[p].rs);}
	void psdall(int p) {if(nrt(p)) psdall(e[p].fa); psd(p);}
	void upd(int p) {e[p].sz = e[e[p].ls].sz + e[e[p].rs].sz + 1;}
	void rtt(int p) {
		int y = e[p].fa, z = e[y].fa, k = idy(p), s = e[p].ch[k^1];
		e[p].fa = z; if(nrt(y)) e[z].ch[idy(y)] = p;
		e[y].fa = p; e[p].ch[k^1] = y;
		e[s].fa = y; e[y].ch[k] = s;
		upd(y); upd(p);
	}
	void splay(int p) {
		psdall(p);
		for(int y = e[p].fa; nrt(p); rtt(p), y = e[p].fa)
			if(nrt(y)) rtt(idy(p) == idy(y) ? y : p);
	}
	void access(int p) {for(int y = 0; p; y = p, p = e[y].fa = getup(e[p].fa)) splay(p), e[p].rs = y, upd(p);}//here
	void mkrt(int p) {access(p); splay(p); psdrev(p);}
	int getrt(int p) {access(p); splay(p); while(e[p].ls) psd(p = e[p].ls); splay(p); return p;}
	void split(int x, int y) {mkrt(x); access(y); splay(y);}
}
using namespace LCT;
void dfs(int p, int rt) {//make the father of any node in the subtree become rt.
	if(!p) return ;
	dfs(e[p].ls, rt); dfs(e[p].rs, rt);
	upto[p] = rt;
}
void merge(int u, int v) {
	if(u == v) return ;
	mkrt(u);
	if(getrt(v) != u) {e[u].fa = v; return ;}
	dfs(e[u].rs, u);
	e[u].rs = 0; upd(u);
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) upto[i] = i, e[i] = (Node){{0, 0}, 0, 0, 1};
	for(int i = 1; i <= m; i++) {
		ed[i].u = read(), ed[i].v = read();
		mp[pii(ed[i].u, ed[i].v)] = i; mp[pii(ed[i].v, ed[i].u)] = i;
	}
	while(1) {
		int id = read();
		if(id == -1) break;
		int u = read(), v = read();
		q[++q_num] = (Qry){id, u, v};
	}
	for(int i = 1; i <= q_num; i++) if(q[i].op == 0) dty[mp[pii(q[i].u, q[i].v)]] = 1;
	for(int i = 1; i <= m; i++) if(!dty[i]) merge(getup(ed[i].u), getup(ed[i].v));
	for(int i = q_num; i >= 1; i--) {
		int u = getup(q[i].u), v = getup(q[i].v);
		if(q[i].op == 0) {
			merge(u, v);
		} else {
			split(u, v);
			ans[i] = e[v].sz - 1;
		}
	}
	for(int i = 1; i <= q_num; i++)
		if(q[i].op == 1)
			printf("%d\n", ans[i]);
	return 0;
}
```

