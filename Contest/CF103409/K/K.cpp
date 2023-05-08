#include <iostream>
#include <algorithm>
#include <queue>
using ll = long long;
using namespace std;

constexpr int MAXN = 55;
constexpr int MAXM = 2505;
constexpr ll lINF = 1e18;
int n, m;
int w[MAXM];
struct Edge {
	int v, nxt, c;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v, int c) {
	e[++cnt] = {v, head[u], c}; 
	head[u] = cnt;
}

int dep[MAXN], vis[MAXN], num[MAXM];
ll dist[MAXN];

void bfs() {
	vis[1] = 1;
	queue<int> que;
	que.push(1);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (vis[v])
				continue;
			dep[v] = dep[u] + 1;
			vis[v] = 1;
			que.push(v);
		}
	}
}

void dfs(int u, ll nowans) {
	dist[u] = min(dist[u], nowans);
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v, c = e[i].c;
		if (dep[v] != dep[u] + 1)
			continue;
		num[c]++;
		dfs(v, nowans + num[c] * w[c]);
		num[c]--;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> w[i];
	for (int i = 1; i <= m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		addedge(u, v, c);
		addedge(v, u, c);
	}
	bfs();
	for (int i = 2; i <= n; i++)
		dist[i] = lINF;
	dfs(1, 0);
	for (int i = 2; i <= n; i++)
		cout << dist[i] << '\n';
	return 0;
}
