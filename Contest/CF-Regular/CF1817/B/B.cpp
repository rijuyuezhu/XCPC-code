#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 2005;
int n, m;
struct Edge {
	int v, nxt;
}e[MAXN << 1];
int head[MAXN], cnt, deg[MAXN];
int stk[MAXN], _stk, vis[MAXN], flag, around[MAXN], rt;

void addedge(int u, int v) 
{
	e[++cnt] = {v, head[u]};
	head[u] = cnt;
}

void clear()
{
	for (int i = 1; i <= n; i++)
		head[i] = deg[i] = around[i] = 0;
	cnt = 0;
	flag = 0;
}
void dfs(int u, int fr)
{
	stk[++_stk] = u;
	vis[u] = 1;
	if (fr != rt && around[u])
		throw 1;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (v == fr || vis[v])
			continue;
		dfs(v, u);
	}
	--_stk;
}

void work()
{
	cin >> n >> m;
	clear();
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
		++deg[u];
		++deg[v];
	}
	try {
		for (int i = 1; i <= n; i++)
			if(deg[i] >= 4) {
				rt = i;
				_stk = 0;
				for (int j = 1; j <= n; j++)
					vis[j] = 0;
				for (int j = head[i]; j; j = e[j].nxt)
					around[e[j].v] = 1;
				dfs(rt, 0);
			}
	} catch (...) {
		flag = 1;
	}
	if (flag) {
		cout << "YES" << '\n';
		cout << 2 + _stk << '\n';
		for (int i = 1; i < _stk; i++)
			cout << stk[i] << ' ' << stk[i+1] << '\n';
		cout << stk[_stk] << ' ' << stk[1] << '\n';
		int ext = 0;
		for (int i = head[rt]; i && ext < 2; i = e[i].nxt) {
			int v = e[i].v;
			if (v != stk[2] && v != stk[_stk]) {
				cout << rt << ' ' << v << '\n';
				++ext;
			}
		}
	} else {
		cout << "NO" << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--)
		work();
	return 0;
}
