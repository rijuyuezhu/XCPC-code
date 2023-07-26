#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e3 + 5;
int n;
ll a[MAXN];

bool check(ll v) {
	if (v == 1) return 0;
	for (ll i = 2; i * i <= v; i++)
		if (v % i == 0)
			return 0;
	return 1;
}
bool check2(ll S) {
	if (S < 4)
		return 0;
	else if (S % 2 == 0)
		return 1;
	else
		return check(S - 2);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	ll S = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		S += a[i];
	}
	if (n == 1) {
		if (check(a[1]))
			cout << "Yes" << '\n';
		else
			cout << "No" << '\n';
		return 0;
	} else if (n == 2) {
		if (check2(S))
			cout << "Yes" << '\n';
		else
			cout << "No" << '\n';
	} else {
		if (S >= 2 * n)
			cout << "Yes" << '\n';
		else
			cout << "No" << '\n';
	}
	return 0;
}
