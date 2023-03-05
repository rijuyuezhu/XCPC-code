#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
using pr = pair<int, int>;
using ll = long long;
int a, b, d;
vector<int> prs;
map<pr, ll> mp;
void clear() {
	prs.clear();
	mp.clear();
}
void divide(int n) {
	for(int i = 2; 1ll * i * i <= n; i++)
		if(n % i == 0) {
			prs.push_back(i);
			while(n % i == 0)
				n /= i;
		}
	if(n > 1)
		prs.push_back(n);
}


void work() {
	clear();
	cin >> a >> b;
	if(a > b)
		swap(a, b);
	d = b - a;
	divide(d);
	cout << dfs(a, d) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--)
		work();
	return 0;
}
