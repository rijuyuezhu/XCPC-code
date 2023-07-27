#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
using ll = long long;
ll rs() {
	string s;
	cin >> s;
	ll ret = 0;
	for (auto ch : s)
		ret = ret << 1 | ll(ch - '0');
	return ret;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll x = rs();
	ll y = rs();
	if (x == y) {
		cout << 0 << '\n';
		return 0;
	} else if (x == 0) {
		cout << -1 << '\n';
		return 0;
	}
	cout << abs(x - y) << '\n';
	return 0;
}
