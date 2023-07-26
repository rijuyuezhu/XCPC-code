#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;
constexpr int MAXN = 2e6 + 5;
constexpr int MAXM = 2e6 + 5;
int n, m, deg[MAXN];
queue<int> q;
struct Edge {
	int v, nxt;
}e[MAXM];
int head[MAXN], cnt, seq[MAXN], _seq;
void addedge(int u, int v) {
	e[++cnt] = {v, head[u]};
	head[u] = cnt;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		addedge(u, v); ++deg[v];
	}        
	for (int i = 1; i <= n; i++)
		if (!deg[i])
			q.push(i);
	while (q.size()) {
		int u = q.front(); q.pop();
		seq[++_seq] = u;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (!--deg[v])
				q.push(v);
		}
	}
	if (_seq == n) {
		cout << 1 << '\n';
		for (int i = 1; i <= n; i++)
			cout << seq[i] << ' ';
		cout << '\n';
	} else {
		cout << 2 << '\n';
		for (int i = 1; i <= n; i++)
			cout << i << ' ';
		cout << '\n';
		for (int i = n; i >= 1; i--)
			cout << i << ' ';
		cout << '\n';
	}
	return 0;
}
