#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
using pii = pair<int, int>;
constexpr int MAXN = 2e5 + 5;
constexpr int MAXM = 2e5 + 5;
constexpr int P1 = 998244353;
constexpr int bas1 = 233;
constexpr int P2 = 1e9 + 7;
constexpr int bas2 = 1919810;
constexpr int C1 = 501;
constexpr int C2 = 234;
int n, m;
struct Edge {
	int v, nxt;
}e[MAXM];
int head[MAXN], cnt, deg[MAXN], seq[MAXN], _seq, onc[MAXN], basPow1[MAXN], basPow2[MAXN], siz[MAXN];
pii hsonc[MAXN];

void addedge(int u, int v) {
	e[++cnt] = {v, head[u]};
	head[u] = cnt;
}

void clear() {
	for(int i = 1; i <= n; i++) {
		head[i] = deg[i] = seq[i] = onc[i] = siz[i] = 0;
		hsonc[i] = {0, 0};
	}
	cnt = _seq = 0;
}

void dfs(int u) {
	onc[u] = 1;
	seq[++_seq] = u;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if(!onc[v] && deg[v] == 2) {
			dfs(v);
			return ;
		}
	}
}

pii hs(int u, int fa) {
	pii ret = {0, 0};
	siz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if(v == fa || onc[v])
			continue;
		pii hsv = hs(v, u);
		ret.first = (1ll * ret.first + 1ll * basPow1[siz[v]] * hsv.first) % P1;
		ret.second = (1ll * ret.second + 1ll * basPow2[siz[v]] * hsv.second) % P2;
		siz[u] += siz[v];
	}
	ret.first = (1ll * ret.first + 1ll * C1 * siz[u]) % P1;
	ret.second = (1ll * ret.second + 1ll * C2 * siz[u]) % P2;
	return ret;
}

void find_circle() {
	for(int i = 1; i <= n; i++)
		if(deg[i] == 2) {
			dfs(i);
			break;
		}
}
bool check() {
	queue<int> que;
	for(int i = 1; i <= n; i++)
		if(deg[i] == 1)
			que.push(i);
	while(que.size()) {
		int u = que.front(); que.pop();
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			--deg[u]; --deg[v];
			if(deg[v] == 1) 
				que.push(v);
		}
	}
	bool flag = 0;
	for(int i = 1; i <= n; i++) {
		if(deg[i]) {
			flag = 1;
			if(deg[i] >= 3)
				return 0;
		}
	}
	if(!flag)
		return 1;
	//then, we have circle
	find_circle();

	for(int i = 1; i <= _seq; i++)
		hsonc[i] = hs(seq[i], 0);
	if(_seq % 2 == 0) {
		for(int i = 3; i <= _seq; i++)
			if(hsonc[i] != hsonc[i-2])
				return 0;
	} else {
		for(int i = 2; i <= _seq; i++)
			if(hsonc[i] != hsonc[i-1])
				return 0;
	}
	return 1;
}

void work() {
	cin >> n >> m;
	clear();
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		if(u == v)
			continue;
		addedge(u, v);
		addedge(v, u);
		++deg[u]; ++deg[v];
	}
	if(check()) {
		cout << "YES" << '\n';
	} else {
		cout << "NO" << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	basPow1[0] = basPow2[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		basPow1[i] = 1ll * basPow1[i-1] * bas1 % P1;
		basPow2[i] = 1ll * basPow2[i-1] * bas2 % P2;
	}
	int T;
	cin >> T;
	while(T--)
		work();
	return 0;
}
