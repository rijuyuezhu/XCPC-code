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
const int MAXN = 4e4 + 5, B = 61;
int n, q, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, fa[MAXN][17], dep[MAXN];
ll val[MAXN];
//--LinearBasis
struct Node {
	ll b[61]; int pos[61];
	void ins(ll v, int p) {
		for(int i = B-1; i >= 0; i--) 
			if((v >> i) & 1) {
				if(!b[i]) {
					b[i] = v; pos[i] = p;
					break;
				}
				if(pos[i] < p) swap(b[i], v), swap(pos[i], p);
				v ^= b[i];
			}
	}
	ll qrymax(int p) {
		ll ans = 0;
		for(int i = B-1; i >= 0; i--)
			if(b[i] && pos[i] >= p)
				ans = max(ans, ans ^ b[i]);
		return ans;
	}
}e[MAXN];
Node merge(Node x, Node y) {
	for(int i = B-1; i >= 0; i--)
		if(x.b[i]) y.ins(x.b[i], x.pos[i]);
	return y;
}
//
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void dfs(int u, int f) {
	fa[u][0] = f; dep[u] = dep[f] + 1;
	for(int k = 1; k <= 16; k++) fa[u][k] = fa[fa[u][k-1]][k-1];
	e[u] = e[f]; e[u].ins(val[u], dep[u]);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f) continue;
		dfs(v, u);
	}
}
int Lca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int k = 16; k >= 0; k--)
		if(dep[fa[u][k]] >= dep[v]) u = fa[u][k];
	if(u == v) return u;
	for(int k = 16; k >= 0; k--)
		if(fa[u][k] != fa[v][k]) u = fa[u][k], v = fa[v][k];
	return fa[u][0];
}
int main() {
	n = read(); q = read();
	for(int i = 1; i <= n; i++) val[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs(1, 0);
	for(int i = 1; i <= q; i++) {
		int u = read(), v = read(), l = Lca(u, v);
		Node t = merge(e[u], e[v]);
		printf("%lld\n", t.qrymax(dep[l]));
	}
	return 0;
}
