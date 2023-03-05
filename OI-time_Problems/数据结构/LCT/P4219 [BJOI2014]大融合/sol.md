# P4219 [BJOI2014]大融合 解题报告

[P4219 大融合](https://www.luogu.com.cn/problem/P4219)

## 题目大意

动态维护一个森林，完成以下操作：

1. 连边 $(u,v)$。
2. 查询假如把边 $(u,v)$ 割断，形成的两个连通块的大小的乘积。**值得注意的是**，这个操作并不会真正割断边。

点数 $n\le 10^5$，询问数 $q\le 10^5$。

## 解题思路

看到连边，我们可以想到 LCT。那么我们可以发现，第二个操作其实是查询子树 $sz$ 和。

那么问题来了，由于 LCT 辅助树的特性“认父不认子”，我们无法方便地维护。怎么办？

答案是：额外的维护 **虚子树** 信息。即对于每一个节点 $u$，在维护 子树节点数 $sz$ 外，再维护一个 虚子树节点数 $szv$。即 $szv_x=\sum\limits_y sz_y[fa_y=x\and son_x\ne y]$。

如果我们正确的维护 $szv_x$ ，就有 `upd(p)` 为

```cpp
void upd(int p) {
    e[p].sz = e[e[p].ls].sz + e[e[p].rs].sz + 1 + e[p].szv;
}
```

应该很好理解。

那么接下来要做的，就是讨论：哪些函数会使 $szv$ 改变。

显然：**使虚边消失或使虚边生成的函数会使** $szv$ **改变。**

`upd` ,`psd` ,`rtt`,`splay` 只在单棵splay上操作，不会影响虚边的改变。

`access` 则会变化了。它使一个节点的右儿子发生了变化，所以这里要进行更新：

```cpp
void access(int p) {
    for(int y = 0; p; y = p, p = e[p].fa) 
        splay(p), e[p].szv += e[e[p].rs].sz, e[p].rs = y, e[p].szv -= e[e[p].rs].sz, upd(p);
}
```

`mkrt` 没有虚边的改变，不管。

`getrt` 不用管。

`link` 则要管了。

```cpp
void link(int x, int y) {
    mkrt(x); access(y); splay(y);
    e[x].fa = y; e[y].szv += e[x].sz; upd(y);
}
```

这里为什么要把 $y$ 搞到连通块的根呢?平常我们可以直接改是因为虚边不会影响 $y$ 维护的值。但是如果要额外信息，那就得更新 $y$ 到其连通块上所有节点的值。

`cut` 是 实边 $\to$ 没边，不涉及虚边。不管。

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
char readc() {
	char c = getchar();
	for(; c != 'A' && c != 'Q'; c = getchar());
	return c;
}
#define ls ch[0]
#define rs ch[1]

const int MAXN = 1e5 + 5;
int n, q;
struct Node {int fa, ch[2], sz, rev, szv;}e[MAXN];
int nrt(int p) {return e[e[p].fa].ls == p || e[e[p].fa].rs == p;}
int idy(int p) {return e[e[p].fa].rs == p;}
void upd(int p) {e[p].sz = e[e[p].ls].sz + e[e[p].rs].sz + 1 + e[p].szv;}
void psdrev(int p) {if(p) swap(e[p].ls, e[p].rs), e[p].rev ^= 1;}
void psd(int p) {if(e[p].rev) psdrev(e[p].ls), psdrev(e[p].rs), e[p].rev = 0;}
void psdall(int p) {if(nrt(p)) psdall(e[p].fa);   psd(p);}
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
void access(int p) {for(int y = 0; p; y = p, p = e[p].fa) splay(p), e[p].szv += e[e[p].rs].sz, e[p].rs = y, e[p].szv -= e[e[p].rs].sz, upd(p);}
void mkrt(int p) {access(p); splay(p); psdrev(p);}
void split(int x, int y) {mkrt(x); access(y); splay(y);}
void link(int x, int y) {mkrt(x); access(y); splay(y); e[x].fa = y; e[y].szv += e[x].sz; upd(y);}


int main() {
	n = read(), q = read();
	for(int i = 1; i <= n; i++) e[i] = (Node){0, {0, 0}, 1, 0, 0};
	for(int i = 1; i <= q; i++) {
		char c = readc();
		if(c == 'A') {
			int x = read(), y = read();
			link(x, y);
		} else {
			int x = read(), y = read();
			split(x, y);
			printf("%lld\n", 1ll * (e[x].szv+1) * (e[y].szv+1));
		}
	}
	return 0;
}
```



