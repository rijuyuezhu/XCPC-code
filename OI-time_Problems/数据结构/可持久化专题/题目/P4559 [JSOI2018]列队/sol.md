# P4559 [JSOI2018]列队 解题报告

一道好题。

[link](https://www.luogu.com.cn/problem/P4559)

## 题目大意

数轴上有 $n$ 个点，每个点依次编号为 $1\cdots n$，且具有一个坐标 $x_i$。 $q$ 次询问，每次 **假定**使编号为 $[l,r]$ 的所有点移动到坐标为 $[K,K+r-l]$ 的连续一段，求最小总移动次数。注意是假定，不会真的移动。

$1\le n,m\le 5\times 10^5, 1\le x_i,K\le 10^6$。

## 解题报告

贪心策略可证明，一种最优的方案是每个点相对位置不改变，即按坐标排序，第一名在 $K$，第二名在 $K+1$ ……依此类推。

这个编号为 $[l,r]$  ，很容易想到主席树。接下来的查询只要在主席树上分类讨论就可以了。

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
const int MAXN = 5e5 + 5;
const int MAXK = 1e6 + 5, K = 1e6;
namespace Sgt {
	const int MAXNODE = MAXK << 5;
	struct {int ls, rs; ll sz, sum;}e[MAXNODE];
	int tot;
	void mdy(int& p, int pre, int l, int r, ll x) {
		p = ++tot; e[p] = e[pre];
		e[p].sz++; e[p].sum += x;
		if(l == r) return;
		int m = (l + r) >> 1;
		if(x <= m) mdy(e[p].ls, e[pre].ls, l, m, x);
		else mdy(e[p].rs, e[pre].rs, m+1, r, x);
	}
	ll qry(int u, int v, int l, int r, ll k) {
		ll tsz = e[v].sz - e[u].sz, tsum = e[v].sum - e[u].sum;
		if(tsz == 0) return 0;
		if(r <= k + tsz - 1) return tsz * (2 * k + tsz - 1) / 2 - tsum;
		else if(l >= k) return tsum - tsz * (2 * k + tsz - 1) / 2;
		else {
			int m = (l + r) >> 1; ll lsz = e[e[v].ls].sz - e[e[u].ls].sz;
			return qry(e[u].ls, e[v].ls, l, m, k) + qry(e[u].rs, e[v].rs, m+1, r, k+lsz);
		}
	}
}
using namespace Sgt;
int n, m, rt[MAXN];
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		mdy(rt[i], rt[i-1], 1, K, read());
	}
	for(int i = 1; i <= m; i++) {
		int l = read(), r = read(), k = read();
		printf("%lld\n", qry(rt[l-1], rt[r], 1, K, k));
	}
	return 0;

}
```

