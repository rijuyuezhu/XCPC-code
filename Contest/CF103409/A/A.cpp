#include <iostream>
#include <algorithm>
using namespace std;

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		long long x;
		cin >> x;
		cout << 2 * x - 1 << '\n';
	}
	return 0;
}
