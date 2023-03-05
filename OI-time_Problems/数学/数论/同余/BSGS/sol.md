# BSGS算法 学习笔记

[toc]

## 简介

BSGS(Baby-step Giant-step，大步小步，~~北上广深，拔山盖世~~)算法，是用来求解高次同余方程 $a^x\equiv b\pmod n,a\perp n$，或者换个写法 $x\equiv\log_ab\pmod n$，即离散对数。

## 前置知识

**欧拉定理：**$a^{\varphi(n)}\equiv 1\pmod n,a\perp n$.

## 算法思想

我们根据欧拉定理，$a^x\bmod n$的值每经过 $\varphi(n)$ 就会有个循环，所以理论上我们只要看看 $x\in[1,\varphi(n)]$ 内有没有 $x$ 满足 $a^x\equiv b$。

其实也并不一定非得是 $\varphi(n)$ 吧，检验的范围再大一点也不影响结果，为了省去这个求 $\varphi(n)$ 的过程~~（分解因数怪麻烦的）~~，我们直接检验 $x\in [1,n-1]$ 中有没有解。这个算法的时间复杂度是 $\mathcal O(n)$ 的。	而使用BSGS算法可以优化到 $\mathcal O(\sqrt n)$。

算法采用一种分块解决的思想，这也是 “大步” “小步” 的由来。下面是算法的推导过程。

$$a^x\equiv b\pmod n$$

设置一个参数 $k$ ，把 $x$ 写成一种稍有改变的“带余除法”的形式。

$$x=pk-q(1\le p\le\lfloor \dfrac{n}{k}\rfloor+1,1\le q \le k)$$

这样 $x$ 的值域可以包含 $[0,n-1]$ 的整个区间。

于是

$$a^{pk-q}\equiv b\pmod n$$

$$a^{pk}\equiv ba^q\pmod n$$

把这个式子分成左右两部分，先枚举 $q\in[1,k]$，计算处所有的$ba^q\bmod n$，存入一个HASH表中。接下来，只要再枚举 $p\in[1,\lfloor \dfrac{n}{k}\rfloor+1]$ ，计算 $a^{pk}$，在HASH表中查找是否存在这样的 $q$ 满足上面那个等式即可。如果有多个 $q$，应选择最大的那个，这样可以使得 $x=pk-q$ 最小。

时间复杂度为 $\mathcal O(k + \lfloor \dfrac{n}{k}\rfloor)$，显然当 $k=\sqrt n$ 时有最小复杂度为 $\mathcal O(\sqrt n)$。

## 例题

[P3846 [TJOI2007] 可爱的质数/【模板】BSGS](https://www.luogu.com.cn/problem/P3846)

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
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
#define ing long long
namespace HS {
	const int MAXNODE = (1 << 16) + 10;
	const int BS = 1491001;
	int nxt[MAXNODE], num[MAXNODE], val[MAXNODE], cnt, head[BS];
	int hs(int x) {
		return x % BS;
	}
	void ins(int x, int i) {
		int key = hs(x);
		num[++cnt] = x; val[cnt] = i; nxt[cnt] = head[key]; head[key] = cnt;
	}
	int qry(int x) {
		int key = hs(x);
		int mx = -1;
		for(int i = head[key]; i; i = nxt[i]) 
			if(num[i] == x) mx = max(mx, val[i]);
		return mx;
	}
}
int qpow(int a, int n, int mod) {
	int ret = 1;
	for(; n; n >>= 1, a = 1ll * a * a % mod)
		if(n & 1) ret = 1ll * ret * a % mod;
	return ret;
}
int p, b, n, m;
signed main() {
	p = read(), b = read(), n = read();
	if(b % p == 0 && n) {
		printf("no solution\n");
		return 0;
	}
	m = sqrt(p);
	for(int i = 1, k = 1ll * n * b % p; i <= m; i++, k = 1ll * k * b % p)
		HS::ins(k, i);
	for(int i = 1, bas = qpow(b, m, p), k = bas; i <= m+1; i++, k = 1ll * k * bas % p) {
		int t = HS::qry(k);
		if(t != -1) {
			printf("%lld\n", 1ll * m * i - t);
			return 0;
		}
	}
	printf("no solution\n");
	return 0;
}
```

