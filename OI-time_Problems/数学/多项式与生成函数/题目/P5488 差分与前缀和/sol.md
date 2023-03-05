# P5488 差分与前缀和 解题报告

[link](https://www.luogu.com.cn/problem/P5488)

## 题目大意

给定一个长度为 $n$ 的序列 $a_i$ ，求其 $k$ 阶差分或前缀和。对 1004535809 取模。

$1\le n \le 10^5$，$0\le a_i\le 10^9$，$1\le k\le 10^{2333},k\not\equiv 0\pmod {1004545809}$

## 解题思路

一道生成函数裸题。

设序列的OGF为 $A(x)=\sum\limits_{n\ge 0}a_nx^n$。

则求差分为 $A^{-}(x)=(1-x)A(x)$，$k$ 阶差分是 $A^{k-}=(1-x)^kA(x)$。

这是因为 
$$
A^-(x)=[x^0]A(x)+\sum_{n\ge 1}(a_n-a_{n-1})x^n\\
=[x^0]A(x)+\sum_{n\ge 1}a_nx^n-\sum_{n\ge 1}a_{n-1}x^n\\
=A(x)-x\sum_{n\ge 1}a_{n-1}x^{n-1}\\
=A(x)-xA(x)=(1-x)A(x)
$$
而求前缀和为 $A^+(x)=\dfrac1{1-x}A(x)$， $k$ 阶前缀和为 $A^{k+}=\dfrac 1 {(1-x)^k}A(x)$。

这是因为
$$
A^+(x)=\sum_{n\ge 0}\sum_{i=0}^na_i\cdot x^n\\
=\sum_{i\ge 0}a_i\sum_{n\ge i}x^n\\
=\sum_{i\ge 0}a_i\dfrac{x^i}{1-x}\\
=\dfrac 1 {1-x}\sum_{i\ge 0}a_ix^i=\dfrac 1 {1-x}A(x)
$$
所以只要求 $(1-x)^{\alpha}$ ，再乘起来即可。那么直接用个 Ln 和 Exp 即可。

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
#define cpy(f, g, len) memcpy(g, f, sizeof(ll) * (len))
const int MAXN = 1 << 18, P = 1004535809, G = 3, invG = 334845270;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll qpow(ll a, int n) {ll ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a);  return ret;}
int tr[MAXN], tf;
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return ;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(ll* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) {
		ll g0 = qpow(fl ? G : invG, (P-1) / l);
		for(int i = 0; i < lim; i += l) {
			ll gn = 1;
			for(int j = i; j < i+k; j++, gn = mul(gn, g0)) {
				ll tt = mul(gn, f[j+k]);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
		}
	}
	if(!fl) {
		ll in = qpow(lim, P-2);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], in);
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
	if(n == 1) {g[0] = qpow(f[0], P-2); return ;}
	Inv(f, g, (n + 1) >> 1);
	int lim = getlim(n);
	clr(g, (n + 1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	NTT(a, lim, 1); NTT(g, lim, 1);
	for(int i = 0; i < lim; i++) g[i] = (2 - a[i] * g[i] % P + P) * g[i] % P;
	NTT(g, lim, 0); clr(g, n, lim);
}
void Deriv(ll* f, ll* g, int n) {
	for(int i = 1; i < n; i++) g[i-1] = mul(f[i], i);
	g[n-1] = 0;
}
void Integ(ll* f, ll* g, int n) {
	for(int i = 1; i < n; i++) g[i] = mul(f[i-1], qpow(i, P-2));
	g[0] = 0;
}
void Ln(ll* f, ll* g, int n) {
	static ll a[MAXN], b[MAXN];
	Deriv(f, a, n); Inv(f, b, n);
	Mul(a, b, a, n); Integ(a, g, n);
}
void Exp(ll* f, ll* g, int n) {
	static ll a[MAXN], b[MAXN];
	if(n == 1) {g[0] = 1; return;}
	Exp(f, g, (n + 1) >> 1);
	int lim = getlim(n);
	clr(g, (n + 1) >> 1, lim);
	cpy(f, a, n); clr(a, n, lim);
	Ln(g, b, n); clr(b, n, lim);
	NTT(a, lim, 1); NTT(b, lim, 1); NTT(g, lim, 1);
	for(int i = 0; i < lim; i++) g[i] = (1 - b[i] + a[i] + P) * g[i] % P;
	NTT(g, lim, 0); clr(g, n, lim);
}
ll readk() {
	ll x = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar());
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x * 10 + ch - '0') % P;
	return x;
}
int n;
ll k, t, a[MAXN], b[MAXN], c[MAXN];
int main() {
	n = read(); k = readk(); t = read();
	k = (t == 0 ? P-k : k);
	for(int i = 0; i < n; i++) a[i] = read();
	b[0] = 1; b[1] = P-1;
	Ln(b, c, n);
	for(int i = 0; i < n; i++) c[i] = mul(c[i], k);
	Exp(c, b, n);
	Mul(a, b, a, n);
	for(int i = 0; i < n; i++) printf("%lld ", a[i]);
	return 0;
}

```

