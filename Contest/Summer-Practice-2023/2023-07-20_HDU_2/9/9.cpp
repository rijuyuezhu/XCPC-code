#include <iostream>
#include <string>
using namespace std;
string s;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		int n;
		int ans = 0;
		cin >> s;
		n = s.length();
		int len = 1;
		for (int i = 1; i < n; i++)
			if (s[i] == s[i-1]) {
				len++;
			} else {
				ans += len - 1;
				len = 1;
			}
		ans += len - 1;
		cout << ans << '\n';
	}
	return 0;
}
