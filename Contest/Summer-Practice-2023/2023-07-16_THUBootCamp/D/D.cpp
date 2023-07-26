#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e5 + 5;
constexpr int B = 17;
constexpr ll LINF = 1e18;

int n, p[MAXN], fa[B][MAXN];
ll T, a[MAXN], t[MAXN], dist[B][MAXN], d[MAXN];

struct Edge {
	int v, nxt;
	ll w;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v, ll w) {
	e[++cnt] = {v, head[u], w};
	head[u] = cnt;
}

void dfs1(int u) {
	for (int i = 1; i < B; i++) {
		fa[i][u] = fa[i-1][fa[i-1][u]];
		dist[i][u] = dist[i-1][u] + dist[i-1][fa[i-1][u]];
	}
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		fa[0][v] = u; dist[0][v] = e[i].w;
		dfs1(v);
	}
}
void dfs2(int u) {
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		dfs2(v);
		d[u] += d[v];
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> T;
	for (int i = 2; i <= n; i++)
		cin >> p[i];
	for (int i = 2; i <= n; i++) {
		cin >> t[i];
		addedge(p[i], i, t[i]);
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i]++;
	}
	for (int i = 0; i < B; i++)
		dist[i][0] = fa[i][0] = 0;
	dist[0][1] = LINF, fa[0][1] = 0;
	dfs1(1);
	for (int u = 1; u <= n; u++) {
		ll res = T;
		int v = u;
		for (int i = B-1; i >= 0; i--)
			if (res >= dist[i][v]) {
				res -= dist[i][v];
				v = fa[i][v];
			}
		d[u] += a[u];
		d[p[v]] -= a[u];
	}
	dfs2(1);
	int ans = 1;
	for (int i = 2; i <= n; i++)
		if (d[i] > d[ans])
			ans = i;
	cout << ans << ' ' << d[ans] << endl;
	return 0;
}
