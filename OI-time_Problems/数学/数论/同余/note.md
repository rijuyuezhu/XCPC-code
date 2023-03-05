# 同余方程 学习笔记

[toc]

记录一些我另类的模板。

推荐博客：[同余方程-5天从入门到入土](https://www.luogu.com.cn/blog/ShadderLeave/5days-equiv-from-beginner-to-killer)。其中有同步洛谷题单。

## 线性同余方程（exgcd）

[P5656 【模板】二元一次不定方程 (exgcd)](https://www.luogu.com.cn/problem/P5656)

先上板子：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
ll gcd(ll a, ll b) {
    if(!b) return a;
    return gcd(b, a % b);
}
void exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= (a / b) * x;
}

int main() {
    int T = read();
    while(T--) {
        ll a = read(), b = read(), c = read(), x, y, g, xmin, ymin, xmax, ymax;
        g = gcd(a, b);
        if(c % g != 0) {
            printf("-1\n");
            continue;
        }
        a /= g, b /= g, c /= g;
        exgcd(a, b, x, y);
        x *= c; y *= c;
        xmin = (x % b + b) % b; if(xmin == 0) xmin += b;
        ymax = (c - a * xmin) / b;
        ymin = (y % a + a) % a; if(ymin == 0) ymin += a;
        xmax = (c - b * ymin) / a;
        if(ymax > 0) // has a int solution
        {
            printf("%lld %lld %lld %lld %lld\n", (ymax - ymin) / a + 1, xmin, ymin, xmax, ymax);
        } else {
            printf("%lld %lld\n", xmin, ymin);
        }
    }   
    return 0;
}
```

一、极简 gcd & exgcd

```cpp
ll gcd(ll a, ll b) {
    if(!b) return a;
    return gcd(b, a % b);
}
void exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= (a / b) * x;
}
```

二、与众不同的思路

我是这样解方程的：

方程 $ax+by=c$。

1. 想办法把 $a,b$ 都搞成正整数。这一步确保 exgcd 求解的正确性
2. 求 gcd，根据裴蜀定理判断是否有解，然后 **约分**，化成等价的方程 $a'x+b'y=c'$,其中 $\gcd(a',b')=1$。为了方便，下文仍然用 $a,b,c$ 表示。
3. 用 exgcd 求解方程 $ax+by=1$ 的特解 $x_0',y_0'$，于是方程 $ax+by=c$ 的一组特解为 $x_0=cx_0',y_0=cy_0'$
4. 则通解为 $x=x_0+bt,y=y_0-at(t\in \Z)$。

## 线性同余方程组I（CRT）

[P1495 【模板】中国剩余定理(CRT)](https://www.luogu.com.cn/problem/P1495)

求解线性同余方程组

$$\begin{cases}x\equiv r_1\pmod {m_1}\\x\equiv r_2\pmod {m_2}\\\cdots\\x\equiv r_k\pmod {m_k}\end{cases}$$

其中 $m_i$ 两两互质。

记 $M=\prod\limits_{i=1}^km_i$。$t_i$ 为 $\dfrac M{m_i}$ 在 $m_i$ 意义下的逆元。 则构造答案为 $x\equiv \sum\limits_{i=1}^k r_it_i\dfrac M{m_i} \pmod M$。

把 $x$ 带入原方程组的第 $j$ 行 ，即 $x\equiv r_j\pmod {m_j}$ 中，有：

1. 在 $x\equiv \sum\limits_{i=1}^k r_it_i\dfrac M{m_i}$ 中，若 $i\ne j$，则 $\dfrac M{m_i}$ 是 $m_j$ 的倍数，不影响。
2. 所以只需考虑 $r_it_i\dfrac M{m_i}\bmod m_i$ 的值。由于 $t_i\equiv (\dfrac M{m_i})^{-1}\pmod {m_i}$，原式就是 $r_i$。

所以

$x\equiv \sum\limits_{i=1}^k r_it_i\dfrac M{m_i} \pmod M$。

值得注意的是，这个算法常常要写 **快速乘**~~龟速乘~~

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
const int MAXN = 15;
int n;
ll a[MAXN], b[MAXN];
ll qmul(ll a, ll b, ll mod) {
	if(a < b) swap(a, b);
	ll ret = 0;
	for(; b; b >>= 1, (a += a) %= mod)
		if(b & 1) (ret += a) %= mod;
	return ret;
}
void exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll a, ll p) {
	ll x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}
ll CRT() {
	ll M = 1, ans = 0;
	for(int i = 1; i <= n; i++) M *= a[i];
	for(int i = 1; i <= n; i++) {
		ll Mi = M / a[i];
		(ans += qmul(inv(Mi, a[i]) * b[i] % M, Mi, M)) %= M;
	}
	return ans;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read(), b[i] = read();
	printf("%lld\n", CRT());
	return 0;
}
```

## 线性同余方程组II（exCRT）

