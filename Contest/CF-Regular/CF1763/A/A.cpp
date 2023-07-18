#include <iostream>
#include <algorithm>
using namespace std;

constexpr int B = 10;
constexpr int MAXN = 520;
int n, a[MAXN], ans;
void work() {
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	ans = 0;
	for(int i = 0; i < B; i++) {
		int cnt = 0;
		for(int j = 1; j <= n; j++)
			if( (a[j] >> i) & 1 )
				++cnt;
		if(cnt > 0 && cnt < n)
			ans += (1 << i);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--)
		work();
	return 0;
}
