# LOJ#6070. 「2017 山东一轮集训 Day4」基因 解题报告

塔从左到右，编号形成一个 $1\sim n$ 的排列 $p_i$。于是有不等式：

$$
\forall i\in[2,n],x_i-x_{i-1}\ge \max(p_{i-1},p_i)
$$

设区间 $[1,x_1]$ 的长度为 $y_1$，区间 $[x_{i-1}+1,x_i]$ 的长度为 $y_i(2\le i\le n)$，区间 $[x_n+1,l]$ 的长度为 $y_{n+1}$，则有

$$
\begin{gathered}
    y_1+y_2+\cdots+y_{n+1}=l
    \\
    y_1\ge 1,y_{n+1}\ge 0
    \\
    y_i\ge \max(p_{i-1},p_i),2\le i\le n
\end{gathered}
$$

设 $s=\sum_{i=2}^n\max(p_{i-1},p_i)$，则不定方程解的个数为

$$
\binom{l-s-1+n}{n}
$$

只与 $s$ 有关。接下来的问题是，有多少这样的排列 $p$ 使得 $\sum_{i=2}^n\max(p_{i-1},p_i)=s$。

考虑 dp。从小到大考虑 $[1,n]$ 中的每个数将它们往排列上去填。设 $f(i,j,k)$ 表示填了 $[1,n]$，当前 $s=j$，排列分成了 $k$ 个连通块的排列数量。那么讨论 $i$ 的位置：

1. $i$ 独自形成了一个新的连通块，对 $s$ 没有贡献，

$$
f(i,j,k)\gets k\cdot f(i-1,j,k-1)
$$

2. $i$ 依附在某个连通块的左/右，对 $s$ 有一次贡献，

$$
f(i,j,k)\gets 2k\cdot f(i-1,j-i,k)
$$

3. $i$ 连接了两个连通块，对 $s$ 有两次贡献，

$$
f(i,j,k)\gets k\cdot f(i-1,j-2i,k+1)
$$

$s=j$ 的上界大概是 $n(n+1)$，时间复杂度 $O(n^4)$。

接下来问题变为，如何求

$$
\binom{l-s-1+n}{n}
$$

由于 $m$ 不一定小，也不一定是质数，所以它并不好算。注意到 $n$ 特别小，我们可以矩阵快速幂 $f_{0\cdots n}$，求出 $L$ 行的 $0\cdots n$。然后，再进行递推即可。这部分时间复杂度 $O(n^3\log l + n^3)$

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
const int MAXN = 105;
int P=1;
struct mint {
	int v;
	mint(int v = 0) :v(v) {}
};
int MOD(int v) {return v >= P ? v - P : v;}
mint tran(int v) {return MOD(v % P + P);}
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator += (mint& a, mint b) {return a = a + b;}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator -= (mint& a, mint b) {return a = a - b;}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint operator *= (mint a, mint b) {return a = a * b;}
mint qpow(mint a, int n) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
int n, l, lim;
struct Mat {
	mint a[MAXN][MAXN];
	void clear() {
		for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) a[i][j] = 0;
	}
	void setu() {
		for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) a[i][j] = (i == j);
	}
	mint* operator [] (int k) {return a[k];}
	const mint* operator [] (int k) const {return a[k];}
};
Mat operator * (const Mat& a, const Mat& b) {
	Mat c; c.clear();
	for(int i = 0; i <= n; i++)
		for(int k = 0; k <= n; k++)
			for(int j = 0; j <= n; j++)
				c[i][j] += a[i][k] * b[k][j];
	return c;
}
Mat qpow(Mat a, int n) {Mat ret; ret.setu(); for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}


mint f[2][MAXN * MAXN][MAXN];
mint C[MAXN * MAXN][MAXN];
int main() {
	n = read(), l = read(), P = read();
	lim = 0;
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++) {
		int p = i & 1, pre = p ^ 1;
		for(int j = 0; j <= lim; j++)
			for(int k = 0; k <= n; k++) {
				f[p][j][k] = 0;
				if(k >= 1) f[p][j][k] += k * f[pre][j][k-1];
				if(j >= i) f[p][j][k] += 2 * k * f[pre][j-i][k];
				if(j >= 2 * i) f[p][j][k] += k * f[pre][j-2*i][k+1];
			}
		lim += 2 * i;
	}
	lim = min(lim, l - 1);
	Mat T; T.clear();
	for(int i = 0; i <= n; i++) {
		T[i][i] = 1;
		if(i > 0) T[i][i-1] = 1;
	}
	T = qpow(T, l - 1 + n - lim);
	for(int i = 0; i <= n; i++) C[0][i] = T[i][0];
	for(int i = 1; i <= lim; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= n; j++) C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	mint ans = 0;
	for(int i = 0; i <= lim; i++)
		ans += C[i][n] * f[n & 1][lim - i][1];
	printf("%d\n", ans.v);
	return 0;
}
```