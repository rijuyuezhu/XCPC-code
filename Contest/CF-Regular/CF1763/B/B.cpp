#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e5 + 5;

int n, k;
struct Node {
	int h, p;
	bool operator < (const Node &B)const {
		return h > B.h;
	}
}e[MAXN];

void work() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
		cin >> e[i].h;
	for(int i = 1; i <= n; i++)
		cin >> e[i].p;
	priority_queue<Node> health;
	priority_queue<int, vector<int>, greater<int> > power, power_del;
	for(int i = 1; i <= n; i++) {
		health.push(e[i]);
		power.push(e[i].p);
	}
	ll totdam = 0;
	while(k > 0 && health.size()) {
		totdam += k;
		while(health.top().h <= totdam) {
			power_del.push(health.top().p);
			health.pop();
		}
		while(power_del.size() && power.top() == power_del.top()) {
			power.pop();
			power_del.pop();
		}
		if(power.size())
			k -= power.top();
		cerr << "(" << k << ")" << '\n';
	}
	if(k > 0)
		cout << "YES\n";
	else
		cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--)
		work();
	return 0;
}
