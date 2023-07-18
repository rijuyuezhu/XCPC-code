#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 2e5 + 5;

int n, a[MAXN], b[MAXN];

void work() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n);
	for (int i = 1; i <= n; i++)
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
