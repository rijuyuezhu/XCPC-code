#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;
using pr = pair<ll, int>;
constexpr int MAXN = 2005;
constexpr int MAXM = 5005;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = 1e18;
int n, m;
ll c;
struct Edge {
	int v, nxt, w;
}e[MAXM];
int cnt, head[MAXN];

void addedge(int u, int v, int w) {
	e[++cnt] = {v, head[u], w};
	head[u] = cnt;
}

ll dist[MAXN][MAXN];
int vis[MAXN];

void SSSP(int s) {
	priority_queue<pr, vector<pr>, greater<pr> > pq;
	for (int i = 1; i <= n; i++) {
		dist[s][i] = LINF;
		vis[i] = 0;
	}
	dist[s][s] = 0;
	pq.push(pr(0, s));
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v, w = e[i].w;
			if (dist[s][v] > dist[s][u] + w) {
				dist[s][v] = dist[s][u] + w;
				pq.push(pr(dist[s][v], v));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> c;
	int mnw = INF;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		addedge(u, v, w);
		mnw = min(mnw, w);
	}
	if (mnw > c) {
		cout << 0 << '\n';
		return 0;
	}
	for (int i = 1; i <= n; i++)
		SSSP(i);
	ll ret = LINF;
	for (int u = 1; u <= n; u++)
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v, w = e[i].w;
			ret = min(ret, w + dist[v][u]);
		}
	if (ret > c)
		cout << 1 << '\n';
	else
		cout << 2 << '\n';
	return 0;
}
