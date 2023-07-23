#include <iostream>
#include <string>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e5 + 5;
int n;
ll k;
int s[MAXN], f[MAXN], d[MAXN];
void work() {
	cin >> n >> k;
	f[0] = 0;
	for (int i = 1; i <= n; i++) {
		char ch;
		cin >> ch;
		s[i] = ch - '0';
		f[i] = s[i] ^ 1;
		d[i] = f[i] ^ f[i-1];
	}
	if (n == 1) {
		if (k & 1)
			cout << 0 << '\n';
		else
			cout << 1 << '\n';
		return ;
	}
	ll cnt = k * 2;
	for (int i = 1; i <= n; i++)
		if (d[i]) {
			if (cnt > 0)
				cnt--;
			else {
				for (int j = i; j <= n; j++)
					d[j] = 0;
				break;
			}
		}
	if (k == 1 && cnt == k * 2) {
		if (k & 1)
			d[n] ^= 1;
	}
	f[0] = 0;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i-1] ^ d[i];
		cout << (f[i] ^ s[i]);
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
