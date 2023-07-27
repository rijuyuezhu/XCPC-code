#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e6 + 5;
constexpr int MAXM = 1e6 + 5;
int n, m;
struct Edge {
	int v, nxt;
}e[MAXM];
int head[MAXN], cnt;
void addedge(int u, int v) {
	e[++cnt] = {v, head[u]};
	head[u] = cnt;
}
int d[MAXN], vis[MAXN], ins[MAXN], stk[MAXN], tolow[MAXN];
queue<int> que;
void clear() {
	cnt = 0;
	for (int i = 1; i <= n; i++) {
		head[i] = 0;
		d[i] = 0;
		vis[i] = 0;
		ins[i] = 0;
		stk[i] = 0;
		tolow[i] = -1;
	}
	que = queue<int> ();
}
int better(int x, int y) {
	if (x == -1)
		return y;
	else if (y == -1)
		return x;
	else
		return d[x] < d[y] ? y : x;
}
bool dfs(int u) {
	//cerr << u << "t\n";
	vis[u] = ins[u] = 1; stk[d[u]] = u;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (!vis[v]) {
			if(d[v] != d[u] + 1)
				return 0;
			if (!dfs(v))
				return 0;
			tolow[u] = better(tolow[u], tolow[v]);
		} else if (ins[v]) {
			tolow[u] = better(tolow[u], v);
		} else {
			if (d[v] != d[u] + 1)
				return 0;
			int x = tolow[v];
			if (x != -1) {
				int dep = d[x];
				if (dep > d[u] || x != stk[dep]) 
					return 0;
			}
		}
	}
	ins[u] = 0;
	return 1;
}
void work() {
	cin >> n >> m;
	clear();
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		if (u == v)
			continue;
		addedge(u, v);
	}
	d[1] = 0; vis[1] = 1; 
	que.push(1);
	while (que.size()) {
		int u = que.front(); que.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (vis[v])
				continue;
			d[v] = d[u] + 1; vis[v] = 1;
			que.push(v);

		}
	}
	for (int i = 1; i <= n; i++) 
		vis[i] = 0;
	if (dfs(1))
		cout << "Yes" << '\n';
	else
		cout << "No" << '\n';
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
