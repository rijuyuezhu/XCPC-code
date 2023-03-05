# LOJ #6053. 简单的函数 解题报告

[link](https://loj.ac/p/6053)。

## 题目大意

已知函数 $f(x)$ 满足：

1.  $f(1)=1$。
2.  $f(p^c)=p\oplus c$， 其中 $p$ 是质数，$\oplus$ 表示异或。
3.  当 $a\perp b$ 时，有 $f(ab)=f(a)f(b)$ 。

请求出 $\sum\limits_{i=1}^nf(i)\bmod (10^9+7)$。

-   $1\le n\le 10^{10}$

## 解题思路

这是积性函数求前缀和的题目，不难想到使用 Min_25 筛。

回忆一下 Min_25 筛的使用条件：

1.  积性函数。
2.  已知素数及素数的幂处的取值。

先找到一个 $f'(x)$ 使得:

1.  $f'(x)$ 是完全积性的。
2.  $f'(x)$ 在素数处的取值与 $f(x)$ 一致。
3.  $f'(x)$ 可快速求前缀和。

但我们发现，这样的 $f'(x)$ 似乎很难找。根据定义：
$$
f(p)=\left\{
\begin{matrix}
p+1; & (p=2)\\
p-1. & (p > 2)
\end{matrix}
(p\in \mathbb P)
\right.
$$
我们不妨做一个“修正”，在计算 $G(n)$ 的时候把 $f(p)$ 看作是 $p-1$ ，在计算 $S(n,\cdot)$ 时再弥补。这样我们只要定义 $f'_1(x)=x$, $f'_2(x)=1$ ，分别计算 $G_1,G_2$， 最后相减即可。

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
const ll MAXN = 1e10 + 5;
const int MAXK = 5e5 + 5, P = 1e9 + 7;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll n, sn, pr[MAXK], sp2[MAXK], sp1[MAXK], w[MAXK], g1[MAXK], g2[MAXK];
int ip[MAXK], tot, num, id1[MAXK], id2[MAXK];
void pre_gao(int n) {
	ip[1] = 1; 
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			sp1[tot] = pls(sp1[tot-1], i);
			sp2[tot] = pls(sp2[tot-1], 1);
		}
		for(int j = 1; j <= tot && i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
ll S(ll x, int k) {
	if(pr[k] >= x) return 0;
	int t = x <= sn ? id1[x] : id2[n / x];
	ll ret = mns(mns(g1[t], sp1[k]), mns(g2[t], sp2[k]));
	if(n >= 2 && k == 0) ret = pls(ret, 2);
	for(int j = k+1; j <= tot && pr[j] * pr[j] <= x; j++) {
		ll p = pr[j];
		for(int e = 1; p <= x; e++, p *= pr[j]) {
			ret = pls(ret, mul(pr[j] ^ e, pls(S(x / p, j), int(e != 1))));
		}
	}
	return ret;
}
int main() {
	n = read(); sn = sqrt(n) + 1;
	pre_gao(sn);
	for(ll i = 1, j; i <= n; i = j + 1) {
		ll t = n / i; j = n / t;
		w[++num] = t;
		ll tmp = t % P;
		g1[num] = mns(tmp * (tmp + 1) / 2 % P, 1);
		g2[num] = mns(tmp, 1);
		if(t <= sn) id1[t] = num;
		else id2[n / t] = num;
	}
	for(int j = 1; j <= tot; j++)
		for(int i = 1; i <= num && pr[j] * pr[j] <= w[i]; i++) {
			ll nxt = w[i] / pr[j];
			int t = nxt <= sn ? id1[nxt] : id2[n / nxt];
			g1[i] = mns(g1[i], mul(pr[j],  mns(g1[t], sp1[j-1])));
			g2[i] = mns(g2[i], mns(g2[t], sp2[j-1]));
		}
	printf("%lld\n", pls(1, S(n, 0)));

	return 0;
}
```

