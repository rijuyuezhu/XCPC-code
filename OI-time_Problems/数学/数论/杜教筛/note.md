# 杜教筛 学习笔记

[toc]

## 前置知识：数论函数

（这前置知识分量真大）

给几篇博客：

[OI Wiki-莫比乌斯反演](https://oi-wiki.org/math/mobius/)

[铃悬的数学小讲堂——狄利克雷卷积与莫比乌斯反演](https://www.luogu.com.cn/blog/lx-2003/mobius-inversion)

## Reference

我的学习博客来自

## 杜教筛

我们先理解杜教筛可以干啥。

它可以在亚于线性的时间内求出某个数论函数的前缀和。

本质上是利用了狄利克雷卷积的运算性质。

下面我们来推柿子。

假若我们要求的是 $S(n)=\sum\limits_{i=1}^nf(i)$，我们找到一个辅助函数 $g(n)$，使 $g(n),(f*g)(n)$ 的前缀和都利于计算。

于是

$$\sum\limits_{i=1}^n(f*g)(i)=\sum\limits_{i=1}^n\sum\limits_{d|i}f(\lfloor \dfrac nd \rfloor)g(d)$$

$$=\sum\limits_{d=1}^ng(d)\sum\limits_{i=1}^{\lfloor \frac nd \rfloor}f(i)$$

$$=\sum\limits_{d=1}^ng(d)S(\lfloor \dfrac nd\rfloor)$$

我们分出个 $d=1$ 的情况出来。

$$=g(1)S(n)+\sum\limits_{d=2}^ng(d)S(\lfloor \dfrac nd\rfloor)$$

于是得到了一个递归计算柿：

$$S(n)=\dfrac{\sum\limits_{i=1}^n(f*g)(i)-\sum\limits_{d=2}^ng(d)S(\lfloor \dfrac nd \rfloor)}{g(1)}$$

前面的那个 $f*g$ 的前缀和要 **快速计算**，后面由于使用整除分块， $g$ 的前缀和也要 **快速计算**。（关于什么叫做 **快速计算**，请见下文）。

这个柿子是杜教筛的核心。而核心的核心就是 $g$ 的寻找。

在此不进行复杂度证明，仅给出相关结论（详细证明请看上面博客）：

裸的杜教筛（加记忆化）的复杂度为 $\mathcal O(n^{3/4})$。

如果线性筛预处理所有的 $x\le n^{2/3}$ 处 $S(x)$ 的值，递归到 $x\le n^{2/3}$ 时直接返回，那么时间复杂度为 $\mathcal O(n^{2/3})$。

下面解释上文的 **快速计算**：

根据杜教筛的证明，如果 $\sum\limits_{i=1}^n(f*g)(i)$、 $\sum\limits_{i=1}^n g(i)$ 可以用 **不劣于** 杜教筛的算法算出，那么不会影响复杂度，仍为 $\mathcal O(n^{2/3})$。

## 例题

### P4213 【模板】杜教筛（Sum）

> 求 $\mu(n),\varphi(n)$ 的前缀和。
>
> $n< 2^{31}$

还记得那个柿子吗。

$$S(n)=\dfrac{\sum\limits_{i=1}^n(f*g)(i)-\sum\limits_{d=2}^ng(d)S(\lfloor \dfrac nd \rfloor)}{g(1)}$$

我们先考虑怎么求 $\mu(i)$ 的前缀和。

我们知道 $\mu * 1=\epsilon$，于是不妨让 $g=\mathrm{1}$，则 $f*g=\epsilon$。

得到 $S(n)=1-\sum\limits_{d=2}^nS(\lfloor\dfrac nd\rfloor)$。

同理，由于 $\varphi * 1 =\mathrm{id}$，我们让 $g'=1$，则 $f'*g'=\mathrm{id}$

得到 $S'(n)=\dfrac {n(n+1)}2-\sum\limits_{d=2}^n S'(\lfloor \dfrac nd\rfloor)$。

可以杜教筛计算了。

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
const ll MAXN = 1e10 + 5, PN = 1.7e6;
int ip[PN+5], tot;
ll mu[PN+5], phi[PN+5], pr[PN+5];
ll n, fmu[MAXN / PN + 10], fphi[MAXN / PN + 10];
int vmu[MAXN / PN + 10], vphi[MAXN / PN + 10];
void init(ll n) {
	ip[1] = 1; mu[1] = phi[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = -1;
			phi[i] = i-1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			int k = pr[j] * i;
			ip[k] = 1;
			if(i % pr[j]) {
				mu[k] = -mu[i];
				phi[k] = phi[i] * (pr[j] - 1);
			} else {
				mu[k] = 0;
				phi[k] = phi[i] * pr[j];
				break;
			}
		}
	}
	for(int i = 2; i <= n; i++) phi[i] += phi[i-1], mu[i] += mu[i-1];
}
ll calcphi(ll x) {
	if(x <= PN) return phi[x];
	if(vphi[n / x]) return fphi[n / x];
	vphi[n / x] = 1;
	ll ans = x * (x + 1) / 2;
	for(unsigned i = 2, j; i <= x; i = j+1) {
		j = x / (x/i);
		ans -= (j - i + 1) * calcphi(x/i);
	}
	return fphi[n / x] = ans;
}
ll calcmu(ll x) {
	if(x <= PN) return mu[x];
	if(vmu[n / x]) return fmu[n / x];
	vmu[n / x] = 1;
	ll ans = 1;
	for(unsigned i = 2, j; i <= x; i = j+1) {
		j = x / (x/i);
		ans -= (j - i + 1) * calcmu(x/i);
	}
	return fmu[n / x] = ans;
}
int main() {
	init(PN);
	int T = read();
	for(int i = 1; i <= T; i++) {
		n = read();
		memset(vmu, 0x00, sizeof vmu);
		memset(vphi, 0x00, sizeof vphi);
		printf("%lld %lld\n", calcphi(n), calcmu(n));
	}
	return 0;
}
```

tips：这里有个记忆化的技巧：我们要存 $x> n^{2/3}$ 处的计算结果，根据杜教筛的递归特性，$\lfloor \dfrac nx\rfloor$ 各不相同，于是我们可以用数组存储所有的 $\lfloor \dfrac nx\rfloor\le n^{1/3}$。

 

