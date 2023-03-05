# DGF（狄利克雷生成函数） 学习笔记

## 0. reference

<https://shanlunjiajian.github.io/2021/05/19/dgf/>

<https://www.luogu.com.cn/blog/gxy001/di-li-ke-lei-sheng-cheng-han-shuo-qian-tan>

## 1. 引进

### 1.1 定义

对于数论函数 $f(x)$，定义其 DGF 为
$$
    F(z)=\sum_{i=1}\dfrac{f(i)}{i^x}
$$

如果 $f(x)$ 是**积性函数**，可以将式中的 $i$ 分解成若干素数幂的乘积。我们发现同样可以把 $\frac{f(i)}{i^x}$ 分解成素数幂相关。考虑每个素数的贡献，有：

$$
F(z)=\prod_{p\in \mathbb{P}}\sum_{i=0}\dfrac{f(p^i)}{p^{ix}}
$$

### 1.2 常见数论函数的 DGF

- 单位函数 $\epsilon(x)$ 的 DGF
  $$
    \tilde {\epsilon}(z)= 1
  $$
- 常数函数 $1(x)$ 的 DGF 是黎曼函数
  $$
    \begin{aligned}
        \zeta(z)=&\sum_{i=1}\dfrac{1}{i^z}
        \\=&\prod_{p\in\mathbb{P}}\sum_{i=0}\dfrac{1}{p^{iz}}
        \\=&\prod_{p\in\mathbb{P}}\dfrac{1}{1-p^{-z}}
    \end{aligned}
  $$
- 莫比乌斯函数 $\mu(x)$ 
  $$
    \begin{aligned}
        \tilde {\mu}(z)=&\prod_{p\in\mathbb P}\left( 1+\dfrac{-1}{p^z} \right)
        \\=&\prod_{p\in\mathbb P}(1-p^{-z})
        \\=&\zeta^{-1}(z)
    \end{aligned}
  $$
- $\mu^2(x)$
  $$
    \begin{aligned}
        \tilde \mu_2(z)=&\prod_{p\in\mathbb P}(1+p^{-z})
        \\=&\prod_{p\in\mathbb P}\dfrac{1-p^{-2z}}{1-p^{-z}}
        \\=&\dfrac{\zeta(z)}{\zeta(2z)}
    \end{aligned}
  $$
- 幂函数 $id_k(x)=x^k$
  $$
    \begin{aligned}
        \tilde {id}_k(z)=&\sum_{i=1}\dfrac{i^k}{i^z}
        \\=&\sum_{i=1}\dfrac{1}{i^{z-k}}
        \\=&\zeta(z-k)
    \end{aligned}
  $$
- 欧拉函数 $\varphi(x)$
  $$
    \begin{aligned}
        \tilde \varphi(z)=&\prod_{p\in\mathbb P}\left(1+\sum_{i=1}\dfrac{p^i-p^{i-1}}{p^{iz}}\right)
        \\=&\prod_{p\in\mathbb P}\left( 1+\left(1-\dfrac{1}{p}\right)\sum_{i=1} \left(p^{1-z}\right)^i \right)
        \\=&\prod_{p\in\mathbb{P}}\left( 1+ \dfrac{p-1}{p}\cdot \dfrac{p^{1-z}}{1-p^{1-z}} \right)
        \\=&\prod_{p\in\mathbb{P}}\dfrac{1-p^{-z}}{1-p^{1-z}}
        \\=&\dfrac{\zeta(z-1)}{\zeta(z)}
        \\=&\dfrac{\tilde {id}(z)}{\zeta(z)}
    \end{aligned}
  $$

