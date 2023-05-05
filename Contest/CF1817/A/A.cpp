#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 2e5 + 5;

int n, q, a[MAXN], b[MAXN], s[MAXN];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 2; i <= n-1; i++)
		b[i] = ((a[i-1] >= a[i]) && (a[i] >= a[i+1]));
	for (int i = 1; i <= n; i++)
		s[i] = s[i-1] + b[i];
	for (int t = 1; t <= q; t++) {
		int l, r;
		cin >> l >> r;
		int ans = 0;
		if (l == r) 
			ans = 1;
		else
			ans = r - l + 1 - (s[r-1] - s[l]);
		cout << ans << '\n';
	}
	return 0;
}
