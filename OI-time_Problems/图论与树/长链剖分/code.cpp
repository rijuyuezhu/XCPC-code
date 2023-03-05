#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned int uint;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e5 + 5;
int n, q, fa[20][MAXN], head[MAXN], ver[MAXN], nxt[MAXN], cnt, rt, son[MAXN], h[MAXN], dep[MAXN], top[MAXN], U[MAXN], D[MAXN], dfn[MAXN], tim, lg2[MAXN];
uint s;
ll ans, lans;
uint get(uint x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x;
}
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void dfs1(int u) {
	for(int k = 1; k <= 19; k++) fa[k][u] = fa[k-1][fa[k-1][u]];
	dep[u] = dep[fa[0][u]] + 1; h[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i];
		dfs1(v);
		h[u] = max(h[u], h[v] + 1);
		if(h[v] > h[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp, int up) {
	dfn[u] = ++tim; top[u] = tp;
	U[tim] = up; D[tim] = u;
	if(son[u]) dfs2(son[u], tp, fa[0][up]);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == son[u]) continue;
		dfs2(v, v, v);
	}
}
int kth(int u, int k) {
	if(!k) return u;
	u = fa[lg2[k]][u]; k -= (1 << lg2[k]);
	k -= dep[u] - dep[top[u]]; u = top[u];
	if(k >= 0) return U[dfn[u] + k];
	else return D[dfn[u] - k];
}
int main() {
	n = read(); q = read(); s = read();
	for(int i = 1; i <= n; i++) {
		fa[0][i] = read();
		if(fa[0][i]) addedge(fa[0][i], i);
		else rt = i;
	}
	dfs1(rt); dfs2(rt, rt, rt);
	lg2[0] = -1;
	for(int i = 1; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
	for(int i = 1; i <= q; i++) {
		int x = (get(s) ^ lans) % n + 1, k = (get(s) ^ lans) % dep[x];
		lans = kth(x, k);
		ans ^= i * lans;
	}
	printf("%lld\n", ans);
	return 0;
}
