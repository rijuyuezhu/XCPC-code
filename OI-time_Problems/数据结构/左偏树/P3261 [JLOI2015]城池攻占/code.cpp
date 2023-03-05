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
typedef pair<ll, int> pr;
#define fi first
#define se second
const int MAXN = 3e5 + 5;
int n, m, fa[MAXN], head[MAXN], ver[MAXN], nxt[MAXN], cnt, a[MAXN], rt[MAXN], c[MAXN], dep[MAXN], ans1[MAXN], ans2[MAXN];
ll h[MAXN], val[MAXN];
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
namespace LT {
	struct Node {int ls, rs, dis; pr val; ll atag, mtag;}e[MAXN];
	int tot;
	int crenode(ll v, int x) {
		e[++tot] = (Node){0, 0, 0, pr(v, x), 0, 1};
		return tot;
	}
	void psdm(int p, ll k) {
		if(p) {
			e[p].val.fi *= k;
			e[p].mtag *= k;
			e[p].atag *= k;
		}
	}
	void psda(int p, ll k) {
		if(p) {
			e[p].val.fi += k;
			e[p].atag += k;
		}
	}
	void psd(int p) {
		if(e[p].mtag != 1) {
			psdm(e[p].ls, e[p].mtag);
			psdm(e[p].rs, e[p].mtag);
			e[p].mtag = 1;
		}
		if(e[p].atag) {
			psda(e[p].ls, e[p].atag);
			psda(e[p].rs, e[p].atag);
			e[p].atag = 0;
		}
	}
	int merge(int x, int y) {
		if(!x || !y) return x + y;
		psd(x); psd(y);
		if(e[x].val > e[y].val) swap(x, y);
		e[x].rs = merge(e[x].rs, y);
		if(e[e[x].ls].dis < e[e[x].rs].dis) swap(e[x].ls, e[x].rs);
		e[x].dis = e[e[x].rs].dis + 1;
		return x;
	}
	pr top(int p) {return e[p].val;}
	int del(int p) {
		if(!p) return 0;
		psd(p);
		return merge(e[p].ls, e[p].rs);
	}
}
void dfs(int u) {
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i];
		dep[v] = dep[u] + 1;
		dfs(v);
	}
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i];
		rt[u] = LT::merge(rt[u], rt[v]);
	}
	while(rt[u]) {
		pr t = LT::top(rt[u]);
		if(t.fi < h[u]) {
			rt[u] = LT::del(rt[u]);
			ans1[u]++;
			ans2[t.se] = dep[c[t.se]] - dep[u];
		} else break;
	}
	if(u != 1) {
		if(a[u] == 0) LT::psda(rt[u], val[u]);
		else LT::psdm(rt[u], val[u]);
	}
}
int main() {
	LT::e[0].dis = -1;
	n = read(), m = read();
	for(int i = 1; i <= n; i++) h[i] = read();
	for(int i = 2; i <= n; i++) {
		fa[i] = read(); addedge(fa[i], i);
		a[i] = read(), val[i] = read();
	}
	for(int i = 1; i <= m; i++) {
		ll v = read(); c[i] = read();
		rt[c[i]] = LT::merge(rt[c[i]], LT::crenode(v, i));
	}
	dfs(1);
	while(rt[1]) {
		pr t = LT::top(rt[1]);
		rt[1] = LT::del(rt[1]);
		ans2[t.se] = dep[c[t.se]] + 1;
	}
	for(int i = 1; i <= n; i++) printf("%d\n", ans1[i]);
	for(int i = 1; i <= m; i++) printf("%d\n", ans2[i]);
	return 0;
}
