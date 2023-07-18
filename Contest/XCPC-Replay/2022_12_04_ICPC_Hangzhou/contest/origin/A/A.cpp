#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e5 + 5;
#define int long long
int n, m, a[MAXN], ans, K, K2;
int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}
void exgcd(int a, int b, int &x, int &y) {
	if(!b) x = 1, y = 0;
	else exgcd(b, a % b, y, x), y -= a / b * x;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		(K += a[i]) %= m;
	}
	int g = gcd(n, m);
	K2 = (K + 1ll * n * (n + 1) / 2) % m;
	int ans1 = K % g;
	int ans2 = K2 % g;
	if(ans1 <= ans2) {
		cout << ans1 << '\n';
		int x, y;
		exgcd(n / g, m / g, x, y);
		x *= - (K / g);
		x = (x % m + m) % m;
		cout << x << ' ' << 0 << '\n';
	} else  {
		cout << ans2 << '\n';
		int x, y;
		exgcd(n / g, m / g, x, y);
		x *= - (K2 / g);
		x = (x % m + m) % m;
		cout << x << ' ' << 1 << '\n';
	}
	return 0;
}
