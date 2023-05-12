#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e5 + 5, MAXM = 1e5 + 5;

int n, m;
int a[MAXN], _a;
int le, ri;

void work() {
	le = ri = _a = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		if (x > 0) {
			a[++_a] = x;
		} else if (x == -1) {
			le++;
		} else {
			ri++;
		}
	}
	int ans = 0;
	sort(a + 1, a + 1 + _a);
	_a = unique(a + 1, a + 1 + _a) - a - 1;
	a[0] = 0;
	a[_a+1] = m+1;
	for(int i = 0; i <= _a+1; i++) 
		ans = max(ans, min(le, a[i]-1-(i-1)) + min(ri, m-a[i]-(_a-i)) + _a);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--)
		work();
	return 0;
}
