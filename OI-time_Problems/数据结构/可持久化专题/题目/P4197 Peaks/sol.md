# P4197 Peaks 解题报告

[P4197 Peaks](https://www.luogu.com.cn/problem/P4197)

## 解题报告

看到“只经过困难值小于等于 $x$ 的路径”这样一句话，我们就知道了这题应该是考察 Kruskal重构树+树上倍增。

于是建出Kruskal重构树，每次询问就可以确定可以到达的点在哪个Kruskal重构树节点的子树里。预先跑一个dfs，赋予叶子节点时间戳，使得任意一个子树中的所有叶子节点时间戳连续。然后就可以建立主席树，接下来是经典做法了。

还有另一个做法是离线后set启发式合并，也可以通过本题。

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
const int MAXM = 1e6 + 5;
int upto[MAXN], n, m, q, num, h[MAXN], lsh[MAXN], lsh_num, head[MAXN], ver[MAXN], nxt[MAXN], cnt, fa[MAXN][21], val[MAXN], dfn[MAXN], bel[MAXN], tim, st[MAXN], sz[MAXN], sgt[MAXN];
struct Ed {int u, v, w;}ed[MAXM];
bool operator < (const Ed& A, const Ed& B) {return A.w < B.w;}

void LSH() {
	sort(lsh + 1, lsh + 1 + lsh_num);
	lsh_num = unique(lsh + 1, lsh + 1 + lsh_num) - lsh - 1;
}
int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + lsh_num, x) - lsh;
}
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
namespace Sgt {
	struct Node {int ls, rs, sz;}e[MAXN << 5];
	int tot;
	void mdy(int& p, int pre, int l, int r, int x) {
		p = ++tot; e[p] = e[pre]; e[p].sz++;
		if(l == r) return;
		int m = (l + r) >> 1;
		if(x <= m) mdy(e[p].ls, e[pre].ls, l, m, x);
		else mdy(e[p].rs, e[pre].rs, m+1, r, x);
	}
	int calc(int u, int v) {return e[v].sz - e[u].sz;}
	int qry(int u, int v, int l, int r, int k) {
		if(k > calc(u, v)) return -1;
		if(l == r) return lsh[l];
		int m = (l + r) >> 1;
		if(k <= calc(e[u].rs, e[v].rs)) return qry(e[u].rs, e[v].rs, m+1, r, k);
		else return qry(e[u].ls, e[v].ls, l, m, k - calc(e[u].rs, e[v].rs));
	}

}
void kruskal() {
	sort(ed + 1, ed + 1 + m);
	num = n;
	for(int i = 1; i <= m; i++) {
		int u = ed[i].u, v = ed[i].v;
		if(getup(u) == getup(v)) continue;
		num++; val[num] = ed[i].w;
		addedge(num, getup(u)), addedge(num, getup(v));
		fa[getup(u)][0] = num; fa[getup(v)][0] = num;
		upto[getup(u)] = upto[getup(v)] = upto[num] = num;
	}
	for(int i = 1; i <= 20; i++)
		for(int u = 1; u <= num; u++)
			fa[u][i] = fa[fa[u][i-1]][i-1];
}
void dfs(int u) {
	st[u] = tim + 1;
	if(u <= n) dfn[u] = ++tim, bel[tim] = u, sz[u] = 1;
	else sz[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		dfs(ver[i]); sz[u] += sz[ver[i]];
	}
}

int main() {
	n = read(); m = read(); q = read();
	for(int i = 1; i <= n; i++) lsh[++lsh_num] = h[i] = read(), upto[i] = i;
	LSH();
	for(int i = 1; i <= m; i++) ed[i].u = read(), ed[i].v = read(), ed[i].w = read();
	kruskal();
	for(int i = 1; i <= n; i++) if(!dfn[i]) dfs(getup(i));
	for(int i = 1; i <= n; i++) Sgt::mdy(sgt[i], sgt[i-1], 1, lsh_num, LSH(h[bel[i]]));
	while(q--) {
		int u = read(), x = read(), k = read();
		for(int i = 20; i >= 0; i--)
			if(fa[u][i] && val[fa[u][i]] <= x) u = fa[u][i];
		printf("%d\n", Sgt::qry(sgt[st[u] - 1], sgt[st[u] + sz[u] - 1], 1, lsh_num, k));
	}
	return 0;
}
```

