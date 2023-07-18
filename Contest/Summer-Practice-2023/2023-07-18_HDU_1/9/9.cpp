#include <iostream>
#include <algorithm>
using namespace std;

using ll = long long;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		ll n, m, d;
		cin >> n >> m >> d;
		if (d == 0 || m >= n * (d - 1) + 1)
			cout << "Yes" << '\n';
		else
			cout << "No" << '\n';
	}
	return 0;
}
