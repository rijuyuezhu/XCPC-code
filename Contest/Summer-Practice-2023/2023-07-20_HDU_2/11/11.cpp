#include <iostream>
#include <algorithm>
using namespace std;
using db = double;
constexpr int MAXN = 1e4 + 5;
constexpr db eps = 1e-8;
db p[MAXN], sh[MAXN];
int n;
void work() {
	cin >> n;
	sh[n] = 0;
	for (int i = n-1; i >= 1; i--) {
		sh[i] = sh[i+1] + 1.0 / db(i);
		p[i] = i * sh[i];
	}
	p[0] = 1;
	int k = 0;
	for (int i = 1; i <= n-1; i++)
		if(p[i] - p[k] > eps)
			k = i;
	cout << k << '\n';
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
