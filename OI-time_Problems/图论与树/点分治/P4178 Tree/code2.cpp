#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
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
const int MAXN = 4e4 + 5, INF = 0x3f3f3f3f;
int n, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, edg[MAXN << 1], k, sz[MAXN], mxsz[MAXN], tsz, rt, vis[MAXN], ans, tree, d[MAXN], dnum;
namespace Treap {
	struct Node{int ls, rs, v, s, c, k;}e[MAXN];
	int tot;
	void upd(int p) {e[p].s = e[e[p].ls].s + e[e[p].rs].s + e[p].c;}
	void lturn(int& p) {int s = e[p].rs; e[p].rs = e[s].ls; upd(p); e[s].ls = p; upd(s); p = s;}
	void rturn(int& p) {int s = e[p].ls; e[p].ls = e[s].rs; upd(p); e[s].rs = p; upd(s); p = s;}
	void ins(int& p, int v) {
		if(!p) e[p = ++tot] = (Node){0, 0, v, 1, 1, rand()};
		else if(e[p].v == v) e[p].c++, upd(p);
		else if(e[p].v > v)
			ins(e[p].ls, v), e[p].k > e[e[p].ls].k ? rturn(p) : upd(p);
		else
			ins(e[p].rs, v), e[p].k > e[e[p].rs].k ? lturn(p) : upd(p);
	}
	int le(int p, int v) {
		if(!p) return 0;
		else if(e[p].v == v) return e[e[p].ls].s + e[p].c;
		else if(e[p].v > v) return le(e[p].ls, v);
		else return e[e[p].ls].s + e[p].c + le(e[p].rs, v);
	}
}
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
void getrt(int u, int f) {
	sz[u] = 1; mxsz[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getrt(v, u); sz[u] += sz[v]; mxsz[u] = max(mxsz[u], sz[v]);
	}
	mxsz[u] = max(mxsz[u], tsz - sz[u]);
	if(mxsz[u] < mxsz[rt]) rt = u;
}
void getdis(int u, int f, int w) {
	d[++dnum] = w;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getdis(v, u, w + edg[i]);
	}
}
void calc(int u) {
	tree = Treap::tot = 0;
	Treap::ins(tree, 0);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		dnum = 0;
		getdis(v, u, edg[i]);
		for(int i = 1; i <= dnum; i++) ans += Treap::le(tree, k - d[i]);
		for(int i = 1; i <= dnum; i++) Treap::ins(tree, d[i]);
	}
}

void solve(int u) {
	vis[u] = 1; calc(u);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		tsz = sz[v]; mxsz[rt = 0] = INF;
		getrt(v, u); solve(rt);
	}
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(), w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	k = read();
	tsz = n; mxsz[rt = 0] = INF;
	getrt(1, 0); solve(rt);
	printf("%d\n", ans);
	return 0;
}
