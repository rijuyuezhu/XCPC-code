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
const int MAXN = 2e5 + 5, MAXV = 1e5 + 5;
int n, m, val[MAXN], head[MAXN], ver[MAXN], nxt[MAXN], cnt, tim, st[MAXN][18], bg[MAXN], lg2[MAXN], dep[MAXN], vis[MAXN], rt, tsz, sz[MAXN], mxsz[MAXN], anc[MAXN], sgt[2][MAXN], lans;
namespace Sgt {
	const int MAXNODE = MAXN << 5;
	int tot;
	struct Node{int ls, rs, sum;}e[MAXNODE];
	void upd(int p) {e[p].sum = e[e[p].ls].sum + e[e[p].rs].sum;}
	void addpos(int& p, int l, int r, int x, int v) {
		if(!p) p = ++tot;
		if(l == r) {e[p].sum += v; return ;}
		int m = (l + r) >> 1;
		if(x <= m) addpos(e[p].ls, l, m, x, v);
		else addpos(e[p].rs, m+1, r, x, v);
		upd(p);
	}
	int qryrange(int p, int l, int r, int x, int y) {
		if(!p) return 0;
		if(x <= l && r <= y) return e[p].sum;
		int m = (l + r) >> 1;
		if(y <= m) return qryrange(e[p].ls, l, m, x, y);
		else if(x > m) return qryrange(e[p].rs, m+1, r, x, y);
		else return qryrange(e[p].ls, l, m, x, m) + qryrange(e[p].rs, m+1, r, m+1, y);
	}
}
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void dfs1(int u, int f) {
	dep[u] = dep[f] + 1; st[++tim][0] = u; bg[u] = tim;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f) continue;
		dfs1(v, u);
		st[++tim][0] = u;
	}
}
int NDmax(int u, int v) {return dep[u] < dep[v] ? u : v;}
void getst() {
	for(int k = 1; (1 << k) <= tim; k++)
		for(int i = 1; i + (1 << k) - 1 <= tim; i++)
			st[i][k] = NDmax(st[i][k-1], st[i + (1 << (k-1))][k-1]);
	lg2[0] = -1;
	for(int i = 1; i <= tim; i++) lg2[i] = lg2[i >> 1] + 1;
}
int Lca(int u, int v) {
	int a = bg[u], b = bg[v]; if(a > b) swap(a, b);
	int k = lg2[b - a + 1];
	return NDmax(st[a][k], st[b - (1 << k) + 1][k]);
}
int Dist(int u, int v) {return dep[u] + dep[v] - 2 * dep[Lca(u, v)];}
void getrt(int u, int f) {
	sz[u] = 1; mxsz[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f || vis[v]) continue;
		getrt(v, u); sz[u] += sz[v]; mxsz[u] = max(mxsz[u], sz[v]);
	}
	mxsz[u] = max(mxsz[u], tsz - sz[u]);
	if(mxsz[u] < mxsz[rt]) rt = u;
}
void divide(int u) {
	vis[u] = 1; 
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(vis[v]) continue;
		tsz = sz[v]; mxsz[rt = 0] = MAXN;
		getrt(v, 0);
		sz[rt] = sz[v]; anc[rt] = u;
		divide(rt);
	}
}
void modify(int u, int w) {
	for(int i = u; i; i = anc[i]) Sgt::addpos(sgt[0][i], 0, sz[i], Dist(i, u), w);
	for(int i = u; anc[i]; i = anc[i]) Sgt::addpos(sgt[1][i], 0, sz[anc[i]], Dist(anc[i], u), w);
}
int query(int u, int k) {
	int ans = 0;
	ans += Sgt::qryrange(sgt[0][u], 0, sz[u], 0, min(sz[u], k));
	for(int i = u; anc[i]; i = anc[i]) {
		int d = Dist(anc[i], u);
		if(k >= d) ans += Sgt::qryrange(sgt[0][anc[i]], 0, sz[anc[i]], 0, min(k - d, sz[anc[i]]))
						- Sgt::qryrange(sgt[1][i], 0, sz[anc[i]], 0, min(k - d, sz[anc[i]]));
	}
	return ans;
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) val[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs1(1, 0); getst();
	tsz = n; mxsz[rt = 0] = MAXN;
	getrt(1, 0);
	sz[rt] = sz[1]; divide(rt);
	for(int i = 1; i <= n; i++) modify(i, val[i]);
	lans = 0;
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read() ^ lans, y = read() ^ lans;
		if(opt == 0) {
			printf("%d\n", lans = query(x, y));
		} else {
			modify(x, y - val[x]); val[x] = y;
		}
	}
	return 0;
}