- 除数函数 $\sigma_k(x)$
  $$
    \begin{aligned}
        &
        \tilde \sigma(z)=\prod_{p\in \mathbb P}\sum_{i=0}\dfrac{\sum_{j=0}^ip^{jk}}{p^{iz}}
        \\=&
        \prod_{p\in \mathbb P}\sum_{i=0}\dfrac{1-p^{(i+1)k}}{(1-p^k)p^{iz}}
        \\=&
        \prod_{p\in \mathbb P}\dfrac{1}{1-p^k}\left(\sum_{i=0}p^{-iz}-p^k\sum_{i=0}p^{-(z-k)i}\right)
        \\=&
        \prod_{p\in \mathbb P}\dfrac{1}{1-p^k}\left(\dfrac{1}{1-p^{-z}}-\dfrac{pk}{1-p^{-(z-k)}}\right)
        \\=&
        \prod_{p\in \mathbb P}\dfrac{1-p^{-(z-k)}-p^k(1-p^{-z})}{(1-p^k)(1-p^{-z})(1-p^{-(z-k)})}
        \\=&
        \prod_{p\in \mathbb P}\dfrac{1}{(1-p^{-z})(1-p^{-(z-k)})}
        \\=&\zeta(z)\zeta(z-k)
        \\=&\zeta(z)\tilde {id}_k(z)
    \end{aligned}
  $$

## 2. 运算

### 2.1 乘法

$$
    \begin{gathered}
        F(z)=\sum_{i=1}\dfrac{f_i}{i^z}
        \\
        G(z)=\sum_{i=1}\dfrac{g_i}{i^z}
    \end{gathered}
$$
$$
    \begin{aligned}
        (F*G)(z)=&\sum_{i=1}\dfrac{f_i}{i^z}\sum_{j=1}\dfrac{g_j}{j^z}\\=&\sum_{i=1,j=1}\dfrac{f_ig_j}{(ij)^z}
        \\=&\sum_{n=1}\dfrac{\sum_{i|nf_ig_{n/i}}}{n^z}    
    \end{aligned}
$$

发现 $(F*G)(z)$ 就是 $f*g$ 的 DGF。

时间复杂度是 $O(n\log n)$ 的。

### 2.2 乘法逆，以及除法

求 $f(x)$ 的狄利克雷乘法逆。设为 $g(x)$。

递推：

$$
\begin{aligned}
    \epsilon(n)=&\sum_{d|n}g(d)f(n/d)
    \\=&
    g(n)f(1)+\sum_{d|n,d\ne n}g(d)f(n/d)
    \\
    g(n)=&\dfrac{1}{f(1)}\left([n=1]-\sum_{d|n,d\ne n}g(d)f(n/d)\right)
\end{aligned}
$$

每求出一个 $g(n)$，计算对 $n$ 倍数的贡献。

类似地，可以推出除法的递推式：

$$
\begin{aligned}
    h(n)=&\sum_{d|n}g(d)f(n/d)
    \\
    g(n)=&\dfrac{1}{f(1)}\left(h(n)-\sum_{d|n,d\ne n}g(d)f(n/d)\right)
\end{aligned}
$$
时间复杂度 $O(n\log n)$。

### 2.3 求导与积分

根据定义式，$F(z)=\sum_{i=1}\dfrac{f_i}{i^z}$。

那么求导：

$$
\dfrac{d}{dz}\dfrac{f_i}{i^z}=-\ln i\cdot \dfrac{f_i}{i^z}
$$

积分：

$$
\int\dfrac{f_i}{i^z}dz=-\dfrac{1}{\ln i}\cdot \dfrac{f_i}{i^z}+c
$$

这里的 $\ln i$ 是什么东西？它在 $i>2$ 时根本 $\not\in \mathbb Z$。这里有一个很好的替代品：用 $i$ 的各质因子次数之和代替 $\ln i$。这是因为它与对数有着类似的性质。

### 2.4 对数

