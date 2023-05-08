#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
constexpr int MAXN = 55;
int n, a[MAXN], S, ave;

vector<vector<int> > ans;
stack<int> les;
vector<int> std1, std2;

void init() {
	for (int i = 1; i <= n; i++)
		std1.push_back(i);
	for (int i = n; i >= 3; i--)
		std2.push_back(i);
	std2.push_back(1);
	std2.push_back(2);
}

void mov(int i, int j) {
	vector<int> p1(n), p2(n); 
	for (int k = 1, c = 0; k <= n; k++) {
		if (k == i || k == j)
			continue;
		p1[k-1] = std1[c];
		p2[k-1] = std2[c];
		c++;
	}
	p1[i-1] = std1[n-2];
	p2[i-1] = std2[n-2];
	p1[j-1] = std1[n-1];
	p2[j-1] = std2[n-1];
	ans.push_back(p1);
	ans.push_back(p2);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	init();
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		S += a[i];
	}
	if (S % n != 0) {
		if ((S + n * (n+1) / 2) % n == 0) {
			cout << "Yes" << '\n';
			vector<int> piece;
			for (int i = 1; i <= n; i++) {
				a[i] += i;
				S += i;
				piece.push_back(i);
			}
			ans.push_back(piece);
		} else {
			cout << "No" << '\n';
			return 0;
		}
	} else {
		cout << "Yes" << '\n';
	}
	ave = S / n;
	for (int i = 1; i <= n; i++)
		while (a[i] < ave) {
			les.push(i);
			a[i]++;
		}
	for (int i = 1; i <= n; i++)
		while (a[i] > ave) {
			mov(i, les.top());
			les.pop();
			a[i]--;
		}
	cout << ans.size() << '\n';
	for (const auto &line : ans) {
		for (int v : line)
			cout << v << ' ';
		cout << '\n';
	}
	return 0;
}
