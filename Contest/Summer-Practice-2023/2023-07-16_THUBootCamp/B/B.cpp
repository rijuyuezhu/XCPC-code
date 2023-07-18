#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

constexpr int MAXN = 1e5 + 5;
constexpr int MAXM = 1e6 + 5;
int n, m, a[MAXN], im[MAXN], id[MAXN];
ll k, ans;
bool cmp(int x, int y) {
	return im[x] > im[y];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= m; i++) {
		int l, r;
		cin >> l >> r;
		im[l]++; im[r+1]--;
	}
	for (int i = 1; i <= n; i++) {
		im[i] += im[i-1];
		ans += 1ll * im[i] * a[i];
	}
	for (int i = 1; i <= n; i++)
		id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	for (int i = 1; i <= n; i++) {
		int t = id[i];
		ll l = min<ll>(a[t], k);
		k -= l;
		ans -= im[t] * l;
	}
	cout << ans << '\n';
	return 0;
}
