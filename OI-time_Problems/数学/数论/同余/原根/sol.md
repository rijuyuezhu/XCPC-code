# 原根 学习笔记

[toc]

**前排Warning**

以下内容全部都是我自己的随便写写，肯定有所枉谬，还请谅解。想看系统的证明和系统的做法，请直接查阅 **Reference**。

## 题目链接

[P6091 【模板】原根](https://www.luogu.com.cn/problem/P6091)

## 引入

### 何为阶

根据欧拉定理，当 $a\perp n$ 时，有 $a^{\varphi(n)}\equiv 1\pmod n$。

那么我们知道，当 $a\perp n$时，必定存在一个正整数 $x$，使得 $a^x\equiv 1\pmod n$ （因为至少有个 $x=\varphi(n)$满足条件）。

我们把满足条件的**正整数** $x$ 中最小的那个叫做 $a$ 在模 $n$ 意义下的 **阶**。

### 何为原根

原根是一组定义在同余意义下的数。

对于一个数 $n$ ，它的原根是所有满足下列条件的数 $g$:

1. $1\le g<n$
2. $g^{\varphi(n)}\equiv1\pmod n$
3. $g^i\not\equiv 1\pmod n(\forall i,1\le i <\varphi(n))$

**换个定义方法：** 如果 $g$ 在模 $n$ 意义下的阶是 $\varphi(n)$，那么 $g$是原根。

### 原根的性质与求法

为了方便理解和记忆，我们一边说求原根的算法，一边给出若干性质。

所有原根的性质证明请看下方博客。

看看上面那道[例题](https://www.luogu.com.cn/problem/P6091)

我们考虑怎么求一个数 $n$ 的原根。

---



要求原根，我们先判断一个数是否有原根。

#### Theory 1 (原根存在性)

> 只有 $2, 4, p^k,2p^k$ 有原根。其中 $p$ 为**奇**素数，$k$ 为正整数。



---

接下来，我们判断一个数有原根后，先找出它的**最小**原根

#### Theory 2.1 (最小原根的大小)

> 一个数 $n$ 的最小原根大约是 $n^{0.25}$ 级别的。

这使得我们有理有据地去直接**暴力从小到大枚举**自然数来判断其是否是原根。

如何判断一个数是否是 $n$ 的原根？

根据原根定义，我们只需要验证 $a^{\varphi(n)}\equiv 1$ 且 $a^{i}\not \equiv 1(1\le i < \varphi(n))$

那么这妥妥地超时，验证一个数都是 $O(n\log n)$级别的了。

于是我们又有了一个定理。

#### Theory 2.2 （较简易的原根判定定理）

>判断一个数 $g$ 是 $n$ 的原根，只需验证 $a^{\varphi(n)}\equiv 1$ 且 $a^{k}\not \equiv 1$。其中 $k$ 是所有由 $\varphi(n)$ 除去其一个质因子得到的数。即假设 $\varphi(n)=p_1^{a_1}p_2^{a_2}\cdots p_t^{a_t}$, 只要验证所有的$k=\dfrac{\varphi(n)}{p_i}(1\le i\le t)$即可。

如此便保证了复杂度。

---

至此，我们已经求出了**最小**原根，怎么求出所有原根呢？

#### Theory 3 

> 设 $g$ 为 $n$ 的最小原根，那么对于 $n$ 的任意一个原根 $G$，都存在一个 $k$ 使得 $G=g^k$，其中 $k\perp \varphi(n)$。
>
> 于是一个数的原根应当有 $\varphi(\varphi(n))$个。

只要枚举 $k$ 即可。

### 原根与阶的其他性质（先咕着）

### 代码

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
int ip[MAXN], pr[MAXN], tot, phi[MAXN], havert[MAXN], fj[MAXN], cnt, ans[MAXN], anscnt;
void init() {
	ip[1] = 1; phi[1] = 1;
	for(int i = 2; i < MAXN; i++) {
		if(!ip[i]) {pr[++tot] = i; phi[i] = i - 1;}
		for(int j = 1; j <= tot && 1ll * i * pr[j] < MAXN; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) phi[i * pr[j]] = phi[i] * (pr[j] - 1);
			else {
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
		}
	}
	havert[2] = havert[4] = 1;
	for(int j = 2; j <= tot; j++) {
		for(int i = 1; 1ll * i * pr[j] < MAXN; i *= pr[j]) havert[i * pr[j]] = 1;
		for(int i = 2; 1ll * i * pr[j] < MAXN; i *= pr[j]) havert[i * pr[j]] = 1;
	}
}
int ksm(int a, int n, int mod) {
	int ret = 1;
	for(; n; n >>= 1, a = 1ll * a * a % mod)
		if(n & 1) ret = 1ll * ret * a % mod;
	return ret;
}
void fenjie(int n) {
	cnt = 0;
	for(int i = 2; i * i <= n; i++)
		if(n % i == 0) {
			fj[++cnt] = i;
			while(n % i == 0) n /= i;
		}
	if(n > 1) fj[++cnt] = n;
}
bool check(int n, int g) {
	if(ksm(g, phi[n], n) != 1) return 0;
	for(int i = 1; i <= cnt; i++)
		if(ksm(g, phi[n] / fj[i], n) == 1) return 0;
	return 1;
}
int getrt(int n) {
	for(int i = 1; i < n; i++)
		if(check(n, i)) return i;
	return 0;
}
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
void getallrt(int n, int g) {
	anscnt = 0;
	int k = 1;
	for(int i = 1, k = g; i <= phi[n]; i++, k = 1ll * k * g % n)//be careful, i <= phi[n]!!!(when n=2)
		if(gcd(i, phi[n]) == 1) ans[++anscnt] = k;
}
void work() {
	int n = read(), d = read();
	if(!havert[n]) {
		printf("0\n\n");
		return ;
	}
	fenjie(phi[n]);
	int g = getrt(n);
	getallrt(n, g);
	sort(ans + 1, ans + 1 + anscnt);
	printf("%d\n", anscnt);
	for(int i = d; i <= anscnt; i += d) printf("%d ", ans[i]);
	printf("\n");
}
int main() {
	init();
	int T = read();
	while(T--) work();
	return 0;
}
```





## Reference

[证明](https://www.luogu.com.cn/blog/codecodeakioi/solution-p6091)

[模板题题解](https://www.luogu.com.cn/blog/ix-35/solution-p6091)

[原根&离散对数相关——command_block](https://www.luogu.com.cn/blog/command-block/yuan-gen-li-san-dui-shuo-xiang-guan)