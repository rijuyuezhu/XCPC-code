#include <iostream>
#include <algorithm>
#include <vector>
using ll = long long;
using namespace std;

ll A, B;
vector<ll> factor, factor2;

void divide(ll v)
{
	for (int i = 1; 1ll * i * i <= v; i++) {
		if (v % i == 0) {
			factor.push_back(i);
			if (i != v / i)
				factor2.push_back(v / i);
		}
	}
	for (int i = (int)factor2.size() - 1; i >= 0; i--)
		factor.push_back(factor2[i]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> A >> B;
	if (A == B) {
		cout << 1 << '\n';
		return 0;
	}

	if (A < B) {
		swap(A, B);
	}
	divide(A - B);
	ll ret = B, ans = 0;
	for (int i = (int)factor.size()-1; i >= 0; i--) {
		ll v = factor[i];
		ans += ret / v;
		ret %= v;
	}
	cout << ans << '\n';
	

	
	return 0;
}
