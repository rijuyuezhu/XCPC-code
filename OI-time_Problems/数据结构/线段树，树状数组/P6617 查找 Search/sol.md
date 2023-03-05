# P6617 查找 Search

[toc]

## 题目链接

[查找 Search](https://www.luogu.com.cn/problem/P6617)

## 题目大意

给一个长度为 $n$ 的序列 $a_i$ 和一个参数 $k$ ，有 $m$ 次操作。操作有两种：

1.  单点修改序列。
2.  给定一个区间 $[l,r]$ ，询问是否存在 $l\le i<j\le r$，满足 $a_i +a_j=w$。

-   $1\le n,m,w\le5\times 10^5,0\le a_i\le w$.
-   **强制在线**.

## 解题报告

我们先来看一个前置知识：

### PART 1

看这样一个小题目：

给定一个长度为 $n$ 的序列 $a_i$ ，两种操作:

1.  单点修改。
2.  查询区间是否有重复元素。

$1\le n\le 5\times 10^5$.

怎么解决?

套路性地维护每个数的后继。改为判断区间内是否 **存在** 一个数的后继亦在区间内。根据高中数学的知识，这是一种“存在问题”，我们可以转而判断区间后继的 **最小值** 是否在区间内。如何单点修改？只要用个set数组（下标为权值）记录每个值所有的下标，然后求前驱后继即可。

### PART 2

好，我们回到正题。

为了描述方便，我们把“两个数相加为 $w$ ”称为这两个数“互补”。

这道题怎么做？可以套路性地维护每个数的后缀中第一个与它互补的数，即互补意义下的“后继”。这样只要判断区间后继最小值即可完成操作2了。

完结撒花！（？）

猛地发现，这样根本维护不来。这个“互补后继”没有之前那道题的“相等后继”那么好的性质。可能有多个数的“互补后继”是同一个数，所以你可能需要改一连串的数。~~爆炸~~

根本上的原因是它不满足 **后继的后继仍然是它的后继这样一个性质**，我们就不能在单点修改时做到仅修改两个数（一个前驱一个后继），这样就没法维护了。

一种绝妙的方法是：不要看这么远。

举个例子：

```
w = 7
1 3 2 3 4 6
```

 位于第二、四位的3显然可以与4配对。但是，我只让第四位的3与4配对，第三位的3由于前面有另一个3的阻挡，不会与那个4配对。~~我在说啥~~

**换句话说：**一个数的后继只会在 **一段区间** 内查找，中间不能跨过与它相等的数。

容易发现这样更好维护，并且对答案毫无影响。

于是剩下的工作就是分类讨论了。注意细节。

## 代码详情

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
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
typedef set<int> SET;
const int MAXN = 5e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m, w, lans, f[MAXN], num[MAXN];
namespace Segtree {
#define ls o << 1
#define rs o << 1 | 1
	int val[MAXN << 2];
	void pushup(int o) {val[o] = min(val[ls], val[rs]);}
	void build(int o, int l, int r, int f[]) {
		if(l == r) {val[o] = f[l]; return ;}
		int m = (l + r) >> 1;
		build(ls, l, m, f); build(rs, m+1, r, f);
		pushup(o);
	}
	void mdypos(int o, int l, int r, int x, int v) {
		if(l == r) {val[o] = v; return ;}
		int m = (l + r) >> 1;
		if(x <= m) mdypos(ls, l, m, x, v);
		else mdypos(rs, m+1, r, x, v);
		pushup(o);
	}
	int query(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y) return val[o];
		int m = (l + r) >> 1;
		if(y <= m) return query(ls, l, m, x, y);
		else if(x > m) return query(rs, m+1, r, x, y);
		else return min(query(ls, l, m, x, y), query(rs, m+1, r, x, y));
	}
#undef ls
#undef rs
}
using namespace Segtree;
namespace Settree {
	SET s[MAXN];
	int a[MAXN];
	void ins(int v, int i) {
		s[v].insert(i);
	}
	void del(int v, int i) {
		s[v].erase(i);
	}
	void init() {
		for(int i = 1; i <= n; i++)
			ins(a[i], i);
	}
	void mdy(int i, int v) {
		del(a[i], i);
		a[i] = v;
		ins(a[i], i);
	}
	int pre1(int i) {//sameval
		SET::iterator it = s[a[i]].lower_bound(i);
		if(it == s[a[i]].begin()) return INF;
		return *--it;
	}
	int nxt1(int i) {//sameval
		SET::iterator it = s[a[i]].upper_bound(i);
		if(it == s[a[i]].end()) return INF;
		return *it;
	}
	int pre2(int i) {//buval
		SET::iterator it = s[w-a[i]].lower_bound(i);
		if(it == s[w-a[i]].begin()) return INF;
		return *--it;
	}
	int nxt2(int i) {
		SET::iterator it = s[w-a[i]].upper_bound(i);
		if(it == s[w-a[i]].end()) return INF;
		return *it;
	}
}
using namespace Settree;
void gao1(int i, int v) {
	int p1 = pre1(i), p2 = pre2(i);
	if(p1 != INF) {
		if(p2 == INF || p2 <= p1)
			mdypos(1, 1, n, p1, query(1, 1, n, i, i));
	}
	if(p2 != INF) {
		if(p1 == INF || p1 <= p2)
			mdypos(1, 1, n, p2, nxt1(i));
	}
	mdy(i, v);
	p1 = pre1(i), p2 = pre2(i);
	if(p1 != INF) {
		if(p2 == INF || p2 <= p1)
			mdypos(1, 1, n, p1, INF);
	}
	if(p2 != INF) {
		if(p1 == INF || p1 <= p2)
			mdypos(1, 1, n, p2, i);
	}
	int n1 = nxt1(i), n2 = nxt2(i);
	if(n2 == INF) mdypos(1, 1, n, i, INF);
	else {
		if(n2 <= n1) mdypos(1, 1, n, i, n2);
		else mdypos(1, 1, n, i, INF);
	}

}
bool gao2(int l, int r) {
	return query(1, 1, n, l, r) <= r;
}
int main() {
	n = read(), m = read(), w = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	init();
	for(int i = n; i >= 1; i--) {
		if(num[w-a[i]]) {
			if(!num[a[i]] || num[w-a[i]] <= num[a[i]]) f[i] = num[w-a[i]];
			else f[i] = INF;
		} else f[i] = INF;
		num[a[i]] = i;
	}
	build(1, 1, n, f);
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read(), y = read();
		if(opt == 1) {
			gao1(x, y);
		} else {
			if(gao2(x ^ lans, y ^ lans)) {
				printf("Yes\n");
				lans++;
			} else {
				printf("No\n");
			}
		}
	}
	return 0;	
}
```

