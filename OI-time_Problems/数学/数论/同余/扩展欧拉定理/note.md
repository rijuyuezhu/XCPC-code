# 扩展欧拉定理 学习笔记

[toc]

## 例题

[P5091 【模板】扩展欧拉定理](https://www.luogu.com.cn/problem/P5091)

## 题目大意

给出 $a,m,b$，求 $a^b\bmod m$.

- $1\le a\le 10^9,1\le b\le 10^{20000000},1\le m\le10^8$

## 算法

我们之前就知道，在模 $m$ 意义下，我们可以方便地完成以下运算：

**加减**： ${(a\pm b)\bmod m=(a\bmod m\pm b\bmod m)\bmod m}$

**乘**：$(ab)\bmod m=((a\bmod m)\cdot(b\bmod m))\bmod m$

如果 $b$ 模 $m$ 有逆元（即 $b\perp m$），那么还可以有除法：

**除**：$\dfrac{a}{b}\bmod m=(ab^{-1})\bmod m$





那么这道题要我们求在模 $m$ 意义下的**乘方**。

怎么求？

大家都会快速幂，知道这个问题可以在 $\mathcal O(log\ b)$ 的复杂度下解决。问题是， $b$ 再大一点?

在此给出结论（即扩展欧拉定理）：

1. 当 $b< \varphi(m)$ 时，可以直接计算
2. 当 $b\ge \varphi(m)$时， 有 $a^b \equiv a^{b \bmod \varphi(m)+\varphi(m)} \pmod m$

值得注意的是，请一定要弄清 $b$ 和 $\varphi(m)$ 的大小关系，否则可能出错！！！

详细证明请看 **Reference**

## 代码

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
ll a, b, m;
ll phi;
ll qpow(ll a, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, a = a * a % m)
		if(n & 1) ret = ret * a % m;
	return ret;
}
int main() {
	a = read(), m = read();
	phi = m; ll tmp = m;
	for(int i = 2; i * i <= tmp; i++) 
		if(tmp % i == 0) {
			phi = phi / i * (i-1);
			while(tmp % i == 0) tmp /= i;
		}
	if(tmp > 1) phi = phi / tmp * (tmp-1);
	bool flag = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar());
	for(; ch >= '0' && ch <= '9'; ch = getchar()) {
		b = b * 10 + ch - '0';
		if(b >= phi) flag = 1;
		b %= phi;
	}
	printf("%lld\n", qpow(a, b + flag * phi));
	return 0;
}
```

## Reference

[ouuan的洛谷博客](https://www.luogu.com.cn/blog/ouuan/solution-p5091)



