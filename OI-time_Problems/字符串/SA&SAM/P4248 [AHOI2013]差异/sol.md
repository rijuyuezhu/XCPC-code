# P4248 [AHOI2013]差异 解题报告

[link](https://www.luogu.com.cn/problem/P4248)

## 题目大意

给一个长度为 $n$ 的字符串 $S$，记 $T_i$ 为后缀 $i$（即 $S[i\dots n]$），$\mathrm{lcp}(S,T)$ 为字符串 $S$ 与字符串 $T$ 的最长公共前缀。

求：
$$
\sum\limits_{1\le i<j\le n}(|T_i|+|T_j|-2|\mathrm{lcp}(T_i, T_j)|)
$$

- $n \le 5\times 10 ^ 5$

## 解题报告

首先式子的前一部分比较好算。
$$
\sum\limits_{1\le i < j \le n}(|T_i|+|T_j|)\\
=\sum\limits_{1\le i<j\le n}(i+j)
=\dfrac{n(n-1)(n+1)}2
$$
$(i,j)$ 一共有 $\dfrac{n(n-1)}2$ 对，且根据对称性所有的 $(i,j)$ 的平均数为 $n+1$。

那么考虑后面的那个 $A=\sum\limits_{1\le i<j\le n}(|\mathrm{lcp}(T_i,T_j|)$ 怎么求。它相当于任意两个不相邻的后缀的 $\mathrm{lcp}$。根据 **LCP Theorem**，我们只要求所有的 $(i,j)$，$\mathrm{height}(i..j)=\min\{\mathrm{height}(k)|i<k\le j\}$

这个可以方便地用单调栈维护。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e6 + 5, INF = 0x3f3f3f3f;
int n, sa[MAXN], rk[MAXN], ht[MAXN], x[MAXN], y[MAXN], c[MAXN], L[MAXN], R[MAXN], stk[MAXN], stp;
char s[MAXN];
ll ans;
void SuffixSort() {
	int m = 300;
	for(int i = 1; i <= n; i++) c[x[i] = s[i]]++;
	for(int i = 2; i <= m; i++) c[i] += c[i-1];
	for(int i = n; i >= 1; i--) sa[c[x[i]]--] = i;
	for(int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for(int i = n - k + 1; i <= n; i++) y[++num] = i;
		for(int i = 1; i <= n; i++) if(sa[i] > k) y[++num] = sa[i] - k;
		for(int i = 1; i <= m; i++) c[i] = 0;
		for(int i = 1; i <= n; i++) c[x[i]]++;
		for(int i = 2; i <= m; i++) c[i] += c[i-1];
		for(int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
		for(int i = 1; i <= n; i++) swap(x[i], y[i]);
		x[sa[1]] = num = 1;
		for(int i = 2; i <= n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k]) ? num : ++num;
		m = num;
		if(n == m) break;
	}
}
void GetHeight() {
	for(int i = 1; i <= n; i++) rk[sa[i]] = i;
	for(int i = 1, k = 0; i <= n; i++) {
		if(k) --k;
		if(rk[i] == 1) {ht[rk[i]] = 0; continue;}
		int j = sa[rk[i] - 1];
		while(i+k <= n && j+k <= n && s[i+k] == s[j+k]) k++;
		ht[rk[i]] = k;
	}
}
ll calc() {
	stp = 0; ht[0] = -INF; stk[++stp] = 0;
	for(int i = 1; i <= n; i++) {
		while(stp && ht[stk[stp]] > ht[i]) stp--;
		L[i] = stk[stp] + 1;
		stk[++stp] = i;
	}
	stp = 0; ht[n+1] = -INF; stk[++stp] = n+1;
	for(int i = n; i >= 1; i--) {
		while(stp && ht[stk[stp]] >= ht[i]) stp--;
		R[i] = stk[stp] - 1;
		stk[++stp] = i;
	}
	ll ret = 0;
	for(int i = 1; i <= n; i++) ret += 1ll * ht[i] * (1ll * (i - L[i] + 1) * (R[i] - i + 1));
	return ret;
}

int main() {
	scanf("%s", s+1); n = strlen(s+1);
	ans = 1ll * n * (n - 1) * (n + 1) / 2;
	SuffixSort(); GetHeight(); ans -= 2 * calc();
	printf("%lld\n", ans);
	return 0;
}
```

