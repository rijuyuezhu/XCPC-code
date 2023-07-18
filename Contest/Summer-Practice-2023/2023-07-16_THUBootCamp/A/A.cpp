#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAXN = 1e6 + 5, INF = 0x3f3f3f3f;


int n, a[MAXN], lsh[MAXN], _lsh, p[MAXN];
int vis[MAXN], b[MAXN], _b, ans[MAXN], _gr;
int timest[MAXN], pos[MAXN];

void LSH() {
	sort(lsh + 1, lsh + 1 + _lsh);
	_lsh = unique(lsh + 1, lsh + 1 + _lsh) - lsh - 1;
}

int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + _lsh, x) - lsh;
}
void dfs(int u) {
	vis[u] = 1;
	b[++_b] = u;
	if (!vis[p[u]])
		dfs(p[u]);
}
void calc() {
	for (int i = 1; i <= _b; i++)
		b[i + _b] = b[i];
	for (int i = 1; i <= 2 * _b; i++) {
		int v = a[b[i]];
		if (timest[v] == _gr)
			ans[b[i]] = min(ans[b[i]], i - pos[v]);
		timest[v] = _gr;
		pos[v] = i;
	}

}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ans[i] = INF;
		lsh[++_lsh] = a[i];
	}
	LSH();
	for (int i = 1; i <= n; i++)
		a[i] = LSH(a[i]);
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	for (int i = 1; i <= n; i++)
		if (!vis[i]) {
			_b = 0;
			++_gr;
			dfs(i);
			calc();
		}
	int fans = 0;
	for (int i = 1; i <= n; i++)
		fans = max(fans, ans[i]);
	cout << fans << '\n';
	return 0;
}
