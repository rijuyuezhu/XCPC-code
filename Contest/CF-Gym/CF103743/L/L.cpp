#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
constexpr int MAXN = 2e5 + 5;
using ll = long long;
int n;
char s[MAXN];
int preA[MAXN], sufC[MAXN], c;
ll ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> (s + 1);

	n = strlen(s + 1);
	preA[0] = 0;
	for (int i = 1; i <= n; i++)
		if (s[i] == 'A') {
			preA[i] = preA[i-1] + 1;
		} else {
			preA[i] = 0;
		}
	sufC[n+1] = 0;
	for (int i = n; i >= 1; i--)
		if (s[i] == 'C') {
			sufC[i] = sufC[i+1] + 1;
		} else {
			sufC[i] = 0;
		}
	int c = 0;
	ll ans = 0;
	for (int i = 1; i <= n; i++)
		if (s[i] == 'B') {
			int l = min(preA[i-1], sufC[i+1]);
			if (l >= 1) {
				ans += min(l, c + (~i & 1) + 1);
				if (!(c == 0 && (~i & 1) && l == 1))
					++c;
			}
		}
	cout << ans << '\n';
	return 0;
}
