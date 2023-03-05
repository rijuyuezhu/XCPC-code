#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
/*char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)*/
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5;
int n, m, a[MAXN], head[MAXN], cnt, ver[MAXN << 1], nxt[MAXN << 1];
int dep[MAXN], sz[MAXN], fa[MAXN], top[MAXN], son[MAXN], rt[MAXN];
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}


namespace Trie {
	const int MAXNODE = MAXN * 50;
	struct Node {int ch[2], sz;}e[MAXNODE];
	int tot;
	void ins(int& p, int pre, int x, int t) {
		p = ++tot; e[p] = e[pre];
		if(t == -1) {
			e[p].sz++;
			return ;
		}
		int v = (x >> t) & 1;
		e[p].sz++;
		ins(e[p].ch[v], e[pre].ch[v], x, t-1);
	}
	int qry(int a, int b, int x, int t) {
		if(t == -1) return 0;
		int v = (x >> t) & 1;
		if(e[e[b].ch[v^1]].sz - e[e[a].ch[v^1]].sz > 0) return (1 << t) + qry(e[a].ch[v^1], e[b].ch[v^1], x, t-1);
		else if(e[e[b].ch[v]].sz - e[e[a].ch[v]].sz > 0) return qry(e[a].ch[v], e[b].ch[v], x, t-1);
		else return 0;
	}
}
void dfs1(int u, int f) {
	dep[u] = dep[f] + 1; fa[u] = f; Trie::ins(rt[u], rt[f], a[u], 16); sz[u] = 1; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i]; dfs1(v, u); sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tprt) {
	top[u] = tprt; if(son[u]) dfs2(son[u], tprt);
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != fa[u] && ver[i] != son[u]) {
		int v = ver[i]; dfs2(v, v);
	}
}


int Lca(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}

void clear() {
	memset(head, 0x00, sizeof head); cnt = 0;
	Trie::tot = 0;
	memset(Trie::e, 0x00, sizeof Trie::e);
}
void work() {
	clear();	
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v); addedge(v, u);
	}
	dfs1(1, 0); dfs2(1, 1); 
	for(int i = 1; i <= m; i++) {
		int x = read(), y = read(), z = read();
		int t = fa[Lca(x, y)];
		printf("%d\n", max(Trie::qry(rt[t], rt[x], z, 16), Trie::qry(rt[t], rt[y], z, 16)));
	}

}
int main() {
	while(scanf("%d%d", &n, &m) != EOF) work();
	return 0;
}
