# 动态树问题，Link Cut Tree 学习笔记

@[toc]
## 前言

我的学习资料：

[FlashHu的博客1](https://www.cnblogs.com/flashhu/p/8324551.html)

[FlashHu的博客2](https://www.cnblogs.com/flashhu/p/9498517.html)

[oi-wiki——Link Cut Tree](https://oi-wiki.org/ds/lct/)

这几篇博客都很经典。

## 动态树问题

同样是维护树，动态树比树链剖分更加困难。它多了两种操作：Link（连边），Cut（断边）。动态树其实不是一种算法，而是一种思想，我们要维护一个动态的森林。

OI中，我们常常用 LCT（Link-Cut Tree）来进行动态树维护。

## 模板题引入

[P3690 【模板】Link Cut Tree （动态树）](https://www.luogu.com.cn/problem/P3690)

>   维护一棵树，点有点权，进行下列操作：
>
>   1.  求路径点权异或和。
>   2.  Link（连边）
>   3.  Cut（断边）
>   4.  单点修改点权。
>
>   保证任意时刻都是一棵树。

这就是个经典的动态树问题。

模板题，不会的同学请自行点击上述博客进行学习。下面给出我的模板（压行警告）。

时间复杂度应为 $O(m\log n)$（$m$ 次操作，每次 $O(\log n)$）

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
const int MAXN = 1e5 + 5;
int n, m, val[MAXN];
namespace LCT {
	#define ls ch[0]
	#define rs ch[1]
	struct Node {int ch[2], fa, rev, sum;}e[MAXN];
	int nrt(int x) {return e[e[x].fa].ls == x || e[e[x].fa].rs == x;}
	int idy(int x) {return e[e[x].fa].rs == x;}
	void upd(int x) {e[x].sum = e[e[x].ls].sum ^ e[e[x].rs].sum ^ val[x];}
	void psdrev(int x) {if(x) swap(e[x].ls, e[x].rs), e[x].rev ^= 1;}
	void psd(int x) {if(e[x].rev) e[x].rev = 0, psdrev(e[x].ls), psdrev(e[x].rs);}
	void psdall(int x) {if(nrt(x)) psdall(e[x].fa); psd(x);}
	void rtt(int x) {
		int y = e[x].fa, z = e[y].fa, k = idy(x), s = e[x].ch[k^1];
		e[x].fa = z; if(nrt(y)) e[z].ch[idy(y)] = x;
		e[y].fa = x; e[x].ch[k^1] = y;
		e[s].fa = y; e[y].ch[k] = s;
		upd(y); upd(x);
	}
	void splay(int x) {
		psdall(x);
		for(int y = e[x].fa; nrt(x); rtt(x), y = e[x].fa)
			if(nrt(y)) rtt(idy(x) == idy(y) ? y : x);
	}
	void access(int x) {for(int y = 0; x; y = x, x = e[x].fa) splay(x), e[x].rs = y, upd(x);}
	void mkrt(int x) {access(x); splay(x); psdrev(x);}
	int getrt(int x) {access(x); splay(x); while(e[x].ls) psd(x = e[x].ls); splay(x); return x;}
	void split(int x, int y) {mkrt(x); access(y); splay(y);}
	void link(int x, int y) {mkrt(x); if(getrt(y) != x) e[x].fa = y;}
	void cut(int x, int y) {mkrt(x); if(getrt(y) == x && e[y].fa == x && e[y].ls == 0) e[x].rs = e[y].fa = 0, upd(x);}
}
using namespace LCT;

int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) val[i] = read();
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read(), y = read();
		if(opt == 0) {split(x, y); printf("%d\n", e[y].sum);}
		else if(opt == 1) link(x, y);
		else if(opt == 2) cut(x, y);
		else {
			splay(x); val[x] = y; upd(x);
		}
	}
	return 0;
}
```

## LCT应用 & 技巧

接下来的题目基本选了FlashHu的博客的题目（FlashHu yyds）。

### 类型1：维护路径信息

如果没有 Link 和 Cut 操作，那么其实可以用树链剖分来完成。尽管 树链剖分一般是 $O(n\log^2 n)$，比 LCT 多了个 $\log$，但是一般来说常数上树剖完虐 LCT。

只要 `split`，再在 Splay 上进行操作即可，转化为Splay的查询和修改操作。

典型例题有

[P3203 [HNOI2010]弹飞绵羊](https://www.luogu.com.cn/problem/P3203)

[P1501 [国家集训队]Tree II](https://www.luogu.com.cn/problem/P1501)

### 类型2：维护连通性与边双

1. 动态树上维护连通性相当简单，用 `getrt` 操作得到两个树的根进行比对即可。或者还有种写法，先`mkrt` 一个点，再判断另一个点 `getrt` 后是不是这个点。

2. 维护边双：LCT可以结合并查集维护边双缩点树的动态加边和查询。这是很好用的操作。

典型例题有

[P3950 部落冲突](https://www.luogu.com.cn/problem/P3950) （连通性）

[P2542 航线规划](https://www.luogu.com.cn/problem/P2542) （边双）[我的题解](https://blog.csdn.net/qq_41996523/article/details/113130182)

### 类型3：维护边权

众所周知，树剖上维护边权的话，由于树剖的 **父子关系确定**，通常可以方便地用儿子节点的点权来代替边权。但是在LCT上，**父子关系不确定**，这种方法就失去其用武之地了。

我们一般用 **边化点** 的办法来解决。把每条边也变成LCT上的节点，这样就可以正常操作了。只不过连边、断边要操作2次。具体的用途很多，常见的是动态维护最小（大）生成树。

典型例题有

[P4172 [WC2006]水管局长](https://www.luogu.com.cn/problem/P4172) （动态维护最小生成树）

[P2387 [NOI2014] 魔法森林](https://www.luogu.com.cn/problem/P2387) （同上）

[P4234 最小差值生成树](https://www.luogu.com.cn/problem/P4234)



