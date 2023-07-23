#include <iostream>
using namespace std;

constexpr int P = 998244353;
int MOD(int v) { return v >= P ? v - P : v; }
struct mint {
	int v;
	mint(int v) : v(v) {}
};
mint operator + (mint a, mint b) { return MOD(a.v + b.v); }
mint operator - (mint a, mint b) { return MOD(a.v - b.v + P); }
mint operator * (mint a, mint b) { return 1ll * a.v * b.v % P; }
mint qpow(mint a, int n = P - 2) {
	mint ret = 1;
	for (; n; n >>= 1, a = a * a)
		if (n & 1)
			ret = ret * a;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		cout << (qpow(2, n-1) - 1).v << '\n';
	}
	return 0;
}
