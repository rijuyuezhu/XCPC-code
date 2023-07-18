#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int MAXN = 105;
constexpr int INF = 0x3f3f3f3f;

int n, K, a[MAXN][MAXN], d[MAXN][MAXN];

void solve() {
	ll s, t;
	int s0, t0;
	cin >> s >> t;
	s0 = (s-1) % n + 1;
	t0 = (t-1) % n + 1;
	int ans = max(1, d[s0][t0]);
	cout << (ans == INF ? -1 : ans) << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> K;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			d[i][j] = INF;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j])
				d[i][j] = min(d[i][j], 1);
		}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++)
		solve();


	return 0;
}
