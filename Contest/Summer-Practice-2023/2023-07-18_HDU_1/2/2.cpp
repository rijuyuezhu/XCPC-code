#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int MAXN = 4e5 + 5;
constexpr ll LINF = 1e18;
int n;
ll a[MAXN];
struct Edge {
	int v, nxt;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {
	e[++cnt] = {v, head[u]};
	head[u] = cnt;
}
void clear() {
	cnt = 0;
	for (int i = 1; i <= n; i++)
		head[i] = 0;
}
ll f[MAXN], g[MAXN], h[MAXN];
void dfs(int u, int fa) {
	f[u] = h[u] = g[u] = 0;
	int isleaf = 1;
	ll gmf = LINF;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (v == fa)
			continue;
		dfs(v, u);
		isleaf = 0;
		f[u] += min(f[v], g[v]);
		gmf = min(gmf, g[v] - f[v]);
		g[u] += min(min(g[v], f[v]), h[v]);
		h[u] += min(f[v], g[v]);
	}
	if (isleaf) {
		f[u] = LINF;
		g[u] = a[u];
		h[u] = 0;
	} else {
		if (gmf > 0)
			f[u] += gmf;
		g[u] += a[u];
	}
}
void work() {
	cin >> n;
	clear();
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
	}
	dfs(1, 0);
	cout << min(f[1], g[1]) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