$$
    \ln(F(z))=\int \dfrac{F'(z)}{F(z)}dz
$$

差不多这个意思）

### 2.5 指数

$$
    \begin{gathered}
        \exp F(z)=G(z)
        \\
        G'(z)=F'(z)\exp F(z)=F'(z)G(z)
        \\
        -\ln n\cdot g_n=\sum_{d|n}-\ln d\cdot f_dg_{n/d}
        \\
        g_n=\dfrac{1}{\ln n}\sum_{d|n}f_dg_{n/d}\ln d
    \end{gathered}
$$

### 2.7 例题

<https://loj.ac/p/6713>

> 给出 $g$，求出 $f$ 使得 $f^k=g$。其中幂为狄利克雷乘法幂。

sol：

从 DGF 入手，有 $F^k(z)=G(z)$，故 $F(z)=\exp{\dfrac{\ln G(z)} k}$

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
const int MAXN = 1e6 + 5;
const int P = 998244353;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
mint operator + (const mint& a, const mint& b) { return MOD(a.v + b.v); }
mint operator - (const mint& a, const mint& b) { return MOD(a.v - b.v + P); }
mint operator - (const mint& a) { return 0-a; }
mint operator * (const mint& a, const mint& b) { return 1ll * a.v * b.v % P; }
mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
int n, k;
mint g[MAXN], f[MAXN], c[MAXN], invc[MAXN];
int pr[MAXN], ip[MAXN], tot;
void Sieve(int n) {
	ip[1] = 1; c[1] = 0;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i; c[i] = 1;
		}
		for(int j = 1; j <= tot && pr[j] <= n / i; j++) {
			int k = i * pr[j];
			c[k] = c[i] + 1;
			ip[k] = 1;
			if(i % pr[j] == 0) break;
		}
	}
	for(int i = 1; i <= n; i++) c[i] = -c[i], invc[i] = qpow(c[i]);
}
void Div(mint* f, mint* g, mint* ans, int n) {
	for(int i = 1; i <= n; i++) ans[i] = f[i];
	mint iv = qpow(g[1]);
	for(int i = 1; i <= n; i++) {
		ans[i] = ans[i] * iv;
		for(int j = 2; j <= n / i; j++) {
			ans[i * j] = ans[i * j] - ans[i] * g[j];
		}
	}
}
void Deriv(mint* f, mint* ans, int n) {
	for(int i = 1; i <= n; i++) ans[i] = f[i] * c[i];
}
void Integ(mint* f, mint* ans, int n) {
	for(int i = 1; i <= n; i++) ans[i] = f[i] * invc[i];
}
void Ln(mint* f, mint* ans, int n) {
	static mint tmp[MAXN];
	Deriv(f, tmp, n);
	Div(tmp, f, ans, n);
	Integ(ans, ans, n);
}
void Exp(mint* f, mint* ans, int n) {
	for(int i = 1; i <= n; i++) ans[i] = 0;
	ans[1] = 1;
	for(int i = 1; i <= n; i++) {
		if(i != 1) ans[i] = ans[i] * invc[i];
		for(int j = 2; j <= n / i; j++)
			ans[i * j] = ans[i * j] + ans[i] * f[j] * c[j];
	}
}
int main() {
	n = read(), k = read();
	Sieve(n);
	for(int i = 1; i <= n; i++) f[i] = read();
	mint invk = qpow(k);
	Ln(f, g, n);
	for(int i = 1; i <= n; i++) g[i] = g[i] * invk;
	Exp(g, f, n);
	for(int i = 1; i <= n; i++) printf("%d ", f[i].v);
	return 0;
}
```

## 3. 应用

### 3.1 构造线性筛

通过DGF，我们可以方便地求出某些函数的狄利克雷卷积的质数幂处的值，从而方便线性筛。

比如要线性筛 $f=\varphi*\mu$：

我们可以算出它的 DGF：

$$
\begin{aligned}
  F(z)=&\tilde \varphi(z) \tilde \mu(z)
  \\=&\dfrac{\zeta(z-1)}{\zeta^2(z)}
  \\=&\prod_{p\in\mathbb P}\dfrac{(1-p^{-z})^2}{1-p^{1-z}}
  \\=&\prod_{p\in \mathbb P}\left(1+\dfrac{-2}{p^{z}}+\dfrac{1}{p^{2z}}\right)\left(1+\dfrac{p}{p^z}+\dfrac{p^2}{p^{2z}}+\cdots\right)
\end{aligned}
$$

那么，我们要得到的 $f(p^k)$ 就是展开式中 $\dfrac{1}{p^{kz}}$ 项的系数。容易得到：

- $k=0$ 时，$f(p^k)=1$
- $k=1$ 时，$f(p^k)=p-2$
- $k\ge 2$ 时，$f(p^k)=p^k-2p^{k-1}+p^{k-2}$

于是可以线性筛。

### 3.2 构造杜教筛等
我们先回忆一下杜教筛：

对于一个数论函数 $f(n)$，要求其前缀和 $F(n)=\sum_{i=1}^n f(i)$，通过构造函数 $g(n)$，有

$$
\begin{aligned}
  \sum_{i=1}^n(f*g)(i)=&\sum_{i=1}^n\sum_{d|i}g(d)f(i/d)
  \\=&\sum_{d=1}^ng(d)\sum_{d|i,i\le n}f(i/d)
  \\=&\sum_{d=1}^ng(d)\sum_{i=1}^{n/d}f(i)
  \\=&\sum_{d=1}^ng(d)F(n/d)
  \\=&g(1)F(n)+\sum_{d=2}^ng(d)F(n/d)
\end{aligned}
$$

于是

$$
F(n)=\dfrac{1}{g(1)}\left[\sum_{i=1}^n(f*g)(i)-\sum_{d=2}^ng(d)F(n/d)\right]
$$

若 $\sum_{i=1}^n (f*g)(i),g(n)$ 可以在不亚于杜教筛的复杂度内求出，则可以在 $O(n^{2/3})$ 的时间内求出 $F(n)$。

问题在于这个 $g(n)$ 的选取。

#### 3.2.1 例题1 杜教筛

<https://www.luogu.com.cn/problem/P4213>

对于 $f=\mu$,有

$$
\tilde {\mu}(z)=\dfrac{1}{\zeta(z)}
$$

于是构造 $g=1$，则 $f*g=\epsilon$

对于 $f=\varphi$，有

$$
\tilde \varphi(z)=\dfrac{\zeta(z-1)}{\zeta(z)}=\dfrac{id(z)}{\zeta(z)}
$$

于是构造 $g=1$，则 $\varphi * 1=id$

#### 3.2.2 Min25筛

<https://www.luogu.com.cn/problem/P5325>

这一题需要应用到 Powerful Number 相关知识。

如果 $f=g*h$，$h(n)$ 仅在 Powerful Number 处有值，由于 $n$ 以内的 Powerful Number 仅有 $O(\sqrt n)$ 个，故通过

$$
\begin{aligned}
  \sum_{i=1}^nf(i)=\sum_{d=1}^nh(d)\sum_{i=1}^{n/d}g(i)
\end{aligned}
$$

若可以在较快时间内求出特殊点处的 $g$ 的前缀和，则可以通过爆搜 Powerful Number 来计算 $f$ 的前缀和。

而怎样找到这样的 $h$ 呢？有两种方法：

1. 若 $f$ 是与 $g$ 在素数处取值相同的积性函数，根据 $f(p)=g(1)h(p)+h(1)g(p)$，而 $g(1)=h(1)=0, f(p)=g(p)$，有 $h(p)=0$。
2. 通过 DGF 计算，使得 $h$ 的 DGF 后面的因式类似于 $\left(1+\sum_{i=2}\dfrac{\cdots}{p^{iz}}\right)$ 的形式。
  
通常两种方法可以结合使用。

我们先将 $f(n)$ 的 DGF 写出来：

$$
\begin{aligned}
  F(z)=&
  \prod_{p\in \mathbb P}\left(1+\sum_{i=1}\dfrac{p^i(p^i-1)}{p^{iz}}\right)
  \\=&
  \prod_{p\in \mathbb P}\left( 1+\sum_{i=1}p^{(2-z)i}-\sum_{i=1}p^{(1-z)i} \right)
  \\=&
  \prod_{p\in \mathbb P}\left( 1+\dfrac{p^{2-z}}{1-p^{2-z}}-\dfrac{p^{1-z}}{1-p^{1-z}} \right)
  \\=&
  \prod_{p\in \mathbb P}\left(\dfrac{1-2p^{1-z}+p^{3-2z}}{(1-p^{2-z})(1-p^{1-z})}\right)
\end{aligned}
$$  
这里似乎推不下去了，我们想我们需要一个什么样的 $g$？要求满足 $g(p)=f(p)=p(p-1)$，不妨设 $g=id\varphi$，于是有

$$
\tilde g(z)=\dfrac{\zeta(z-1)}{\zeta(z)}\cdot
$$