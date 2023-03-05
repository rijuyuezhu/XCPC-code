# 二次剩余 学习笔记

## 学习资料

[OI-wiki](https://oi-wiki.org/math/quad-residue), [rqy's blog](https://www.luogu.com.cn/blog/rqy/er-ci-sheng-yu)。

## 约定

以下 $p$ 均代指 **奇素数**，$\mathbb F_p$ 指 $\bmod p$ 的域。

## 二次剩余

### 定义

若 $\exist y\in \mathbb F_p\wedge y\not\equiv 0\pmod p$ 使得 $x\equiv y^2\pmod p$，则 $x$ 是 $\bmod p$ 意义下的二次剩余；不存在这样的 $y$，则 $x$ 称为非二次剩余。

### 性质

一、在 $1,2,\cdots,p-1$ 中恰有 $\dfrac{p-1}2$ 个二次剩余， $\dfrac{p-1}2$ 个非二次剩余。

设 $g$ 为 $\mathbb F_p$ 的原根，则二次剩余恰为 $1,g^2,g^4,\cdots,g^{p-3}$

二、$xy$ 是二次剩余当且仅当 $x,y$ 均是二次剩余或均不是二次剩余。

三、勒让德符号
$$
\left(\dfrac a p\right)=
\left\{\begin{matrix}
0 & a\equiv 0\pmod p\\
1 & a 是二次剩余\\
-1 & a不是二次剩余
\end{matrix}\right.
$$
有 $\left(\dfrac a p\right)\equiv a^{(p-1)/2}$. 这就是二次剩余的判断方法。

**证：**

设 $a=g^u$，则 $a^{(p-1)/2}=g^{u(p-1)/2}$

当 $u$ 是奇数（即 $a$ 为非二次剩余）时，$g^{u(p-1)/2}\equiv g^{(p-1)/2}\equiv -1$.

当 $u$ 是偶数（即 $a$ 为非二次剩余）时，$g^{u(p-1)/2}\equiv g^0\equiv 1$.

Q.E.D.

根据性质二，有
$$
\left(\dfrac {ab}p\right)\equiv\left(\dfrac ap\right)\left(\dfrac bp\right)
$$

### 求二次剩余：Cipolla 算法

如何快速求一个 $x$，使 $x^2\equiv n\pmod p$ （$n$ 是 $\bmod p$ 的二次剩余）？

首先我们先找到一个 $a$，使得 $a^2-n$ 为 **非二次剩余**。可以证明这样的 $a$ 有 $\dfrac{p-1}2$ 个，直接随机判断即可。

然后我们建立“复数域”。定义 $i^2\equiv a^2-n$。

则 $x^2\equiv n\pmod p$ 的解为 $(a+i)^{(p+1)/2}$.

### Cipolla算法的证明

首先有一些定理：

定理1： $(a+b)^p\equiv a^p+b^p\pmod p$。

二项式定理展开即可。

定理2： $i^p\equiv -i$

**证：**
$$
i^p\equiv i^{p-1}\cdot i\\
\equiv (i^2)^{(p-1)/2}\cdot i\\
\equiv (a^2-n)^{(p-1)/2}\cdot i
\equiv -i\\
Q.E.D.
$$
有了这两个定理，那么我们可以验证：
$$
x\equiv (a+i)^{(p+1)/2}\\
\equiv ((a+i)^p(a+i))^{1/2}\\
\equiv ((a^p+i^p)(a+i))^{1/2}\\
\equiv ((a-i)(a+i))^{1/2}\\
\equiv (a^2-i^2)^{1/2}
\equiv n^{1/2}
$$
故 $x\equiv (a+i)^{(p+1)/2}\equiv n^{1/2}$。

接下来还要说明 $x\in \mathbb F_p$。由于域中的 $k$ 次方程至多有 $k$ 个解，而 $n$ 为二次剩余，所以 $x\in \mathbb F_p$。当然还有一解为 $-x$。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
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
ll n;
ll P, a, I2;
struct F2 {ll x, y;};
F2 operator * (const F2& A, const F2& B) {return (F2){A.x * B.x % P + I2 * (A.y * B.y % P) % P, (A.x * B.y + A.y * B.x) % P};}
ll qpow(ll a, int n) {ll ret = 1; for(; n; n >>= 1, a = a * a % P) if(n & 1) ret = ret * a % P; return ret;}
F2 qpow(F2 a, int n) {F2 ret = (F2){1, 0}; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
ll judge(ll a) {return qpow(a, (P-1) / 2);}
void work() {
	n = read(); P = read();
	ll k = judge(n);
	if(k == 0) {
		printf("0\n");
		return ;
	} else if(k == P-1) {
		printf("Hola!\n");
		return ;
	}
	while(1) {
		a = rand() % P;
		I2 = (a * a % P + P - n) % P;
		if(judge(I2) == P-1) break;
	}
	ll ans1 = qpow((F2){a, 1}, (P+1) / 2).x % P;
	ll ans2 = P-ans1;
	if(ans1 > ans2) swap(ans1, ans2);
	printf("%lld %lld\n", ans1, ans2);
}
	

int main() {
	int T = read();
	while(T--) work();
	return 0;
}
```