[P4777 【模板】扩展中国剩余定理（EXCRT](https://www.luogu.com.cn/problem/P4777)

$$\begin{cases}x\equiv r_1\pmod {m_1}\\x\equiv r_2\pmod {m_2}\\\cdots\\x\equiv r_k\pmod {m_k}\end{cases}$$

其中 $m_i$ **不一定**两两互质。

我们考虑两个方程的 **合并** 过程。

$x\equiv r_1\pmod {m_1}$,$x\equiv r_2\pmod {m_2}$

那么可设 $x=pm_1+r_1$，则

$pm_1+r_1\equiv r_2\pmod {m_2}$

故有

$pm_1+qm_2= r_2-r_1$。

通过 exgcd求出 $p$，那么合并后的方程就为

$x\equiv R\pmod M$，其中 $R=pm_1+r_1,M=\mathrm{lcm}(m_1,m_2)$

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
const int MAXN = 1e5 + 5;
int n;
ll r[MAXN], m[MAXN], ansr, ansm;
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
void exgcd(ll a, ll b, ll& x, ll& y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll qmul(ll a, ll b, ll mod) {
	ll ret = 0;
	for(; b; b >>= 1, (a += a) %= mod)
		if(b & 1) (ret += a) %= mod;
	return ret;
}
ll calc(ll a, ll b, ll c) {
	ll g = gcd(a, b); a /= g; b /= g; c /= g;
	ll x, y; exgcd(a, b, x, y); x = qmul(x, c, b);
	return (x % b + b) % b;
}
void solve() {
	ansr = r[1], ansm = m[1];
	for(int i = 2; i <= n; i++) {
		ll k = calc(ansm, m[i], (r[i] - ansr) % m[i] + m[i]), m1 = ansm;
		ansm = m1 / gcd(m1, m[i]) * m[i];
		(ansr += qmul(k, m1, ansm)) %= ansm;
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) m[i] = read(), r[i] = read();
	solve();
	printf("%lld\n", ansr);
	return 0;
}

```

## 离散对数I（BSGS）

[P3846 [TJOI2007] 可爱的质数/【模板】BSGS](https://www.luogu.com.cn/problem/P3846)

BSGS(Baby-step Giant-step，大步小步，~~北上广深，拔山盖世~~)算法，是用来求解高次同余方程 $a^x\equiv b\pmod n,a\perp n$，或者换个写法 $x\equiv\log_ab\pmod n$，即离散对数。

**前置知识：欧拉定理：**$a^{\varphi(n)}\equiv 1\pmod n,a\perp n$.

我们根据欧拉定理，$a^x\bmod n$的值每经过 $\varphi(n)$ 就会有个循环，所以理论上我们只要看看 $x\in[1,\varphi(n)]$ 内有没有 $x$ 满足 $a^x\equiv b$。

其实也并不一定非得是 $\varphi(n)$ 吧，检验的范围再大一点也不影响结果，为了省去这个求 $\varphi(n)$ 的过程 ~~分解因数怪麻烦的~~ ，我们直接检验 $x\in [1,n-1]$ 中有没有解。这个算法的时间复杂度是 $\mathcal O(n)$ 的。	而使用BSGS算法可以优化到 $\mathcal O(\sqrt n)$。

算法采用一种分块解决的思想，这也是 “大步” “小步” 的由来。下面是算法的推导过程。

$$a^x\equiv b\pmod n$$

设置一个参数 $k$ ，把 $x$ 写成一种稍有改变的“带余除法”的形式。

$$x=pk-q(1\le p\le\lfloor \dfrac{n}{k}\rfloor+1,1\le q \le k)$$

这样 $x$ 的值域可以包含 $[0,n-1]$ 的整个区间。

于是

$$a^{pk-q}\equiv b\pmod n$$

$$a^{pk}\equiv ba^q\pmod n$$

把这个式子分成左右两部分，先枚举 $q\in[1,k]$，计算处所有的$ba^q\bmod n$，存入一个HASH表中。接下来，只要再枚举 $p\in[1,\lfloor \dfrac{n}{k}\rfloor+1]$ ，计算 $a^{pk}$，在HASH表中查找是否存在这样的 $q$ 满足上面那个等式即可。如果有多个 $q$，应选择最大的那个，这样可以使得 $x=pk-q$ 最小。

时间复杂度为 $\mathcal O(k + \lfloor \dfrac{n}{k}\rfloor)$，显然当 $k=\sqrt n$ 时有最小复杂度为 $\mathcal O(\sqrt n)$。写哈希表或者写 map 都可以，差距不大。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
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
#define ing long long
namespace HS {
	const int MAXNODE = (1 << 16) + 10;
	const int BS = 1491001;
	int nxt[MAXNODE], num[MAXNODE], val[MAXNODE], cnt, head[BS];
	int hs(int x) {
		return x % BS;
	}
	void ins(int x, int i) {
		int key = hs(x);
		num[++cnt] = x; val[cnt] = i; nxt[cnt] = head[key]; head[key] = cnt;
	}
	int qry(int x) {
		int key = hs(x);
		int mx = -1;
		for(int i = head[key]; i; i = nxt[i]) 
			if(num[i] == x) mx = max(mx, val[i]);
		return mx;
	}
}
int qpow(int a, int n, int mod) {
	int ret = 1;
	for(; n; n >>= 1, a = 1ll * a * a % mod)
		if(n & 1) ret = 1ll * ret * a % mod;
	return ret;
}
int p, b, n, m;
signed main() {
	p = read(), b = read(), n = read();
	if(b % p == 0 && n) {
		printf("no solution\n");
		return 0;
	}
	m = sqrt(p);
	for(int i = 1, k = 1ll * n * b % p; i <= m; i++, k = 1ll * k * b % p)
		HS::ins(k, i);
	for(int i = 1, bas = qpow(b, m, p), k = bas; i <= m+1; i++, k = 1ll * k * bas % p) {
		int t = HS::qry(k);
		if(t != -1) {
			printf("%lld\n", 1ll * m * i - t);
			return 0;
		}
	}
	printf("no solution\n");
	return 0;
}
```

## 离散对数 II（exBSGS）

[P4195 【模板】扩展BSGS](https://www.luogu.com.cn/problem/P4195)

