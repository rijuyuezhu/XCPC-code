# LOJ#6074. 「2017 山东一轮集训 Day6」子序列

先考虑全局询问怎么做，设 $f(i,c)$ 表示在 $S_{1\cdots i}$ 中，最后一个选取 $\max\{j|j\le i,S_j=c\}$ 的子序列个数。本质上是在子序列自动机的 DAG 上计数路径，可以保证本质不同。

转移很简单：

$$
\begin{gathered}
f(i,c)=f(i-1,c),(c\ne S_i)
\\
f(i,c)=\sum_{j=0}^9f(i-1,j),(c=S_i)
\end{gathered}
$$
其中 $f(0,0)=1$ 特殊定义，字符集占位 $1\cdots 9$。

考虑怎么运用到区间查询上。初始状态为

$$
P_0=\begin{bmatrix}
    1 & 0 & \cdots & 0
\end{bmatrix}^T
$$

转移为

$$
F_i=\begin{bmatrix}
    1 \\
    &1\\
    &&\ddots\\
    1 & 1 & 1& 1 & 1& 1\\
    &&&&\ddots\\
    &&&&&1
\end{bmatrix}
$$
其中第 $S_i$ 行为 1。

则有 $P_n=F_n\cdots F_2F_1P_0$

试着对 $F_i$ 求个逆（可以用初等变换），发现

$$
B_i=F_i^{-1}=\begin{bmatrix}
    1 \\
    &1\\
    &&\ddots\\
    -1 & -1 & -1& 1 & -1& -1\\
    &&&&\ddots\\
    &&&&&1
\end{bmatrix}
$$

对角线为 1，第 $S_i$ 行除了第 $S_i$ 列以外为 -1。

则我们求

$$
P=F_rF_{r-1}\cdots F_lP_0=\hat F_r\hat B_{l-1}P_0
$$

或者写好一点，

$$
ans=\begin{bmatrix}
    1 & 1 & \cdots & 1
\end{bmatrix}\hat F_r\hat B_{l-1}\begin{bmatrix}
    1 & 0 & \cdots & 0
\end{bmatrix}^T
$$
其中 $\hat F_n=F_nF_{n-1}\cdots F_1$，即左乘前缀积；$\hat B_n=B_1B_2\cdots B_n$，即右乘前缀积。

如果直接做，复杂度是 $O((n+q)m^3)$。由于 $F_i,B_i$ 都相当稀疏，考虑直接递推得出。

左乘 $F_n$，相当于**在原来基础上**把第 $S_n$ 行的每个数变成了它们这一列的和。

考虑求 $\begin{bmatrix}1 & 1 & \cdots & 1\end{bmatrix}\hat F_n$，这相当于求它各列的和。于是我们维护每一列的和，即可 $O(m)$ 单次转移。

右乘 $B_n$，相当于**在原来基础上**将每一行的每一个数（除了第 $S_i$ 列的数）都减去当前行第 $S_i$ 列的数。

考虑求 $\hat B_n\begin{bmatrix} 1 &0 & \cdots & 0\end{bmatrix}^T$，这相当于求它的第一列的每个数。维护第一列每个数的值和每行的全局增减标记即可。

时间复杂度 $O((n+m)q)$。

```cpp
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5, P = 1e9 + 7, M = 9;
namespace MINT {
	struct mint {
		int v;
		mint(int v = 0) : v(v) {}
	};
	int MOD(int v) {return v >= P ? v - P : v;}
	mint tran(int v) {return MOD(v % P + P);}
	mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
	mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
	mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
	mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
} using namespace MINT;
char s[MAXN];
int n, q;
mint f[MAXN][M+1], b[MAXN][M+1], tag[MAXN][M+1], matf[M+1][M+1], matb[M+1][M+1];
int main() {
	scanf("%s", s+1); n = strlen(s+1);
	q = read();
	for(int i = 0; i <= M; i++) f[0][i] = 1, matf[i][i] = 1, matb[i][i] = 1, tag[0][i] = 0;
	b[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		int c = s[i] - 'a' + 1;
		for(int j = 0; j <= M; j++) {
			f[i][j] = f[i-1][j] - matf[c][j] + f[i-1][j];
			matf[c][j] = f[i-1][j];
			tag[i][j] = tag[i-1][j] - (matb[j][c] + tag[i-1][j]); matb[j][c] = matb[j][c] + (matb[j][c] + tag[i-1][j]);
			b[i][j] = matb[j][0] + tag[i][j];
		}
	}
	for(int i = 1; i <= q; i++) {
		int l = read(), r = read();
		mint ans = 0;
		for(int j = 0; j <= M; j++) ans = ans + f[r][j] * b[l-1][j];
		printf("%d\n", (ans-1).v);
	}
	return 0;
}
```