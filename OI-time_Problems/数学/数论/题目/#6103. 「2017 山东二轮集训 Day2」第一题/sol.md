# LOJ#6103. 「2017 山东二轮集训 Day2」第一题 解题报告

前置知识：闭区间上的连续函数的零点存在性定理：

我们定义这样的函数：

定义域为 $[l,r]\cap \mathbb Z$ 对于 $\forall x \in [l,r-1]\cap \mathbb Z$，有 $|f(x+1)-f(x)|\le 1$，则称它为定义在闭区间 $[l,r]$ 上的整数连续函数。（我自己瞎定义的）。那么在这上面，零点存在性定理仍适用。

而 $\mu$ 的前缀和函数显然是这样的函数，于是可以使用这个定理，直接二分即可。

那么关键在于要求 $[1,N]$ 范围内 $M(n)=\sum_{i=1}^n\mu(i)$ 的最值。其中 $N=10^5,10^7,10^9$。

对于 $N=10^5,10^7$ 的点，直接写个线性筛 $\mu$，再线性扫一遍即可。可以求得：

当 $N=10^5$ 时，最大值点 $n_1=48433$，最小值点 $n_2=96014$；

当 $N=10^7$ 时，最大值点 $n_1=9993034$，最小值点 $n_2=7109110$。

而 $N=10^9$ 则比较困难，反正我家内存开不下 $10^9$ 大小的数组）我采取的策略是分段，每次打 $2\times 10^8$ 的表，用区间筛，就可以分五次搞出来。

最后得到的答案：最大值点 $n_1=903087703$，最小值点 $n_2=456877618$。

这里给出最后一次扫 $(8\times 10^8+1)\sim 10^9$ 时的程序：

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
const int BAS = 8e8;
const ll PRES = 1130;
const int N = 2e8, SQN = 4e4;
int mu[N+5], lst[N+5], pr[SQN+5], ip[SQN+5], tot;
void sieve(int n) {
	ip[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
		}
		for(int j = 1; j <= tot && pr[j] <= n / i; j++) {
			int k = i * pr[j];
			ip[k] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
int main() {
	sieve(SQN);
	for(int i = 1; i <= N; i++)	mu[i] = 1, lst[i] = BAS + i;
	for(int j = 1; j <= tot; j++)
		for(int i = pr[j] * (BAS / pr[j] + 1); i <= BAS + N; i += pr[j]) {
			mu[i-BAS] *= -1; lst[i-BAS] /= pr[j];
			if(lst[i-BAS] % pr[j] == 0)
				mu[i-BAS] = 0;
		}
	for(int i = 1; i <= N; i++) if(lst[i] > 1) mu[i] *= -1;
	ll sum = PRES; int mx = -1, mn = -1; ll mxv = -1, mnv = -1;
	for(int i = 1; i <= N; i++) {
		sum += mu[i];
		if(mx == -1 || sum > mxv) mx = BAS+i, mxv = sum;
		if(mn == -1 || sum < mnv) mn = BAS+i, mnv = sum;
	}
	printf("mx = %d, mxv = %lld\nmn = %d, mnv = %lld\nsum=%lld\n", mx, mxv, mn, mnv, sum);
	return 0;
}
```

于是最后只需要一个写一个杜教筛即可，时间复杂度 $O(n^{2/3}\log n)$。（似乎这个 $\log n$ 可以放到指数下面去？不懂）

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
const int MAXN = 1e6 + 5, N = 1e6;

int n, v, mu[MAXN], pr[MAXN], ip[MAXN], tot;
void sieve(int n) {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && pr[j] <= n / i; j++) {
			int k = i * pr[j];
			ip[k] = 1;
			if(i % pr[j]) mu[k] = -mu[i];
			else {
				mu[k] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) mu[i] += mu[i-1];
}
map<int, int> Smu;
int Calcsmu(int x) {
	if(x <= N) return mu[x];
	map<int, int>::iterator p = Smu.find(x);
	if(p != Smu.end()) return p->second;
	int ret = 1;
	for(int i = 2, j; i <= x; i = j + 1) {
		int t = x / i; j = x / t;
		ret -= (j - i + 1) * Calcsmu(t);
	}
	return Smu[x] = ret;
}
int main() {
	sieve(N);
	n = read(), v = read();
	int l, r;
	if(n == 100000) l = 48433, r = 96014;
	else if(n == 10000000) l = 7109110, r = 9993034;
	else l = 456877618, r = 903087703;
	int L = Calcsmu(l), R = Calcsmu(r);
	if(v > max(L, R) || v < min(L, R)) {
		printf("-1\n");
		return 0;
	}
	while(l <= r) {
		int m = (l + r) >> 1, M = Calcsmu(m);
		if(M == v) {printf("%d\n", m); return 0;}
		if(L <= R) {
			if(v < M) r = m, R = M;
			else l = m, L = M;
		} else {
			if(v < M) l = m, L = M;
			else r = m, R = M;
		}
	}
	return 0;
}
```