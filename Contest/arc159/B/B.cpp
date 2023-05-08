#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
constexpr ll INF = 1e18;


ll A, B, ans;
vector<ll> pr;


ll gcd(ll a, ll b) 
{
	return !b ? a : gcd(b, a % b);
}
void simplify()
{
	ll g = gcd(A, B);
	A /= g;
	B /= g;
}

void divide(ll x)
{
	for (int i = 2; 1ll * i * i <= x; i++)
		if (x % i == 0) {
			pr.push_back(i);
			while (x % i == 0)
				x /= i;
		}
	if(x > 1)
		pr.push_back(x);
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
	if (A < B)
		swap(A, B);
	simplify();
	divide(A - B);
	cerr << A << ' ' << B << '\n';
	while (B > 0) {
		ll mn = B;
		for (ll p : pr)
			if ((A - B) % p == 0)
				mn = min(mn, B % p);
		ans += mn;
		A -= mn, B -= mn;
		simplify();
		cerr << A << ' ' << B << '\n';
	}
	cout << ans << '\n';

	return 0;
}
