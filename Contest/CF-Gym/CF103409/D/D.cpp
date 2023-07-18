#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using pr = pair<int, int>;
constexpr int MAXN = 2100;

int n, a[MAXN], b[MAXN], p[MAXN], fp[MAXN];
int stk[MAXN], _stk;
vector<pr> ans;

bool work(int v) {
	int x = p[v], y = fp[v];
	if (x > y)
		return 0;
	stk[_stk = 1] = x;
	for (int i = x+1; i <= y; i++) 
		if (a[i] < v) {
			while (_stk > 0 && a[i] > a[stk[_stk]])
				--_stk;
			stk[++_stk] = i;
		}
	for (int i = 2; i <= _stk; i++) {
		ans.push_back(pr(stk[i-1], stk[i]));
		swap(p[a[stk[i-1]]], p[a[stk[i]]]);
		swap(a[stk[i-1]], a[stk[i]]);
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			p[a[i]] = i;
		}
		for (int i = 1; i <= n; i++) {
			cin >> b[i];
			fp[b[i]] = i;
		}
		ans.clear();
		for (int i = n; i >= 1; i--)
			if (!work(i)) {
				cout << -1 << '\n';
				goto END;
			}
		cout << ans.size() << '\n';
		for (auto i : ans) {
			cout << i.first << ' ' << i.second << '\n';
		}
END:
		;
	}
	
	return 0;
}
