# P4451 [国家集训队]整数的lqp拆分

[link](https://www.luogu.com.cn/problem/P4451)

## 题目大意

给出 $n$，求
$$
\sum_{a_1,a_2,\cdots a_m是 n 的一组拆分}\prod_{i=1}^mFib_{a_i}
$$
其中 $Fib_{i}$ 表示斐波那契数列第 $i$ 项（即 $Fib_0=0,Fib_1=1,Fib_i=Fib_{i-1}+Fib_{i-2}(i\ge 2)$）

$n\le 10^{10000}$。

## 解题报告

设 $dp_n$ 表示将 $n$ 拆分所有情况的权值和。

则有 
$$
dp_n = \sum_{i=1}^ndp_{n-i}Fib_i(n\ge 1)
$$
考虑边界情况得 $dp_0=1$。

设 
$$
D(x)=\sum_{n\ge 0} dp_nx^n
\\
G(x)=\sum_{n\ge 0}Fib_nx^n=\dfrac{x}{1-x-x^2}
$$
则
$$
D(x)=\sum_{n\ge 0}dp_nx^n=1+\sum_{n\ge 1}dp_nx^n
\\
= 1+\sum_{n\ge 1}\sum_{i=1}^ndp_{n-i}Fib_ix^n
\\
= 1+\sum_{i\ge 1}Fib_ix^i\sum_{n\ge i}dp_{n-i}x^{n-i}
\\
=1+G(x)D(x)
$$
则
$$
D(x)=\dfrac 1 {1-G(x)}=1+\dfrac{x}{1-2x-x^2}
$$
设
$$
D(x)=1+\dfrac{A}{1-ax}+\dfrac{B}{1-bx}\\
=1+\dfrac{A+B-(Ab+Ba)x}{1-(a+b)x+abx^2}\\
=1+\dfrac{x}{1-2x-x^2}
$$
则
$$
\left\{
\begin{matrix}
A+B=0 \\
Ab+Ba=-1\\
a+b=2\\
ab=-1
\end{matrix}
\right.
$$
有一组解为 
$$
\left\{
\begin{matrix}
a=1+\sqrt 2\\
b=1-\sqrt 2\\
A=\dfrac{\sqrt 2}4\\
B = -\dfrac{\sqrt 2}4
\end{matrix}
\right.
$$
故
$$
D(x)=1+\dfrac{\sqrt 2}4\left(\dfrac{1}{1-(1+\sqrt 2)x}-\dfrac{1}{1-(1-\sqrt2)x}\right)
\\
=1+\dfrac{\sqrt 2}4((1+\sqrt 2)^nx^n-(1-\sqrt 2)x^n)
\\
[x^n]D(x)=\dfrac {\sqrt 2}4((1+\sqrt 2)^n-(1-\sqrt 2)^n)(n\ge 1)
$$
而由于 $\sqrt 2 \equiv 59713600\pmod {10^9+7}$，直接快速幂计算即可。注意先用费马小定理缩减 $n$ 的范围。

Tips: 这里求单个二次剩余不要傻乎乎地跑 Cipolla，直接枚举即可。

```c
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
ll read(int mod) {
	ll x = 0; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar());
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x * 10 + int(ch - '0')) % mod;
	return x;
}
const int P = 1e9 + 7, sqrt2 = 59713600;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n;
int main() {
	n = read(P-1);
	printf("%lld\n", 1ll * sqrt2 * qpow(4, P-2) % P * mns(qpow(pls(1, sqrt2), n), qpow(mns(1, sqrt2), n)) % P);
	return 0;
}
```