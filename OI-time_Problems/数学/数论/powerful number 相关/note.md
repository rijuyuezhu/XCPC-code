# 利用 Powerful Number 求数论函数前缀和

## 0. 前言

**Powerful Number** 可以用来快速求解数论函数的前缀和。

本文参考了：

[zzq's blog](https://www.cnblogs.com/zzqsblog/p/9904271.html)

[攀岩高手 的博客](https://www.luogu.com.cn/blog/lengyanze/solution-p5325)

在此向以上文章的作者呈上真挚的感谢！

## 1. Powerful Number

### 1.1 定义

正整数 $n=p_1^{a_1}p_2^{a_2}\cdots p_s^{a_s}$ 满足 $a_i\ge 2(1\le i\le s)$，即 $n$ 的所有质因子的幂次都 $\ge 2$ ，则称 $n$ 是一个 **Powerful Number**。特别地，1 为 **Powerful Number**。

### 1.2 性质

$[1,n]$ 内的 **Powerful Number** 有 $O(\sqrt n)$ 个。

**证：** 显然 **Powerful Number** 都可以表示成 $a^2b^3$ 的形式，我们枚举 $a$，则 $[1,n]$ 内 **Powerful Number** 的数量为
$$
O\left(\sum_{a=1}^{\sqrt n}\sqrt [3]{\dfrac{n}{a^2}}\right)
\\
=O\left(\sqrt[3] n\int_1^{\sqrt n}a^{-2/3}da\right)
\\
=O(\sqrt n)\\\Box
$$
这个性质保证了算法的复杂度。

## 2. 应用

### 例题1

[P5325 【模板】Min_25筛](https://www.luogu.com.cn/problem/P5325)

已知积性函数 $f(n)$，满足 $f(p^k)=p^k(p^k-1)$。求
$$
\sum_{i=1}^nf(i)
$$
$1\le n\le 10^{10}$。

先找到一个积性函数使得它与 $f$ 在素数的取值一致，我们可以找到 $g(n)=n\varphi(n)$。

设 $h$ 满足 $f=g*h$，其中 $*$ 为 Dirichlet 卷积，故有
$$
f(p)=g(1)h(p)+g(p)h(1)
$$
由于 $f,g$ 都是积性函数，则 $h$ 也是积性函数，故有 $h(1)=g(1)=1$，则又由于 $f(p)=g(p)$，有 $h(p)=0$。

由于 $h$ 是积性函数，则 $h$ 仅在 **Powerful Number** 处可能不为 0。

我们继续推式子，题目所求为
$$
\sum_{i=1}^nf(i)=\sum_{i=1}^n\sum_{d|i}g(d)h\left(\dfrac i d\right)
\\
=\sum_{ij\le n}g(i)h(j)=\sum_{i=1}^nh(i)\sum_{j=1}^{n/i}g(j)
$$
根据上文所说，我们只需考虑 $i$ 为 **Powerful Number** 时 $g$ 的前缀和怎么求，$h$ 的函数值怎么求（这两点也是最重要的）。

我们可以通过杜教筛简单地求得 $g$ 在所有特殊点 $\left\lfloor\dfrac ni\right\rfloor$ 处的前缀和。

那么唯一剩下的问题就变成了求 $h$ 在 **Powerful Number** 处的前缀和。

由于 $h$ 是积性函数，我们考虑计算 $h(p^k)$ 的值。注意到当 $p>\sqrt n$ 时不可能有 **Powerful Number** 有质因子 $p$，故我们只要计算 $p\le \sqrt n$ 时的情况。

我们有两种方法计算。

**Way1 推式子**

有
$$
f(p^k)=(h*g)(p^k)=\sum_{i=0}^kg(p^i)h(p^{k-i})
$$
而
$$
g(p^i)=p^i\varphi(p^i)=(p-1)p^{2i-1}(i\ge1)
\\
g(1)=1
$$
展开得
$$
p^k(p^k-1)=h(p^k)+\sum_{i=1}^k(p-1)p^{2i-1}h(p^{k-i})
$$
后面那部分很难看，我们不妨改一下 $h$ 的指数，有
$$
p^k(p^k-1)=h(p^k)+\sum_{i=0}^{k-1}(p-1)p^{2k-2i-1}h(p^i)
$$
接下来考察你高中数列的解题水平了，做不出来的请问你的高中数学老师。

用 $k-1$ 代替原式，有
$$
p^{k-1}(p^{k-1}-1)=h(p^{k-1})+\sum_{i=0}^{k-2}(p-1)p^{2k-2i-3}h(p^i)
\\
p^{k+1}(p^{k-1}-1)=p^2h(p^{k-1})+\sum_{i=0}^{k-2}(p-1)p^{2k-2i-1}h(p^i)
$$
两式相减得
$$
p^{2k}-p^k-p^{2k}+p^{k+1}=h(p^{k})-p^2h(p^{k-1})+(p-1)ph(p^{k-1})
$$
稍作化简得
$$
h(p^k)-ph(p^{k-1})=p^{k+1}-p^k
$$
设 $H(k)=h(p^k)$，则
$$
H(k)-pH(k-1)=p^{k+1}-p^k
\\
\dfrac{H(k)}{p^k}-\dfrac{H(k-1)}{p^{k-1}}=p-1
$$
累加法，又 $H(1)=h(p)=0$ 得
$$
\dfrac{H(k)}{p^k}=(k-1)(p-1)
\\
H(k)=h(p^k)=(k-1)(p-1)p^k
$$
于是我们得到了通项，直接代入计算即可。

**Way2 暴力计算**

根据
$$
p^k(p^k-1)=h(p^k)+\sum_{i=0}^{k-1}(p-1)p^{2k-2i-1}h(p^i)
$$
得
$$
h(p^k)=p^k(p^k-1)-\sum_{i=0}^{k-1}(p-1)p^{2k-2i-1}h(p^i)
$$
直接计算 $h(p^k)$，每个质因子递推计算即可。这样的复杂度为 $O(质数个数\times 幂次)$

而 $\sqrt n$ 以内素数个数为 $\pi(\sqrt n)=O(\dfrac{\sqrt n}{\log n})$，幂次为 $O(\log n)$，故复杂度仍为 $O(\sqrt n)$。这种方法不用动太多脑子。（当然你不好递推的话，纯暴力计算$O(\sqrt n\log n)$ ~~似乎也没啥大问题~~）

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
const int MAXK = 5e6 + 5;
const int P = 1e9 + 7, inv6 = 166666668;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll n, g[MAXK], sg[MAXK], tb_g[MAXK];
int pr[MAXK], ip[MAXK], tot; 
void Sieve(int n) {
	ip[1] = 1; g[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			g[i] = i-1;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			int k = i * pr[j];
			ip[k] = 1;
			if(i % pr[j]) g[k] = g[i] * (pr[j] - 1);
			else {
				g[k] = g[i] * pr[j];
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) g[i] = mul(g[i], i);
	for(int i = 1; i <= n; i++) sg[i] = pls(sg[i-1], g[i]);
}
ll S1(ll n) {n %= P; return n * (n + 1) / 2 % P;}
ll S2(ll n) {n %= P; return n * (n + 1) % P * (n + n + 1) % P * inv6 % P;}
ll calcsg(ll x) {
	if(x < MAXK) return sg[x];
	if(~tb_g[n / x]) return tb_g[n / x];
	ll ret = S2(x);
	for(ll i = 2, j; i <= x; i = j + 1) {
		ll t = x / i; j = x / t;
		ret = mns(ret, mul(calcsg(t), mns(S1(j), S1(i-1))));
	}
	return tb_g[n / x] = ret;
}
ll calch(ll p, ll pk, ll e) {p %= P; pk %= P; e %= P; return (e-1) * (p-1) % P * pk % P;}
ll dfs(ll k, ll lst, ll h) {
	ll ans = mul(h, calcsg(n / lst));
	for(ll g = n / lst; 1ll * pr[k] * pr[k] <= g; k++) {
		for(ll e = 2, p = 1ll * pr[k] * pr[k]; p <= g; p *= pr[k], e++)
			ans = pls(ans, dfs(k+1, lst * p, mul(h, calch(pr[k], p, e))));
	}
	return ans;
}
int main() {
	n = read();
	Sieve(MAXK - 1);
	memset(tb_g, -1, sizeof tb_g);
	printf("%lld\n", dfs(1, 1, 1));
	return 0;
}
```



（未完待续，咕咕咕）