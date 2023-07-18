#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 5;
int a[MAXN];
int n;
double sum, w;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	w = sum / (n + 1);
	cout << fixed << setprecision(8) << 2 * w << ' ';
	for(int i = 2; i <= n; i++) {
		cout << fixed << setprecision(8) << w << ' ';
	}
	cout << '\n';
	return 0;
}
