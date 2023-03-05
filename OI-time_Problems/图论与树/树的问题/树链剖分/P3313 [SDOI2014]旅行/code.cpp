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
	for(; ch < 'A' || ch > 'Z'; ch = getchar());
	return ch;
}
const int MAXN = 1e5 + 5;
const int MAXC = 1e5 + 5;
int n, q, w[MAXN], c[MAXN], head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], cnt, dfn[MAXN], tim, fa[MAXN], son[MAXN], sz[MAXN], dep[MAXN], top[MAXN], rt[MAXC];
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void dfs1(int u, int f) {
	dep[u] = dep[f] + 1; sz[u] = 1; fa[u] = f; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == f) continue;
		dfs1(v, u); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tp) {
	top[u] = tp; dfn[u] = ++tim; if(son[u]) dfs2(son[u], tp);
	for(int i = head[u]; i; i = nxt[i]) {
		int v = ver[i]; if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
namespace Sgt {
	const int MAXNODE = MAXN << 6;
	struct Node{
		int ls, rs, sum, mx;
		void apply(int v) {
			sum = mx = v;
		}
		void merge(const Node& a, const Node& b) {
			sum = a.sum + b.sum;
			mx = max(a.mx, b.mx);
		}
	}e[MAXNODE];
	int tot;
	
	void mdy(int& p, int l, int r, int x, int v) {
		if(!p) p = ++tot;
		if(l == r) {e[p].apply(v); return;}
		int m = (l + r) >> 1;
		if(x <= m) mdy(e[p].ls, l, m, x, v);
		else mdy(e[p].rs, m+1, r, x, v);
		e[p].merge(e[e[p].ls], e[e[p].rs]);
	}
	Node qry(int p, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[p];
		int m = (l + r) >> 1;
		if(y <= m) return qry(e[p].ls, l, m, x, y);
		else if(x > m) return qry(e[p].rs, m+1, r, x, y);
		else {
			Node ans;
			ans.merge(qry(e[p].ls, l, m, x, m), qry(e[p].rs, m+1, r, m+1, y));
			return ans;
		}
	}
}
using namespace Sgt;
int main() {
	n = read(), q = read();
	for(int i = 1; i <= n; i++) w[i] = read(), c[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1);
	for(int i = 1; i <= n; i++) mdy(rt[c[i]], 1, n, dfn[i], w[i]);
	for(int i = 1; i <= q; i++) {
		char a = readc(), b = readc();
		int x = read(), y = read();
		if(a == 'C') {
			if(b == 'C') {
				mdy(rt[c[x]], 1, n, dfn[x], 0);
				mdy(rt[c[x] = y], 1, n, dfn[x], w[x]);
			} else {
				mdy(rt[c[x]], 1, n, dfn[x], w[x] = y);
			}
		} else {
			int col = c[x];
			Node ans = (Node){0, 0, 0, 0};
			while(top[x] != top[y]) {
				if(dep[top[x]] < dep[top[y]]) swap(x, y);
				ans.merge(ans, qry(rt[col], 1, n, dfn[top[x]], dfn[x]));
				x = fa[top[x]];
			}
			if(dep[x] < dep[y]) swap(x, y);
			ans.merge(ans, qry(rt[col], 1, n, dfn[y], dfn[x]));
			if(b == 'S') printf("%d\n", ans.sum);
			else printf("%d\n", ans.mx);
		}
	}

	return 0;
}
