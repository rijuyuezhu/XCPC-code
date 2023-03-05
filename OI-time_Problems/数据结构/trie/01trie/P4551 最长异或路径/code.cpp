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
const int MAXN = 1e5 + 5;
int n, head[MAXN], ver[MAXN << 1], nxt[MAXN << 1], edg[MAXN << 1], dist[MAXN << 1], cnt;
namespace Trie {
	const int MAXNODE = MAXN * 32;
	struct Node {int ch[2], fl;}e[MAXNODE];
	int tot = 1;
	void ins(int x) {
		int p = 1;
		for(int i = 31; i >= 0; i--) {
			int v = (x >> i) & 1;
			if(!e[p].ch[v]) e[p].ch[v] = ++tot;
			p = e[p].ch[v];
		}
		e[p].fl = 1;
	}
	int qry(int x) {
		int p = 1, ans = 0;
		for(int i = 31; i >= 0; i--) {
			int v = (x >> i) & 1;
			if(e[p].ch[v^1]) ans += (1 << i), p = e[p].ch[v^1];
			else p = e[p].ch[v];
		}
		return ans;
	}
}
using namespace Trie;
void addedge(int u, int v, int w) {
	ver[++cnt] = v; nxt[cnt] = head[u]; edg[cnt] = w; head[u] = cnt;
}
void dfs(int u, int f) {
	for(int i = head[u]; i; i = nxt[i]) if(ver[i] != f) {
		int v = ver[i];
		dist[v] = dist[u] ^ edg[i];
		dfs(v, u);
	}
}
int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(),  w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++) ins(dist[i]);
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = max(ans, qry(dist[i]));
	printf("%d\n", ans);
	return 0;
}
