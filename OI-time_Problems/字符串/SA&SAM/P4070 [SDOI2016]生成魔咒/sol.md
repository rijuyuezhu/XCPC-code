# P4070 [SDOI2016]生成魔咒 解题报告

[link](https://www.luogu.com.cn/problem/P4070)

## 题目大意

一开始给一个空串 $s$，每次在其最后加入一个字符 $x$，询问每次加入后 $s$ 的本质不同的非空子串的个数。

$|s|\le 10^5, 1\le x\le 10^9.$

## 解题思路1：SAM

我们考虑到SAM的构建本就是一个在线算法，只要计算出每次加入一个字符得到的贡献即可。

具体地说，加入一个字符 $x$ 得到的贡献就为 $len(np)-len(fa(np))$。那么这题就做完了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
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
const int MAXN = 2e5 + 5;
int n, lst = 1, tot = 1;
ll ans;
struct Node{
	map<int, int> ch;
	int fa, len;
}e[MAXN];
void ins(int c) {
	int p = lst, np = lst = ++tot; e[np].len = e[p].len + 1;
	for(; p && !e[p].ch[c]; p = e[p].fa) e[p].ch[c] = np;
	if(!p) e[np].fa = 1;
	else {
		int q = e[p].ch[c];
		if(e[q].len == e[p].len + 1) e[np].fa = q;
		else {
			int nq = ++tot; e[nq] = e[q];
			e[nq].len = e[p].len + 1; e[q].fa = e[np].fa = nq;
			for(; p && e[p].ch[c] == q; p = e[p].fa) e[p].ch[c] = nq;
		}
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		ins(read());
		ans += e[lst].len - e[e[lst].fa].len;
		printf("%lld\n", ans);
	}
	return 0;
}
```

## 解题思路2：SA

我们每次加入一个字符，所有的后缀都会发生变化。于是我们不妨倒转这个串，改为在之前添加字符，这样每次就只增加一个后缀。

不妨把添加变成删除，考虑每次删除头一个字符的贡献。不难发现，贡献为 $n-i+1-\max\{\mathrm{height}(\mathrm{rk}(i)),\mathrm{height}(\mathrm{rk}(i+1))\}$。然后再删去这个位置，更新 $\mathrm{height}$ 即可。这个操作可以用一个链表简单地完成。

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
const int MAXN = 2e5 + 5;
int n;
int s[MAXN], lsh[MAXN], lsh_num, sa[MAXN], rk[MAXN], ht[MAXN], x[MAXN], y[MAXN], c[MAXN], nxt[MAXN], pre[MAXN];
ll ans[MAXN];
void SuffixSort() {
	int m = lsh_num;
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
		num = x[sa[1]] = 1;
		for(int i = 2; i <= n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k]) ? num : ++num;
		m = num;
		if(num == n) break;
	}
}
void GetHeight() {
	for(int i = 1; i <= n; i++) rk[sa[i]] = i;
	for(int i = 1, k = 0; i <= n; i++) {
		if(k) k--;
		if(rk[i] == 1) {ht[rk[i]] = 0; continue;}
		int j = sa[rk[i] - 1];
		while(i+k <= n && j+k <= n && s[i+k] == s[j+k]) k++;
		ht[rk[i]] = k;
	}
}
int main() {
	n = read();
	for(int i = n; i >= 1; i--) lsh[i] = s[i] = read();
	sort(lsh + 1, lsh + 1 + n);
	lsh_num = unique(lsh + 1, lsh + 1 + n) - lsh - 1;
	for(int i = 1; i <= n; i++) s[i] = lower_bound(lsh + 1, lsh + 1 + lsh_num, s[i]) - lsh;
	SuffixSort();
	GetHeight();
	for(int i = 1; i <= n; i++) nxt[i] = i+1;
	for(int i = 1; i <= n; i++) pre[i] = i-1;
	for(int i = 1; i <= n; i++) {
		int t = rk[i];
		ans[i] = (n-i+1) - max(ht[t], ht[nxt[t]]);
		ht[nxt[t]] = min(ht[nxt[t]], ht[t]);
		nxt[pre[t]] = nxt[t];
		pre[nxt[t]] = pre[t];
	}
	for(int i = n; i >= 1; i--) ans[i] += ans[i+1];
	for(int i = n; i >= 1; i--) printf("%lld\n", ans[i]);
	return 0;
}
```

