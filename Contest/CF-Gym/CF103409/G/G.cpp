#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAXN = 1e6 + 5;

int n;
char s[MAXN];

bool check(int k) 
{
	int lst = 0;
	for (int i = 1; i <= n; i++)
		if (s[i] == '1') {
			int le, ri;
			if (lst + 1 >= i - k + 1) {
				le = i - k + 1;
				ri = i + k;
			} else {
				le = i - k;
				ri = i + k - 1;
			}
			if (lst + 1 < le)
				return 0;
			lst = ri;
		}
	return lst >= n;
}

void work() 
{
	cin >> n;
	cin >> (s+1);
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (s[i] == '1')
			++cnt;
	if (cnt == n) {
		cout << 0 << '\n';
		return;
	}
	int L = 1, R = n, ans = -1;
	while (L <= R) {
		int M = (L + R) >> 1;
		if (check(M)) {
			ans = M;
			R = M - 1;
		} else {
			L = M + 1;
		}
	}
	cout << ans << '\n';
}
 
int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
