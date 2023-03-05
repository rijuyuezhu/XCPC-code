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
char readc() {
	char ch = getchar();
	for(; ch < 'a' || ch > 'z'; ch = getchar());
	return ch;
}
const int MAXN = 6e5 + 5, MAXM = 1e6 + 5, P = 612321329;
int pls(int a, int b) {a += b; return a >= P ? a - P : a;}
int mns(int a, int b) {a -= b; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, m, head[MAXN], ver[MAXN], nxt[MAXN], cnt, st[MAXN][20], _st, dep[MAXN], pos[MAXN], lg2[MAXN], dfn[MAXN], tim, top[MAXN], son[MAXN], U[MAXN], D[MAXN], h[MAXN], fa[MAXN][20];
char ch[MAXN];
struct hsint {
	int a, b;
	hsint(int a = 0, int b = 0) :a(a), b(b) {}
};
const hsint B = hsint(21313, 3137), invB = hsint(488380344, 475100451);
hsint operator + (const hsint& x, const hsint& y) {return hsint(pls(x.a, y.a), pls(x.b, y.b));}
hsint operator - (const hsint& x, const hsint& y) {return hsint(mns(x.a, y.a), mns(x.b, y.b));}
hsint operator * (const hsint& x, const hsint& y) {return hsint(mul(x.a, y.a), mul(x.b, y.b));}
bool operator == (const hsint& x, const hsint& y) {return x.a == y.a && x.b == y.b;}
hsint pre[MAXN], suf[MAXN], powB[MAXN], powinvB[MAXN];


void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
namespace LCA {
	void dfs1(int u, int f) {
		st[++_st][0] = u; pos[u] = _st;
		dep[u] = dep[f] + 1;
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i]; if(v == f) continue;
			dfs1(v, u); st[++_st][0] = u;
		}
	}
	int better(int u, int v) {return dep[u] < dep[v] ? u : v;}
	void init_st() {
		for(int k = 1; (1 << k) <= _st; k++)
			for(int i = 1; i + (1 << k) - 1 <= _st; i++)
				st[i][k] = better(st[i][k-1], st[i + (1 << (k-1))][k-1]);
		lg2[0] = -1; for(int i = 1; i <= _st; i++) lg2[i] = lg2[i >> 1] + 1;
	}
	int Lca(int u, int v) {
		u = pos[u], v = pos[v]; if(u > v) swap(u, v);
		int k = lg2[v - u + 1];
		return better(st[u][k], st[v - (1 << k) + 1][k]);
	}
	int Dist(int u, int v) {return dep[u] + dep[v] - 2 * dep[Lca(u, v)];}
	void init_LCA() {
		dfs1(1, 0);
		init_st();
	}
}
using namespace LCA;
namespace KTH {
	void dfs2(int u, int f) {
		fa[u][0] = f; h[u] = 1;
		for(int k = 1; k <= 19; k++) fa[u][k] = fa[fa[u][k-1]][k-1];
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i]; if(v == f) continue;
			dfs2(v, u); h[u] = max(h[u], h[v] + 1);
			if(h[v] > h[son[u]]) son[u] = v;
		}
	}
	void dfs3(int u, int tp, int up) {
		dfn[u] = ++tim; U[tim] = up; D[tim] = u; top[u] = tp;
		if(son[u]) dfs3(son[u], tp, fa[up][0]);
		for(int i = head[u]; i; i = nxt[i]) {
			int v = ver[i]; if(v == fa[u][0] || v == son[u]) continue;
			dfs3(v, v, v);
		}
	}
	int Kth(int u, int k) {
		if(!k) return u;
		u = fa[u][lg2[k]]; k -= (1 << lg2[k]);
		k -= dep[u] - dep[top[u]]; u = top[u];
		if(k >= 0) return U[dfn[u] + k];
		else return D[dfn[u] - k];
	}
	void init_Kth() {
		dfs2(1, 0); 
		dfs3(1, 1, 1);
	}
}
using namespace KTH;
hsint pre_get(int u, int v) {//dep[u] < dep[v]
	return pre[v] - pre[fa[u][0]] * powB[dep[v] - dep[u] + 1];
}
hsint suf_get(int u, int v) {//dep[u] > dep[v]
	return (suf[u] - suf[fa[v][0]]) * powinvB[dep[v] - 1];
}
hsint geths(int u, int v, int len) {
	int p = Lca(u, v);
	if(len == 0) return 0;
	else if(len <= dep[u] - dep[p] + 1) {
		return suf_get(u, Kth(u, len-1));	
	} else {
		hsint p1 = dep[u] - dep[p] - 1 >= 0 ? suf_get(u, Kth(u, dep[u] - dep[p] - 1)) : 0;
		int lst = len - (dep[u] - dep[p]), k = dep[v] - dep[p] + 1;
		hsint p2 = pre_get(p, Kth(v, k - lst));
		return p1 * powB[lst] + p2;
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) ch[i] = readc();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	init_LCA();
	init_Kth();
	powB[0] = powinvB[0] = hsint(1, 1);
	for(int i = 1; i <= n; i++) {
		powB[i] = powB[i-1] * B;
		powinvB[i] = powinvB[i-1] * invB;
	}
	for(int i = 1; i <= n; i++) {
		int u = D[i], f = fa[u][0];
		pre[u] = pre[f] * B + hsint(ch[u], ch[u]);
		suf[u] = suf[f] + hsint(ch[u], ch[u]) * powB[dep[u] - 1];
	}
	for(int te = read(); te; te--) {
		int a = read(), b = read(), c = read(), d = read();
		int l = 0, r = min(Dist(a, b) + 1, Dist(c, d) + 1), ans = -1;
		while(l <= r) {
			int m = (l + r) >> 1;
			if(geths(a, b, m) == geths(c, d, m)) ans = m, l = m + 1;
			else r = m - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
