# P3592 [POI2015]MYJ 解题报告

- 一道比较不错的区间DP

[P3592 [POI2015]MYJ](https://www.luogu.com.cn/problem/P3592)

## 思路

### DP部分

容易发现，由于每个点的值不是1，不能够转化为贪心模型。所以我们考虑DP做法。

一个人 $i$ 消费多少取决于在区间 $[a_i, b_i]$ 的最小值。问题初步有两个维度：区间和这个最小值。先设状态为 $f(l, r, k)$ 表示：所有 **区间$[l,r]$内消费者** 当区间最小值为 $k$ 时的总消费最小值。这里所说的 **区间内** 指完全嵌入区间，即 $l\le a_i \le b_i\le r$ 的。
于是有状态转移方程为：

$$f(i,j,k)=\min_{i\le pos\le j}\{f(i,pos-1,m)+f(pos+1,j,n)+k\cdot g(pos,k)\}(m,n\ge k)$$

其中 $g(pos,k)$ 表示：在当前区间 $[l,r]$ 内的消费者（“区间内”定义同上）中，经过了 $pos$ 且 $c_i\le k$ 的数量。这一部分消费者的贡献就是 $k$.

我们发现，这个第三维很麻烦，我们完全不需要一个 $k$ 具体的值，于是把状态改成这样： $f(l, r, k)$ 表示：所有 **区间$[l,r]$内消费者** 当区间最小值 $\ge k$ 时的总消费最小值。

转移方程变为：

$$f(i,j,k)=\min_{i\le pos\le j}\{f(i,pos-1,k)+f(pos+1,j,k)+k\cdot g(pos,k)\}$$

$$f(i,j,k)\gets^{update}f(i,j,k+1)$$

不重不漏，get√。时间复杂度 $\mathcal O(n^3m)$

### 方案部分

求方案非常 naive。由于状态由两方面转移过来，我们记录两个值：一个是 $k$ 要往上跳到哪里，一个是断点 $pos$ 的位置。最后用一个 dfs 就可以完成。

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
const int MAXN = 55, MAXM = 4005;
ll n, m, a[MAXM], b[MAXM], c[MAXM], lsh[MAXM], tot, g[MAXN][MAXM], f[MAXN][MAXN][MAXM], pos[MAXN][MAXN][MAXM], lstk[MAXN][MAXN][MAXM], ans[MAXN];

void LSH() {
	sort(lsh + 1, lsh + 1 + tot);
	tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(ll x) {
	return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}


void getans(int l, int r, int k) {
	if(k > tot) return;
	if(l > r) return;
	k = lstk[l][r][k];
	ans[pos[l][r][k]] = lsh[k];
	getans(l, pos[l][r][k] - 1, k);
	getans(pos[l][r][k] + 1, r, k);
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= m; i++) a[i] = read(), b[i] = read(), c[i] = read(), lsh[++tot] = c[i];
	LSH();
	for(int i = 1; i <= m; i++) c[i] = LSH(c[i]);

	for(int len = 1; len <= n; len++)
		for(int l = 1; l + len - 1 <= n; l++) {
			int r = l + len - 1;
			
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= tot; j++)
					g[i][j] = 0;
			for(int i = 1; i <= m; i++)
				if(l <= a[i] && b[i] <= r)
					g[a[i]][c[i]]++, g[b[i]+1][c[i]]--;
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= tot; j++)
					g[i][j] += g[i-1][j];
			for(int i = 1; i <= n; i++)
				for(int j = tot; j >= 1; j--)
					g[i][j] += g[i][j+1];

			for(int k = tot; k >= 1; k--) {
				for(int p = l; p <= r; p++) {
					ll val = (p > l ? f[l][p-1][k] : 0) + (p < r ? f[p+1][r][k] : 0) + lsh[k] * g[p][k];
					if(f[l][r][k] <= val) {
						f[l][r][k] = val;
						pos[l][r][k] = p;
					}
				}
				if(f[l][r][k] >= f[l][r][k+1]) lstk[l][r][k] = k;
				else f[l][r][k] = f[l][r][k+1], lstk[l][r][k] = lstk[l][r][k+1];
			}
		}
	printf("%lld\n", f[1][n][1]);
	getans(1, n, 1);
	for(int i = 1; i <= n; i++) printf("%lld ", ans[i] ? ans[i] : 1);
	printf("\n");
	return 0;
}
```

