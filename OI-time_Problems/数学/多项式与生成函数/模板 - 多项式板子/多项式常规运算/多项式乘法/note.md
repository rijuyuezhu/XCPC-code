# FFT&NTT 多项式乘法

[toc]

## 前言 

FFT，快速傅里叶变换;NTT，快速数论变换，其实是一个东西在不同的域上的不同表现形式。本博客只是简单地总结一下，提一些其它博客没有注意的地方。

推荐学习资料：

[OI Wiki-FFT](https://oi-wiki.org/math/poly/fft/)

[OI Wiki-NTT](https://oi-wiki.org/math/poly/ntt/)

[傅里叶变换(FFT)学习笔记——command block](https://www.luogu.com.cn/blog/command-block/fft-xue-xi-bi-ji) （极度推荐）

[NTT与多项式全家桶——command block](https://www.luogu.com.cn/blog/command-block/ntt-yu-duo-xiang-shi-quan-jia-tong)

## 前置知识

### 多项式的表示

1. **系数表示**。要表示一个度为 $n$ 的多项式，只要 $n+1$ 个数表达 $x^i(0\le i\le n)$ 项的系数即可。
2. **点值表示**。只要 $n+1$ 个横坐标不同的点，也可以表示这个多项式。这是因为代入 $n+1$ 个点，可以得到 $n+1$  个方程，把 $n+1$ 个系数看成未知数，就变成了 ~~小学二年级学过的~~ 多元一次方程组啦。**值得注意的是**，这里的点的横纵坐标不必为实数，比如我们 FFT 用到的就是横纵坐标都为复数的点。

如何快速计算乘法？如果是系数表示，我们需要 $\mathcal O(n^2)$ 的复杂度。但是点值在这方面异常优秀，只要 $\mathcal O(n)$ 即可。

### 单位根

我们把复平面上单位圆 $n$ 等分（以 $(1,0)$ 作为等分的第一个点），会得到 $n$ 个点。把这 $n$ 个点对应的复数叫做 $n$ 次单位根。记作 $w_n^j$，其中 $0\le j<n$。$w_n^j$ 的模为 1，辐角为 $\dfrac{j}{2\pi}$。于是有

$$w_n^j=\exp(i\frac{2\pi j}{n})=\cos\dfrac {2\pi j}{n}+i\sin\dfrac {2\pi j}n$$

单位根有优美的性质：

1. $w_n^j=w_n^{j+kn},k\in\Z$
2. $w_n^j=w_{2n}^{2j}$
3. $w_{2n}^{j+n}=-w_{2n}^j$

这些性质是我们利用 FFT 快速计算的基石。

## 离散傅里叶变换(DFT)

离散傅里叶变换，就是将系数表示变为点值表示（即“求值”）。这个大家都会，$\mathcal O(n^2)$ 暴力代入啊。可惜太慢了。

## 快速傅里叶变换(FFT)

快速傅里叶变换利用 **单位根** 的性质，**分治** 的方法，在 $\mathcal O(n\log n)$ 的时间内将一个度数为 $n$ 的多项式由系数表示变为点值表示。它是 DFT的升级版。

比如一个度数为 $n-1$ （这里假设 $n$ 是2的整数次幂）的多项式 

$$f(x)=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}$$

我们分一下奇偶。

$$f(x)=(a_0+a_2x^2+\cdots+a_{n-2}x^{n-2})+(a_1x+a_3x^3+\cdots+a_{n-1}x^{n-1})$$

$$=(a_0+a_2x^2+\cdots+a_{n-2}x^{n-2})+x(a_1+a_3x^2+\cdots+a_{n-1}x^{n-2})$$

我们记 $f_1(x)=a_0+a_2x+\cdots+a_{n-2}x^{n/2-1}$，$f_2(x)=a_1+a_3x+\cdots+a_{n-1}x^{n/2-1}$

则有 $f(x)=f_1(x^2)+xf_2(x^2)$

为了快速计算，我们带入单位根。

1. 先带入个 $w_n^k(k<n/2)$

有 $f(w_n^k)=f_1(w_{n/2}^{k})+w_n^kf_2(w_{n/2}^k)$

2. 再带入个 $w_n^{k+n/2}=-w_n^k(k<n/2)$

有 $f(w_n^{k+n/2})=f_1(w_{n/2}^k)-w_n^kf_2(w^k_{n/2})$

我们发现，**两次代入有惊人的相似性**。

于是可以分治计算了。每一层 $n$ 的规模规模减半，显然复杂度是 $O(n\log n)$。

代码就不找了，随便一篇博客都有。

## 离散傅里叶逆变换(IDFT)

离散傅里叶逆变换，就是将点值表示变为系数表示（即“插值”）。怎么做？高斯消元是 $O(n^3)$ 的。似乎不怎么好做。

## 快速傅里叶逆变换

还是请回我们的单位根吧，看看怎么做。。。

**结论**：把点值（$f(w_n^k)$）当成系数，将 DFT中乘的那个 $w_n^k$ 换成 $-w_n^k$ 求点值，最后再都除以 $n$ ，就是原多项式的系数啦。

证明去找别的博客啦。

## FTT实现

这里加上了 “蝴蝶效应” 变成了迭代写法，可以大幅度减小常数。



模板：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e6 + 5;
const db Pi = acos(-1.0);
struct cp {db x, y;}f[MAXN], g[MAXN];
cp operator + (const cp& a, const cp& b) {return (cp){a.x+b.x, a.y+b.y};}
cp operator - (const cp& a, const cp& b) {return (cp){a.x-b.x, a.y-b.y};}
cp operator * (const cp& a, const cp& b) {return (cp){a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x};}
int n, m, d, id[MAXN];
void fft(cp* f, int fl) {
	for(int i = 0; i < d; i++) if(i < id[i]) swap(f[i], f[id[i]]);
	for(int l = 2, hl = 1; l <= d; l <<= 1, hl <<= 1) {
        //这是在枚举哪一层，这里的 l 就是推柿子时的 n
		cp w0 = (cp){cos(2*Pi / l), fl * sin(2*Pi / l)};
		for(int i = 0; i < d; i += l) {//i是每次迭代的段头
			cp w = (cp){1, 0};
			for(int j = i; j < i+hl; j++, w = w * w0) {//j则是控制推柿子时的 k
				cp tt = w * f[j+hl];
				f[j+hl] = f[j] - tt;
				f[j] = f[j] + tt;
			}
		}
	}
	if(fl == -1) {//idft还得除以个 d（懒得写数乘，就直接这样写了）
		for(int i = 0; i < d; i++) f[i].x /= d, f[i].y /= d;
	}
}
int main() {
	n = read(), m = read();
	for(int i = 0; i <= n; i++) f[i].x = read();
	for(int i = 0; i <= m; i++) g[i].x = read();
	for(d = 1; d <= n+m; d <<= 1);
	for(int i = 0; i <= d; i++) 
		id[i] = (id[i >> 1] >> 1) | ((i & 1) ? (d >> 1) : 0);
	fft(f, 1); fft(g, 1);
	for(int i = 0; i < d; i++) f[i] = f[i] * g[i];
	fft(f, -1);
	for(int i = 0; i <= n+m; i++) printf("%d ", int(f[i].x + 0.5));
	return 0;
}
```

~~请全文背诵~~

**注意事项：**

1. 数组空间请注意，要开到 $n+m$ 的至少两倍。
2. 请注意精度误差，如果 $f$ 和 $g$ 的数量级差很多，不妨先数乘到同一数量级再做。

### 优化

我们可以利用一下 $f,g$ 系数的虚部为零的特点，“三次变两次”。

我们构造一个系数为复数的多项式 $h(x)=f(x)+ig(x)$，

那么 $h^2(x)=f^2(x)-g^2(x)+i\cdot(2f(x)g(x))$

于是我们只要构造 $h$ ，让其平方即可。只要一次DFT和一次IDFT。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e6 + 5;
const db Pi = acos(-1.0);
struct cp{db x, y;}f[MAXN];
cp operator + (const cp& a, const cp& b) {return (cp){a.x+b.x, a.y+b.y};}
cp operator - (const cp& a, const cp& b) {return (cp){a.x-b.x, a.y-b.y};}
cp operator * (const cp& a, const cp& b) {return (cp){a.x*b.x - a.y*b.y, a.x*b.y + a.y * b.x};}
int n, m, d, id[MAXN];
void fft(cp* f, int fl) {
	for(int i = 0; i < d; i++) if(i < id[i]) swap(f[i], f[id[i]]);
	for(int l = 2, hl = 1; l <= d; l <<= 1, hl <<= 1) {
		cp w0 = (cp){cos(2*Pi / l), fl * sin(2*Pi / l)};
		for(int i = 0; i < d; i += l) {
			cp w = (cp){1, 0};
			for(int j = i; j < i + hl; j++, w = w * w0) {
				cp tt = w * f[j+hl];
				f[j+hl] = f[j] - tt;
				f[j] = f[j] + tt;
			}
		}
	}
	if(fl == -1) {
		for(int i = 0; i < d; i++) f[i].x /= d, f[i].y /= d;
	}
}
int main() {
	n = read(), m = read();
	for(int i = 0; i <= n; i++) f[i].x = read();
	for(int i = 0; i <= m; i++) f[i].y = read();
	for(d = 1; d <= n+m; d <<= 1);
	for(int i = 0; i < d; i++) id[i] = (id[i >> 1] >> 1) | ((i & 1) ? (d >> 1) : 0);
	fft(f, 1);
	for(int i = 0; i < d; i++) f[i] = f[i] * f[i];
	fft(f, -1);
	for(int i = 0; i < d; i++) f[i].y /= 2;
	for(int i = 0; i <= n+m; i++) printf("%d ", int(f[i].y + 0.5));
	return 0;
}

```

---

## NTT

我们之前都是在复数域内搞东西，但如果在模意义下，系数可能较大，题目要求取模。这时 FFT 就无用武之地了。幸运的是，我们有完美的替代品：NTT。

这里需要用到 [原根](https://blog.csdn.net/qq_41996523/article/details/111708138?ops_request_misc=%25257B%252522request%25255Fid%252522%25253A%252522161181167516780261946569%252522%25252C%252522scm%252522%25253A%25252220140713.130102334.pc%25255Fblog.%252522%25257D&request_id=161181167516780261946569&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_v2~rank_v29-1-111708138.pc_v2_rank_blog_default&utm_term=%25E5%258E%259F%25E6%25A0%25B9)。

我们可以把 $g^{j(p-1)/n}$ 当成 $n$ 次单位根$w_n^j$。

1. $w_n^j=w_n^{j+kn},k\in\Z$
2. $w_n^j=w_{2n}^{2j}$
3. $w_{2n}^{j+n}=-w_{2n}^j$

我们仍然有这些性质成立。

于是我们可以把它直接看成是单位根，FFT就变成NTT了。所有运算在模意义下完成。

[常见的模数和它的原根](http://blog.miskcoo.com/2014/07/fft-prime-table)

主要记住：

998244353，原根是 3

1004535809，原根是 3

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
const int MAXN = 5e6 + 5;
const int P = 998244353, G = 3, invG = 332748118;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
int n, m, d, id[MAXN];
ll f[MAXN], g[MAXN];
ll qpow(ll a, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, a = mul(a, a)) 
		if(n & 1) ret = mul(ret, a);
	return ret;
}
void NTT(ll* f, int n, int fl) {
	for(int i = 0; i < n; i++) if(i < id[i]) swap(f[i], f[id[i]]);
	for(int l = 2, hl = 1; l <= n; l <<= 1, hl <<= 1) {
		ll g0 = qpow(fl == 1 ? G : invG, (P-1) / l);
		for(int i = 0; i < n; i += l) {
			ll gn = 1;
			for(int j = i; j < i + hl; j++, gn = mul(gn, g0)) {
				ll tt = mul(f[j+hl], gn);
				f[j+hl] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
		}
	}
	if(fl == -1) {
		ll invn = qpow(n, P-2);
		for(int i = 0; i < n; i++) f[i] = mul(f[i], invn);
	}
}
int main() {
	n = read(); m = read();
	for(int i = 0; i <= n; i++) f[i] = read();
	for(int i = 0; i <= m; i++) g[i] = read();
	for(d = 1; d <= n+m; d <<= 1);
	for(int i = 0; i < d; i++) id[i] = (id[i >> 1] >> 1) | ((i & 1) ? (d >> 1) : 0);
	NTT(f, d, 1); NTT(g, d, 1);
	for(int i = 0; i < d; i++) f[i] = mul(f[i], g[i]);
	NTT(f, d, -1);
	for(int i = 0; i <= n+m; i++) printf("%lld ", f[i]);
	printf("\n");
	return 0;
}
```

## 多项式乘法封装

```cpp
#define clr(f, s, e) memset(f+(s), 0x00, sizeof(int) * ((e) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(int) * (n))
const int MAXN = (1 << 18) + 1, bas = 1 << 18, P = 998244353, G = 3, invG = 332748118;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int tf, tr[MAXN], _g[2][MAXN], inv[MAXN];
void init() {
	inv[1] = 1; for(int i = 2; i < MAXN; i++) inv[i] = mul(P - P / i, inv[P % i]);
	for(int i = 0; i < bas; i++) {
		_g[1][i] = qpow(G, (P-1) / bas * i);
		_g[0][i] = qpow(invG, (P-1) / bas * i);
	}
}
int getlim(int n) {
	int lim = 1; for(; lim < n + n; lim <<= 1);
	return lim;
}
void tpre(int lim) {
	if(lim == tf) return ;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(int* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l)
			for(int j = i; j < i+k; j++) {
				ll tt = mul(f[j+k], _g[fl][(j-i) * (bas / l)]);
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

```

## 任意模数多项式乘法

[P4245 【模板】任意模数多项式乘法](https://www.luogu.com.cn/problem/P4245)

>  给 2 个多项式 $F(x),G(x)$，求 $F(x)G(x)$。系数对 $p$ 取模，不保证 $p$ 是 NTT 模数。

也就是MTT，使用 4 次 FFT 完成任意模数的多项式乘法。

设 $K=2^{15}$，我们把多项式每项系数分为两部分（高低位）。 
$$
F(x)=K\cdot F_1(x)+F_0(x)
\\
G(x)=K\cdot G_1(x)+G_0(x)
\\
\therefore
F(x)G(x)=K^2\cdot F_1(x)G_1(x)+K\cdot [F_1(x)G_0(x)+F_0(x)G_1(x)]+F_0(x)G_0(x)
$$
如何快速得到这四个多项式的点值表示？

构造
$$
P(x)=F_0(x)+iG_0(x)
\\
Q(x)=F_0(x)-iG_0(x)
$$
我们惊奇地发现：
$$
\mathrm{DFT}(P)[j]=P(w_n^j)=F_0(w_n^j)+iG_0(w_n^j)
\\
=\sum_{k=0}^{n-1}F_0[k]w_n^{kj}+i\sum_{k=0}^{n-1}G_0[k]w_n^{kj}
\\
=\sum_{k=0}^{n-1}(F_0[k]+iG_0[k])(\cos(\dfrac {2\pi kj}{n})+i\sin(\dfrac{2\pi kj}n))
\\
=\sum_{k=0}^{n-1}(F_0[k]\cos(\dfrac{2\pi kj}n)-G_0[k]\sin(\dfrac {2\pi kj}n))+\\
i\sum_{k=0}^{n-1}(F_0[k]\sin(\dfrac {2\pi kj}n)+G_0[k]\sin(\dfrac {2\pi kj}n))
$$


同理
$$
\mathrm{DFT}(Q)[n-j]=P(w_n^{-j})=F_0(w_n^{-j})-iG_0(w_n^{-j})
\\
=\sum_{k=0}^{n-1}F_0[k]w_n^{-kj}-i\sum_{k=0}^{n-1}G_0[k]w_n^{-kj}
\\
=\sum_{k=0}^{n-1}(F_0[k]-iG_0[k])(\cos(\dfrac {2\pi kj}{n})-i\sin(\dfrac{2\pi kj}n))
\\
=\sum_{k=0}^{n-1}(F_0[k]\cos(\dfrac{2\pi kj}n)-G_0[k]\sin(\dfrac {2\pi kj}n))+\\
i\sum_{k=0}^{n-1}(F_0[k]\sin(\dfrac {2\pi kj}n)+G_0[k]\sin(\dfrac {2\pi kj}n))
$$
故 $P$ 的第 $j$ 项点值与 $Q$ 的第 $n-j$ 项点值共轭。

于是我们可以使用 1 次 FFT 得到 $P(x)$ 和 $Q(x)$ 的点值，再解方程就可得到 $F_0(x)$ 和 $G_0(x)$ 的点值。

同样地可得到 $F_1(x),G_1(x)$，使用了 2 次FFT。

然后考虑怎么求解 回系数。

构造
$$
P(x)=F_1(x)G_1(x)+i(F_1(x)G_0(x)+F_0(x)G_1(x))
\\
Q(x)=F_0(x)G_0(x)
$$
做两次 IDFT 即可。	

```cpp
#define clr(f, s, t) memset(f + (s), 0x00, sizeof(int) * ((t) - (s)))
#define cpy(f, g, n) memcpy(g, f, sizeof(int) * (n))
const int MAXN = (1 << 19) + 5, bas = 1 << 19;
const db PI = acos(-1.0);
int P;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
struct cp {db x, y;};
cp operator + (const cp& a, const cp& b) {return (cp){a.x + b.x, a.y + b.y};}
cp operator - (const cp& a, const cp& b) {return (cp){a.x - b.x, a.y - b.y};}
cp operator * (const cp& a, const cp& b) {return (cp){a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};}
cp operator * (const cp& a, const db& k) {return (cp){a.x * k, a.y * k};}
const cp I = (cp){0, 1};
cp _g[2][MAXN];
int tr[MAXN], tf;
void init() {
	for(int i = 0; i < bas; i++) {
		db a = cos(2 * PI * i / bas), b = sin(2 * PI * i / bas);
		_g[1][i] = (cp){a, b};
		_g[0][i] = (cp){a, -b};
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
ll tran(db x) {return ((ll)(x > 0 ? x + .5 : x - .5) % P + P) % P;}
void FFT(cp* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
		for(int i = 0; i < lim; i += l)
			for(int j = i; j < i+k; j++) {
				cp tt = f[j+k] * _g[fl][(j-i) * (bas / l)];
				f[j+k] = f[j] - tt;
				f[j] = f[j] + tt;
			}
	if(!fl) for(int i = 0; i < lim; i++) f[i].x /= lim, f[i].y /= lim;
}
void Mul(int* f, int* g, int* h, int n) {
	static cp f0[MAXN], f1[MAXN], g0[MAXN], g1[MAXN];
	int lim = getlim(n);
	for(int i = 0; i < n; i++) f0[i].x = f[i] >> 15, f0[i].y = f[i] & 32767;
	for(int i = 0; i < n; i++) g0[i].x = g[i] >> 15, g0[i].y = g[i] & 32767;
	for(int i = n; i < lim; i++) f0[i] = (cp){0, 0};
	for(int i = n; i < lim; i++) g0[i] = (cp){0, 0};
	FFT(f0, lim, 1); FFT(g0, lim, 1);
	for(int i = 0; i < lim; i++) {
		f1[i] = f0[i ? lim - i : 0], f1[i].y *= -1;
		g1[i] = g0[i ? lim - i : 0], g1[i].y *= -1;
	}
	for(int i = 0; i < lim; i++) {
		cp a = (f0[i] + f1[i]) * 0.5;		//f0
		cp b = (f1[i] - f0[i]) * 0.5 * I;	//f1
		cp c = (g0[i] + g1[i]) * 0.5;		//g0
		cp d = (g1[i] - g0[i]) * 0.5 * I;	//g1
		f0[i] = a * c + I * (a * d + b * c);
		g0[i] = b * d;
	}
	FFT(f0, lim, 0); FFT(g0, lim, 0);
	for(int i = 0; i < n; i++)
		h[i] = (1ll * tran(f0[i].x) * (1 << 30) + 1ll * tran(f0[i].y) * (1 << 15) % P + tran(g0[i].x)) % P;
	clr(h, n, lim);
}
```

