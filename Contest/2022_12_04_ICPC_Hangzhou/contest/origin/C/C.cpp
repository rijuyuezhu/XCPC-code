#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAXN = 3005;
constexpr int MAXK = 3005;
constexpr int MAXP = 15;
constexpr int INF = 1e9;
int n, k;
int p[MAXN], w[MAXN][MAXP];
int f[MAXN][MAXK], g[MAXN][MAXK];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> p[i];
		for(int j = 1; j <= p[i]; j++)
			cin >> w[i][j];
	}
	for(int i = 0; i <= n+1; i++)
		for(int j = 0; j <= k; j++)
			f[i][j] = g[i][j] = -INF;
	f[0][0] = g[n+1][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= k; j++) {
			f[i][j] = f[i-1][j];
			if(j >= p[i])
				f[i][j] = max(f[i][j], f[i-1][j-p[i]] + w[i][p[i]]);
		}
	for(int i = n; i >= 1; i--)
		for(int j = 0; j <= k; j++) {
			g[i][j] = g[i+1][j];
			if(j >= p[i])
				g[i][j] = max(g[i][j], g[i+1][j-p[i]] + w[i][p[i]]);
		}
	int ans = 0;
	for(int j = 0; j <= k; j++)
		ans = max(ans, f[n][j]);
	for(int t = 1; t <= n; t++) {
		for(int v = 1; v <= p[t]; v++)
			for(int j = 0; j <= k - v; j++)
				ans = max(ans, f[t-1][j] + g[t+1][k - v - j] + w[t][v]);
	}
	cout << ans << endl;
	return 0;
}
