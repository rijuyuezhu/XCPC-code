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
	for(; ch != 'Q' && ch != 'L'; ch = getchar());
	return ch;
}
const int MAXN = 8e4 + 5;
int n, m, t, val[MAXN], lsh[MAXN], lsh_num, fa[MAXN][20], dep[MAXN], sz[MAXN], upto[MAXN], rt[MAXN];
int head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, lans;
namespace Sgt {
	const int MAXNODE = 2e7;
	struct Node{int ls, rs, sz;}e[MAXNODE];
	int tot;
	void mdy(int& p, int pre, int l, int r, int x) {
		p = ++tot; e[p] = e[pre]; e[p].sz++;
		if(l == r) return ;
		int m = (l + r) >> 1;
		if(x <= m) mdy(e[p].ls, e[pre].ls, l, m, x);
		else mdy(e[p].rs, e[pre].rs, m+1, r, x);
	}
	int calc(int a, int b, int c, int d) {return e[a].sz + e[b].sz - e[c].sz - e[d].sz;}
	int qry(int a, int b, int c, int d, int l, int r, int k) {
		if(l == r) return lsh[l];
		int t = calc(e[a].ls, e[b].ls, e[c].ls, e[d].ls), m = (l + r) >> 1;
		if(k <= t) return qry(e[a].ls, e[b].ls, e[c].ls, e[d].ls, l, m, k);
		else return qry(e[a].rs, e[b].rs, e[c].rs, e[d].rs, m+1, r, k - t);
	}
}
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
void LSH() {
	sort(lsh + 1, lsh + 1 + lsh_num);
	lsh_num = unique(lsh + 1, lsh + 1 + lsh_num) - lsh - 1;
}
int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + lsh_num, x) - lsh;
}
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
int Lca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = 19; i >= 0; i--)
		if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if(u == v) return u;
	for(int i = 19; i >= 0; i--)
		if(fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
void dfs(int u, int f) {
	fa[u][0] = f; dep[u] = dep[f] + 1; Sgt::mdy(rt[u], rt[f], 1, lsh_num, val[u]);
	for(int i = 1; i <= 19; i++) 
		fa[u][i] = fa[fa[u][i-1]][i-1];
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f) continue;
		dfs(v, u);
	}
}
void merge(int x, int y) {
	if(sz[getup(x)] > sz[getup(y)]) swap(x, y); // x -> y
	sz[getup(y)] += sz[getup(x)]; upto[getup(x)] = getup(y);
	addedge(x, y); addedge(y, x);
	dfs(x, y);
}
int main() {
	read();
	n = read(); m = read(); t = read();	
	for(int i = 1; i <= n; i++) lsh[++lsh_num] = val[i] = read();
	LSH();
	for(int i = 1; i <= n; i++) {
		val[i] = LSH(val[i]);
		upto[i] = i; sz[i] = 1;
		dfs(i, 0);
	}
	for(int i = 1; i <= m; i++) {
		int x = read(), y = read();
		merge(x, y);
	}
	for(int i = 1; i <= t; i++) {
		char ch = readc();
		if(ch == 'Q') {
			int x = read() ^ lans, y = read() ^ lans, k = read() ^ lans, lca = Lca(x, y);
			printf("%d\n", lans = Sgt::qry(rt[x], rt[y], rt[lca], rt[fa[lca][0]], 1, lsh_num, k));
		} else {
			int x = read() ^ lans, y = read() ^ lans;
			merge(x, y);
		}
	}
	return 0;
}
