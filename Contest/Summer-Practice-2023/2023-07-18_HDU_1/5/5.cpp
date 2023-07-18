#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
constexpr int MAXN = 1e5 + 5;
int n, m;
string s[MAXN];
int id[MAXN], cls[MAXN], _cls;
void get_min(string &str) {
	string tmp = str;
	int i = 0, j = 1, k = 0, len = str.length();
	while (k < len && i < len && j < len) {
		if (str[(i + k) % len] == str[(j + k) % len]) {
			k++;
		} else {
			if (str[(i + k) % len] > str[(j + k) % len])
				i += k + 1;
			else
				j += k + 1;
			if (i == j)
				++i;
			k = 0;
		}
	}
	i = min(i, j);
	for (int t = i; t < len; t++)
		str[t - i] = tmp[t];
	for (int t = 0; t < i; t++)
		str[t + len - i] = tmp[t];
}

bool cmp(int x, int y) {
	return s[x] < s[y];
}
void work() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		get_min(s[i]);
	}
	for (int i= 1; i <= n; i++)
		id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	_cls = 0;
	cls[id[1]] = ++_cls;
	for (int i = 2; i <= n; i++) {
		int t = id[i], p = id[i-1];
		if (s[t] == s[p])
			cls[t] = _cls;
		else
			cls[t] = ++_cls;
	}
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int x, y;
		cin >> x >> y;
		if (cls[x] == cls[y])
			cout << "Yes" << '\n';
		else
			cout << "No" << '\n';
	}
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
