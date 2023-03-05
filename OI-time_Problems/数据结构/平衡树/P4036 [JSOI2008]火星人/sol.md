# P4036 [JSOI2008]火星人 

## 题目链接

[[JSOI2008]火星人](https://www.luogu.com.cn/problem/P4036)

## 题目大意

维护一个字符串，有以下三种操作：

1. 给出两个整数 $a, b$，询问后缀 $a$ 和后缀 $b$ 的LCP.
2. 单点修改某个字符
3. 添加字符

- 操作数 $\le150,000$ ；字符串长度 $\le100,000$ 。

## 解题报告

由于有修改与添加，常规的字符串做法（SAM,SA）似乎都行不通。

我们想想有什么办法可以动态的完成这项任务？

**HASH**！

使用进制位哈希，那么我们可以采用二分的方法来求两个后缀的LCP了。

至于单点修改和添加字符，发现可以用splay维护序列来完成。

很好写啦！

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXL = 100005;
const int B = 42323;
ull Base[MAXL];
namespace Splay {
#define L e[x].ls
#define R e[x].rs
#define ls ch[0]
#define rs ch[1]
	struct Node {
		int fa, ch[2];
		int siz;
		ull val, sum;
	}e[MAXL];
	int cnt, rt;
	void init() {
		cnt = rt = 0;
		e[rt = ++cnt] = (Node){0, {0, 0}, 0, 0, 0};
		e[e[rt].ch[1] = ++cnt] = (Node){rt, {0, 0}, 0, 0, 0};
	}
	int crenode(ull v, int f) {
		e[++cnt] = (Node){f, 0, 0, 1, v, v};
		return cnt;
	}
	void upd(int x) {
		e[x].siz = e[L].siz + e[R].siz + 1;
		e[x].sum = (e[L].sum * B + e[x].val) * Base[e[R].siz] + e[R].sum;
	}
	void linkto(int x, int f, int w) {e[x].fa = f; e[f].ch[w] = x;}
	int idy(int x) {return e[e[x].fa].rs == x;}
	void rotate(int x) {
		int y = e[x].fa, z = e[y].fa, ix = idy(x), iy = idy(y), s = e[x].ch[ix^1];
		linkto(s, y, ix); linkto(y, x, ix^1); linkto(x, z, iy);
		upd(y); upd(x);
	}
	void splay(int x, int to) {
		while(e[x].fa != to) {
			int y = e[x].fa;
			if(e[y].fa != to) rotate(idy(x) == idy(y) ? y : x);
			rotate(x);
		}
		if(!to) rt = x;
	}
	int kth(int k) {
		k++;//guard node
		int x = rt;
		while(k) {
			if(k <= e[L].siz) x = L;
			else {
				k -= e[L].siz + 1;
				if(!k) break;
				x = R;
			}
		}
		return x;
	}
	int split(int xx, int yy) {
		int l = kth(xx-1), r = kth(yy+1);
		splay(l, 0); splay(r, l);
		return e[r].ls;
	}
	int qry(int xx, int yy) {
		int x = split(xx, yy);
		return e[x].sum;
	}
	void ins(ull v, int k) {
		split(k+1, k);
		e[e[rt].rs].ls = crenode(v, e[rt].rs);
		upd(e[rt].rs); upd(rt);
	}
	void mdy(ull v, int k) {
		int x = split(k, k);
		e[x].val = v;
		splay(x, 0);
	}
#undef L
#undef R
#undef ls
#undef rs
}
using namespace Splay;
int n, m;
char s[MAXL];
bool check(int a, int b, int l) {
	return qry(a, a+l-1) == qry(b, b+l-1);
}
int work(int a, int b) {
	int len = e[rt].siz - 2;
	int l = 1, r = min(len - a + 1, len - b + 1), ans = 0;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(check(a, b, m)) ans = m, l = m+1;
		else r = m-1;
	}
	return ans;
}
int main() {
	Base[0] = 1;
	for(int i = 1; i < MAXL; i++) Base[i] = Base[i-1] * B;
	scanf("%s", s+1); n = strlen(s+1);
	m = read();
	init();
	for(int i = 1; i <= n; i++) ins(s[i], i-1);
	for(int i = 1; i <= m; i++) {
		char s[6], d[6];
		scanf("%s", s);
		if(s[0] == 'Q') {
			int x = read(), y = read();
			printf("%d\n", work(x, y));
		} else if(s[0] == 'R') {
			int x = read(); scanf("%s", d);
			mdy(d[0], x);
		} else {
			int x = read(); scanf("%s", d);
			ins(d[0], x);
		}
	}
	return 0;
}
```

