# P1587 [NOI2016] 循环之美 解题报告

[link](https://www.luogu.com.cn/problem/P1587)

## 题目大意

求所有满足 $1\le x\le n,1\le y\le m$ 且使得 $\dfrac x y$ 在$k$ 进制下是纯循环小数且值不相等的 $(x,y)$ 的对数。

$1\le x,y\le 10^9,2\le k\le 2000.$

## 解题报告

容易转化，

$\dfrac x y$ 在 $k$ 进制下是纯循环小数 $\Leftrightarrow$ $y\perp k$。

那么我们要统计的即
$$
\sum_{i=1}^n\sum_{j=1}^m[i\perp j][j\perp k]
\\
=\sum_{i=1}^n\sum_{j=1}^m\sum_{d|i,d|j}\mu(d)[j\perp k]
\\
=\sum_{d=1}^{\min(n,m)}\mu(d)[d\perp k]\lfloor \dfrac n d\rfloor \sum_{j=1}^{m/d}[j\perp k]
$$
我们发现我们搞出了一个整除分块的形式。

令
$$
g(n,k)=\sum_{i=1}^n\mu(i)[i\perp k]
\\
f(n,k)=\sum_{i=1}^n[i\perp k]
$$


只要我们可以快速求在所有特殊点 $x$ 处的 $g(x,k),f(x,k)$，这题就大功告成了。

我们考虑递推地求 $f(\cdot ,k),g(\cdot,k)$

假设 $k=p_1p_2\cdots p_t$。这是因为 $k$ 有没有平方因子对 互质 这一限制没有影响。

我们考虑 $k$ 如何从 $\dfrac kp$ 中递推得到。（$p$ 是 $k$ 的质因子）
$$
f(n,k)=\sum_{i=1}^n[i\perp k]
\\
=\sum_{i=1}^n[i\perp \dfrac kp]-\sum_{i=1}^n[i\perp \dfrac kp][p|i]
\\
= f(n,\dfrac kp) - \sum_{i=1}^{n/p}[i\perp \dfrac kp][p\perp \dfrac kp]
\\
=f(n,\dfrac kp)-f(n/p,\dfrac kp)
$$
类似地，
$$
g(n,k)=\sum_{i=1}^n\mu(i)[i\perp k]
\\
= \sum_{i=1}^n\mu(i)[i\perp \dfrac kp]-\sum_{i=1}^n\mu(i)[i\perp \dfrac kp][p | i]
\\
= g(n,\dfrac kp)-\sum_{i=1}^{n/p}\mu(ip)[pi\perp \dfrac kp]
\\
=g(n,\dfrac kp)-\sum_{i=1}^{n/p}\mu(i)\mu(p)[i\perp p][i\perp \dfrac kp]
\\
=g(n,\dfrac kp)-\mu(p)\sum_{i=1}^{n/p}\mu(i)[i\perp k]
\\
=g(n, \dfrac kp)+g(n/p,k)
$$
而递归边界为 
$$
f(0,k)=0,f(n,0)=n\\
g(0,k)=0,g(n,0)=\sum_{i=1}^n\mu(i)
$$
其中 $g(n,0)$ 可以杜教筛算出所有特殊点处的值.

那么我们只要花费 $\mathcal O(\sqrt n \cdot d_p(k))$ ($d_p (k)$ 表示 $k$ 的质因子个数)的时间即可得到所有特殊点处的值.

总时间复杂度为 $\mathcal O(\sqrt n \cdot d_p(k)+n^{2/3})$.

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
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
#define mp make_pair
const int MAXN = 1e9+5, XN = 1e6+5;
const int MAXK = 2e3+5;
int n, m, K, ip[XN], pr[XN], tot, pK[100], totK;
ll mu[XN], smu0[XN];
void init(int n) {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {pr[++tot] = i; mu[i] = -1;}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) {
				mu[i * pr[j]] = -mu[i];
			} else {
				mu[i * pr[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) smu0[i] = smu0[i-1] + mu[i];
}
ll calcsmu(ll n) {
	if(n < XN) return smu0[n];
	static map<ll, ll> table;
	map<ll, ll>::iterator it;
	if((it = table.find(n)) != table.end()) return it->second;
	ll ret = 1;
	for(ll i = 2, j; i <= n; i = j+1) {
		j = n / (n / i);
		ret -= (j - i + 1) * calcsmu(n / i);
	}
	table[n] = ret;
	return ret;
}
ll calcf(ll n, int k) {
	if(n == 0) return 0;
	if(k == 0) return n;
	static map<pair<ll, int>, ll> table;
	map<pair<ll, int>, ll>::iterator it;
	if((it = table.find(mp(n, k))) != table.end()) return it->second;
	ll ret = calcf(n, k-1) - calcf(n / pK[k], k-1);
	table[mp(n, k)] = ret;
	return ret;
}
ll calcg(ll n, int k) {
	if(n == 0) return 0;
	if(k == 0) return calcsmu(n);
	static map<pair<ll, int>, ll> table;
	map<pair<ll, int>, ll>::iterator it;
	if((it = table.find(mp(n, k))) != table.end()) return it->second;
	ll ret = calcg(n, k-1) + calcg(n / pK[k], k);
	table[mp(n, k)] = ret;
	return ret;
}
int main() {
	init(XN-1);
	n = read(), m = read(), K = read();
	int t = K;
	for(int i = 2; i * i <= t; i++)
		if(t % i == 0) {
			pK[++totK] = i;
			while(t % i == 0) t /= i;
		}
	if(t > 1) pK[++totK] = t;
	ll ret = 0;
	for(ll i = 1, j; i <= n && i <= m; i = j+1) {
		j = min(n / (n / i), m / (m / i));
		ret += (calcg(j, totK) - calcg(i-1, totK)) * (n / i) * calcf(m / i, totK);
	}
	printf("%lld\n", ret);
	return 0;
}
```

