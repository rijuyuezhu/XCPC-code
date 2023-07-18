#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e6 + 5;

int n, tot;
ll ans;
char s[MAXN];

void work() 
{
	cin >> n;
	cin >> (s + 1);
	ans = 0;
	tot = 0;
	for (int i = n; i >= 1; i--)
		if (s[i] == '1') {
			if (tot > 0) {
				ans += i;
				tot--;
			} else {
				tot++;
			}
		} else {
			tot++;
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
