# P5641 【CSGRound2】开拓者的卓识

[link](https://www.luogu.com.cn/problem/P5641)

## 解题思路

我们考虑每个 $a_i$ 对 $sum_k(1,r)$ 的贡献。

$a_i$ 有贡献当且仅当
$$
i\in[l_{k-1},r_{k-1}]\subseteq[l_{k-2},r_{k-2}]\subseteq\cdots\subseteq [l_0,r_0]
$$
其中 $l_0=1,r_0=r$。

故有
$$
i\ge l_{k-1}\ge l_{k-2}\ge\cdots\ge l_0
\\
i\le r_{k-1}\le r_{k-2}\le\cdots\le r_0
$$
考虑第一个条件，设
$$
d_k=i-l_{k-1}
\\
d_{k-1}=l_{k-1}-l_{k-2}
\\
\cdots
\\
d_1=l_1-l_0
$$
则有
$$
d_i\ge 0(1\le i\le k)
\\
\sum_{i=1}^kd_i=i-l_0=i-1
$$
根据插板法可知，有
$$
\left(
\begin{matrix}
i+k-2
\\
k-1
\end{matrix}
\right)
$$
种情况。

同样地，考虑第二个条件，有
$$
\left(
\begin{matrix}
r-i+k-1
\\
k-1
\end{matrix}
\right)
$$
种情况。

故最后的答案为
$$
sum_k(1,r)=\sum_{i=1}^ra_i
\left(
\begin{matrix}
i+k-2
\\
k-1
\end{matrix}
\right)
\left(
\begin{matrix}
r-i+k-1
\\
k-1
\end{matrix}
\right)
\\
=\sum_{i=0}^{r-1}a_{i+1}
\left(
\begin{matrix}
i+k-1
\\
k-1
\end{matrix}
\right)
\left(
\begin{matrix}
r-i+k-2
\\
k-1
\end{matrix}
\right)
\\
=\sum_{i+j=r-1}a_{i+1}
\left(
\begin{matrix}
i+k-1
\\
k-1
\end{matrix}
\right)
\left(
\begin{matrix}
j+k-1
\\
k-1
\end{matrix}
\right)
$$
记
$$
F(x)=\sum_{i=1}^{n-1}a_{i+1}
\left(
\begin{matrix}
i+k-1
\\
k-1
\end{matrix}
\right)
x^i
\\
G(x)=\sum_{i=1}^{n-1}
\left(
\begin{matrix}
i+k-1
\\
k-1
\end{matrix}
\right)
x^i
\\
$$
则
$$
sum_k(1,r)=[x^{r-1}]F(x)G(x)
$$
直接卷积计算即可。

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
#define clr(f, s, t) memset(f + (s), 0x00, sizeof(int) * ((t) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(int) * (n))
const int MAXN = (1 << 18) + 5, P = 998244353, G = 3, invG = 332748118;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int inv[MAXN], _g[2][MAXN], tr[MAXN], tf;
void init() {
	inv[1] = 1;
	for(int i = 2; i < MAXN; i++) inv[i] = mul(P - P / i, inv[P % i]);
	for(int l = 2; l < MAXN; l <<= 1) {
		_g[1][l] = qpow(G, (P-1) / l);
		_g[0][l] = qpow(invG, (P-1) / l);
	}
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(tf == lim) return;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(int* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l) 
			for(int j = i, gn = 1; j < i+k; j++, gn = mul(gn, _g[fl][l])) {
				int tt = mul(f[j+k], gn);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
	if(!fl)
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], inv[lim]);
}
void Mul(int* f, int* g, int* h, int n) {
	static int a[MAXN], b[MAXN];
	int lim = getlim(n);
	cpy(f, a, n); clr(a, n, lim);
	cpy(g, b, n); clr(b, n, lim);
	NTT(a, lim, 1); NTT(b, lim, 1);
	for(int i = 0; i < lim; i++) h[i] = mul(a[i], b[i]);
	NTT(h, lim, 0); clr(h, n, lim);
}
int n, k, f[MAXN], g[MAXN], h[MAXN];
int main() {
	init();
	n = read(); k = read();
	g[0] = 1;
	for(int i = 1; i < n; i++) g[i] = mul(g[i-1], mul(i+k-1, inv[i]));
	for(int i = 0; i < n; i++) f[i] = mul(read(), g[i]);
	Mul(f, g, h, n);
	for(int i = 0; i < n; i++) printf("%d ", h[i]);
	return 0;
}
```

