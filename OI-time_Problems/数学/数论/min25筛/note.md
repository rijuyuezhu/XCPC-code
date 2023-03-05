# Min_25 筛学习笔记

Min_25 筛是解决一系列特定的数论函数求前缀和的亚线性方法。

时间复杂度为 $\mathcal O(\dfrac{n^{3/4}}{\log n})$，或者笼统地写 $O(n^{1-\epsilon})$ 表示亚线性。

题目：[P5325 【模板】Min_25筛](https://www.luogu.com.cn/problem/P5325)

## 算法思想&步骤

首先，Min_25 筛主要用于解决满足下列性质的数论函数 $f(n)$ 前缀和的方法。

-   $f(n)$ 是**积性**函数。
-   $f(n)$ 在质数处的取值是一个**低阶多项式**。
-   $f(n)$ 在质数的幂处的取值可以快速计算。

那么我们就可以在 $O(\dfrac{n^{3/4}}{\log n})$ 的时间复杂度（一般可以跑$n=10^{11}$的数据）内解决求 $F(n)=\sum_{i=1}^nf(i)$ 的值的问题。

主要思想是先考虑在 $[1,n]$ 内所有素数的函数值和，再推出合数的函数值和。

### PART 1：素数的函数和

设 $\mathbb P$ 为素数集。

我们先求

$$
G(n) = \sum_{i=1}^n[i\in \mathbb P]f(i)​
$$
即 $f(i)$ 在素数处的函数值和。注意到 $1$ 不是素数。

采用一种 DP 的思想：

设

$$
g(n,j)=\sum_{i=1}^n [i \in \mathbb P\ or\ \mathrm{minp}(i) > p_j]f'(i)​
$$
特别地， $g(1,j)=0$

其中 $\mathrm{minp}(i)$ 意思是 $i$ 的最小素因子，$p_j$ 表示第 $j$ 个素数，$f'(i)$ 是我们构造的一个函数，它满足：

-   $f'(i)$和$f(i)$在素数处的取值都相同。
-   $f'(i)$是一个完全积性函数。
-   $f'(i)$能够快速计算前缀和。

那么我们有以下转移：
$$
g(n,0)=\sum_{i=2}^n f'(i)\\
g(n,j)=g(n,j-1)-f'(p_j)[g(\lfloor \dfrac{n}{p_j}\rfloor,j-1)-\sum_{i=1}^{j-1}f'(p_i)]
$$
这个式子是怎么推来的呢？我们想想从 $i\in \mathbb P\ or\ \mathrm{minp}(i)>p_{j-1}$ 到 $i\in \mathbb P\ or\ \mathrm{minp}(i)>p_j$ 多计数了哪些？是那些 $\mathrm{minp}(i)=p_j$ 的 合数。于是由于 $f'$ 是完全积性，我们从这个多余部分中提出一个 $f'(p_j)$ ，剩下的就是 $\mathrm{minp}(i)>p_{j-1}$ 的数（当然，要更改上界）。

显然当 $p_j>\sqrt n$ 时，后面一部分是没有贡献的。

于是 $G(n) = g(n, \pi(\sqrt n))$ ，其中 $\pi(n)$ 为 $n$ 以内素数个数。

### PART 2 ：再加上合数的部分

设

$$
S(n,j)=\sum_{i=1}^n[\mathrm{minp}(i)>p_j]f(i)​
$$
那么我们有转移：
$$
S(n,j)=G(n)-\sum_{i=1}^jf(p_i)+\sum_{k=j+1\ and\ p_k^2\le n}\sum_{e=1}^{p_k^e\le n} f(p_k^e)[S(\lfloor \dfrac{n}{p_k^e}\rfloor,k)+[e\ne 1]]
$$
前半部分 $G(n)-\sum\limits_{i=1}^jf(p_i)$ 是 $\mathrm{minp}(i)>p_j$ 的素数 $i$ 处的函数值和，后半部分就是 $\mathrm{minp}(i)>p_j$ 的合数 $i$ 处的函数值和。后半部分的大致做法是枚举最小质因子及其次数。这个 $[e\ne 1]$ 是因为当最小质因子次数 $e$ 不为1时，$f(p_k^e)$ 也要计算，因为它也是合数。

于是我们两部分都只需要用到 $\le \sqrt n$ 的素数。

根据某玄学定理，不需要记忆化。

最后答案就是$S(n,0)+1$.（因为1既不是素数也不是合数）

## Reference

[参考博客](https://www.luogu.com.cn/blog/wucstdio/solution-p5325)

## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
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
const int P = 1e9 + 7, MAXK = 5e5+5, inv6 = 166666668, inv2 = 500000004;
const ll MAXN = 1e10+5;
ll n, sn, w[MAXK], pr[MAXK], sp1[MAXK], sp2[MAXK], g1[MAXK], g2[MAXK];
int ip[MAXK], tot, num, id1[MAXK], id2[MAXK];
void pre_gao(int n) {
	ip[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			sp1[tot] = (sp1[tot-1] + 1ll * i * i) % P;
			sp2[tot] = (sp2[tot-1] + i) % P;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
ll S(ll x, int k) {
	if(pr[k] >= x) return 0;
	int t = x <= sn ? id1[x] : id2[n / x];
	ll ret = ((g1[t] - sp1[k] + P) - (g2[t] - sp2[k] + P) % P) % P;
	for(int j = k+1; j <= tot && pr[j] * pr[j] <= x; j++) {
		ll p = pr[j];
		for(int e = 1; p <= x; e++, p *= pr[j]) {
			ll tmp = p % P;
			ret = (ret + tmp * (tmp - 1) % P * (S(x / p, j) + int(e != 1))) % P;
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
		g1[num] = (tmp * (tmp + 1) % P * (tmp + tmp + 1) % P * inv6 + P - 1) % P;
		g2[num] = (tmp * (tmp + 1) % P * inv2 + P - 1) % P;
		if(t <= sn) id1[t] = num;
		else id2[n / t] = num;
	}
	
	for(int j = 1; j <= tot; j++) 
		for(int i = 1; i <= num && pr[j] * pr[j] <= w[i]; i++) {
			ll nxt = w[i] / pr[j]; int t = nxt <= sn ? id1[nxt] : id2[n / nxt];
			g1[i] = (g1[i] - pr[j] * pr[j] % P * (g1[t] - sp1[j-1]) % P + P) % P;
			g2[i] = (g2[i] - pr[j] * (g2[t] - sp2[j-1]) % P + P) % P;
		}
	printf("%lld\n", (S(n, 0) + 1));
	return 0;
}
```

