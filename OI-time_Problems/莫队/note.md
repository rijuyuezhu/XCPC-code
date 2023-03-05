# 莫队 学习笔记

资料：
1. lxl的ppt。
2. 洛谷题单：
   
   [莫队大全](https://www.luogu.com.cn/training/1590#information)

## 基础莫队

例题：[P1494 [国家集训队]小Z的袜子](https://www.luogu.com.cn/problem/P1494)

> 给定序列$a_i(1\le i\le n)$，每次询问给定区间 $[l,r]$，求满足 $l\le i\le j\le r, i\ne j$ 且 $a_i=a_j$ 的数的个数。

有这样一种思路：在询问之间迁移。比如，上一次询问是 $[l_0,r_0]$，本次询问是 $[l,r]$，那么我们只需把 $l_0$ 移至 $l$，$r_0$ 移至 $r$ 即可。一步一步挪动左右端点。每次挪动，会加入一个数或删去一个数，那么这个操作对答案的贡献容易得到。如果我们每次询问都这样挪动，时间复杂度最坏是 $O(nm)$ 的，无法接受。

考虑优化。将询问**分块**，比如说，把左端点每 $B$ 个分为一组，组内从左到右排序，然后按组的顺序进行询问间的迁移。于是得到以下代码：

```cpp
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 50005;
int n, m;
int c[MAXN];
int bsz, b[MAXN];
ll f[MAXN], g[MAXN];
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
struct Qry {
    int id, l, r;
    bool operator < (const Qry& B)const {
        if(b[l] != b[B.l]) return b[l] < b[B.l];
        return r < B.r;
    }
}q[MAXN];
int cnt[MAXN];
int main() {
    n = read(), m = read();
    bsz = n / sqrt(m);
    for(int i = 1; i <= n; i++) {
        c[i] = read();
        b[i] = (i - 1) / bsz;
    }
    for(int i = 1; i <= m; i++) {
        q[i].l = read(), q[i].r = read(); q[i].id = i;
        int len = q[i].r - q[i].l + 1;
        g[i] = 1ll * len * (len-1) / 2;
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0, ans = 0;
    for(int i = 1; i <= m; i++) {
        while(q[i].l < l) ans += cnt[c[--l]]++;
        while(q[i].r > r) ans += cnt[c[++r]]++;
        while(q[i].l > l) ans -= --cnt[c[l++]];
        while(q[i].r < r) ans -= --cnt[c[r--]];
        f[q[i].id] = ans;
    }
    for(int i = 1; i <= m; i++) {
        ll k = gcd(f[i], g[i]);
        if(!k) {
            printf("0/1\n");
        } else {
            printf("%lld/%lld\n", f[i] / k, g[i] / k);
        }
    }
    return 0;
}
```

简单分析一下复杂度和此处 $B=\dfrac{n}{\sqrt m}$ 的来源：

对于左端点在组之间的转移，复杂度为 $O(n)$；对于左端点在组之内的转移，总共复杂度不超过 $O(mB)$。而每组中右端点需要往右扫一遍，总共复杂度为 $O(\dfrac {n^2} B)$

所以最终的复杂度为 $O(n+mB+\dfrac{n^2} B)$，取 $B=\dfrac{n}{\sqrt m}$ 有最优复杂度为 $O(n\sqrt m)$。

**Tip:**
注意常数优化，主要有以下几点：
   1. 加快读。
   2. 可以考虑分类讨论块编号进行转移：就类似于，第一个块右端点从左到右，第二个块右端点从右到左，...，刚好形成一个蛇形。
   
加上优化后，代码如下：
```cpp
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 50005;
int n, m;
int c[MAXN];
int bsz, b[MAXN];
ll f[MAXN], g[MAXN];
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
struct Qry {
    int id, l, r;
    bool operator < (const Qry& B)const {
        if(b[l] != b[B.l]) return b[l] < b[B.l];
        if(b[l] & 1) return r < B.r;
        else return r > B.r;
    }
}q[MAXN];
int cnt[MAXN];
int main() {
    n = read(), m = read();
    bsz = n / sqrt(m);
    for(int i = 1; i <= n; i++) {
        c[i] = read();
        b[i] = (i - 1) / bsz;
    }
    for(int i = 1; i <= m; i++) {
        q[i].l = read(), q[i].r = read(); q[i].id = i;
        int len = q[i].r - q[i].l + 1;
        g[i] = 1ll * len * (len-1) / 2;
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0, ans = 0;
    for(int i = 1; i <= m; i++) {
        while(q[i].l < l) ans += cnt[c[--l]]++;
        while(q[i].r > r) ans += cnt[c[++r]]++;
        while(q[i].l > l) ans -= --cnt[c[l++]];
        while(q[i].r < r) ans -= --cnt[c[r--]];
        f[q[i].id] = ans;
    }
    for(int i = 1; i <= m; i++) {
        ll k = gcd(f[i], g[i]);
        if(!k) {
            printf("0/1\n");
        } else {
            printf("%lld/%lld\n", f[i] / k, g[i] / k);
        }
    }
    return 0;
}
```

## 带修莫队/三维莫队

例题：[P1903 [国家集训队]数颜色 / 维护队列](https://www.luogu.com.cn/problem/P1903)

询问区间 $[l,r]$ 中的不同的颜色数量，带单点修。

带修莫队本质上就是三维莫队（多了一个时间轴）。每个询问抽象成三元组 $(l,r,t)$ 表示在 $t$ 时刻的询问 $[l,r]$。那么我们有三个方向的迁移：
- 左端点的迁移；
- 右端点的迁移；
- 时间的迁移。

稍加思考，可以 $O(1)$ 完成一次迁移。

仍然考虑莫队思想，先将 $l$ 分块（块长为 $a$），再将 $r$ 分块（块长为 $b$），最后 $l,r$ 块都相同的询问按照 $t$ 顺序排序。

考虑这样做的时间复杂度：

1. $l$ 端点块间移动 $O(n)$，块内移动 $O(am)$。
2. $r$ 端点：
   1. 当 $l$ 块不同时（最多 $O(\dfrac{n}{a})$ 个这样的情况），每次迁移需要花费 $O(n)$ 时间，最坏总复杂度 $O(\dfrac{n^2}{a})$。
   2. 当 $l$ 块相同时，需要从左到右扫一遍 $r$，最坏复杂度 $O(\dfrac{n^2}{a})$。
3. $t$ 端点：
   1. 当 $l,r$ 块都不相同时（最多 $O(\dfrac{n^2}{ab})$ 个这样的情况，每次迁移 $O(t)$，最坏总复杂度 $O(\dfrac{n^2T}{ab})$。
   2. 当 $l,r$ 块都相同时，只需要从左到右扫一遍 $t$，最坏复杂度 $O(\dfrac{n^2T}{ab})$。

所以最后的复杂度为 $O(n+am+\dfrac{n^2}{a}+\dfrac{n^2T}{ab})$。

第一项显然可以忽略。