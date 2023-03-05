# P4841 [集训队作业2013]城市规划 解题报告

[link](https://www.luogu.com.cn/problem/P4841)

## 题目大意

求 $n$ 个点的简单有标号无向连通图的数目。

## 解法1

我们设 $n$ 个点的简单有标号无向连通图的数目为 $f_n$， $n$ 个点的简单有标号无向图（不一定连通）的数目为 $g_n$。

那么 $g_n$ 是相当好算的。考虑每两点之间边的有无，有 $g_n=2^{\mathrm C_n^2}$。

一个常用的套路，我们枚举1号点所在的连通块大小。
$$
g_n=\sum_{x=1}^n\left(\begin{matrix}n-1 \\ x-1\end{matrix}\right)f_xg_{n-x}
$$
这个组合数是为了选标号。

把组合数拆了，简单变形可得
$$
\dfrac {g_n}{(n-1)!}=\sum_{x+y=n}\dfrac{f_x}{(x-1)!}\dfrac{g_y}{y!}
$$
设 $g_n$ 的 EGF 为 $G(x)=\sum\limits_{n\ge 0}g_n\dfrac{x^n}{n!}$， $f_n$ 的 EGF 为$F(x)=\sum\limits_{n\ge0}f_n\dfrac{x^n}{n!}$，可得
$$
xG'(x)=xF'(x)*G(x)\\
\therefore F(x)=\int_0^x \dfrac{G'(x)}{G(x)}=\ln G(x)
$$
直接计算 $G(x)$ 系数再套一个板子即可。

这是一种用生成函数快速计算递推式的方法。

## 解法2

由于是有标号计数，我们直接设EGF。设 $F(x)$ 是简单有标号无向连通图的EGF，$G(x)$ 是简单有标号无向图的EGF。

那么 $G(x)$ 的各项系数是很好求的（同上）。

我们考虑普通的无向图是由若干连通块“拼接”得到的，于是我们可以枚举连通块数量。
$$
G(x)=\sum_{k\ge 0}\dfrac{F^k(x)}{k!}=\exp F(x)
$$
这里 $F^k(x)$ 是因为是 $k$ 个连通块组成的图，而 $k!$ 是为了消除连通块之间的顺序。

那么显然 $F(x)=\ln G(x)$ 。

这里直接使用了生成函数完成组合对象之间关系的推导。

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
#define clr(f, s, e) memset(f + (s), 0x00, sizeof(ll) * ((e) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(ll) * (n))
const int MAXN = (1 << 18)+5, P = 1004535809, G = 3, invG = 334845270;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll qpow(ll a, ll n) {ll ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
ll fac[MAXN], ifac[MAXN], inv[MAXN], _g[2][MAXN], tr[MAXN], pow2[MAXN], tf;
void init() {
	fac[0] = 1; for(int i = 1; i < MAXN; i++) fac[i] = mul(fac[i-1], i);
	ifac[MAXN-1] = qpow(fac[MAXN-1], P-2); for(int i = MAXN-2; i >= 0; i--) ifac[i] = mul(ifac[i+1], i+1);
	inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = mul(P - P / i, inv[P % i]);
	for(int l = 2; l < MAXN; l <<= 1) _g[1][l] = qpow(G, (P-1) / l), _g[0][l] = qpow(invG, (P-1) / l);
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(ll* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l) {
			ll gn = 1;
			for(int j = i; j < i+k; j++, gn = mul(gn, _g[fl][l])) {
				ll tt = mul(f[j+k], gn);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
		}
	if(!fl) {
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], inv[lim]);
	}
}
void Mul(ll* f, ll* g, ll* h, int n) {
	static ll a[MAXN], b[MAXN];
	int lim = getlim(n);
	cpy(f, a, n); clr(a, n, lim);
	cpy(g, b, n); clr(b, n, lim);
	NTT(a, lim, 1); NTT(b, lim, 1);
	for(int i = 0; i < lim; i++) h[i] = mul(a[i], b[i]);
	NTT(h, lim, 0); clr(h, n, lim);
}
void Inv(ll* f, ll* g, int n) {
	static ll a[MAXN];
	if(n == 1) {g[0] = qpow(f[0], P-2); return;}
	Inv(f, g, (n+1) >> 1);
	int lim = getlim(n);
	clr(g, (n+1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	NTT(g, lim, 1); NTT(a, lim, 1);
	for(int i = 0; i < lim; i++) g[i] = (2 - a[i] * g[i] % P + P) * g[i] % P;
	NTT(g, lim, 0); clr(g, n, lim);
}
void Deriv(ll* f, ll* g, int n) {
	for(int i = 1; i < n; i++) g[i-1] = mul(f[i], i);
	g[n-1] = 0;
}
void Integ(ll* f, ll* g, int n) {
	for(int i = 1; i < n; i++) g[i] = mul(f[i-1], inv[i]);
	g[0] = 0;
}
void Ln(ll* f, ll* g, int n) {
	static ll a[MAXN], b[MAXN];
	Inv(f, a, n); Deriv(f, b, n);
	Mul(a, b, a, n); Integ(a, g, n);
}
int n;
ll f[MAXN], g[MAXN];
int main() {
	init();
	n = read();
	for(int i = 0; i <= n; i++) g[i] = mul(qpow(2, 1ll * i * (i-1) / 2), ifac[i]);
	Ln(g, f, n+1);
	printf("%lld\n", mul(f[n], fac[n]));
	return 0;
}
```

