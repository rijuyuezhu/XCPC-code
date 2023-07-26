#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
using ll = long long;
using pr = pair<ll, ll>;
constexpr int MAXN = 5e4 + 5;
int n, q;
vector<vector<ll> > res_a, res_b;
map<pr, int> mp_a, mp_b, cnt;
int idx_a, idx_b;
void clear() {
	res_a.clear(); res_b.clear();
	mp_a.clear(); mp_b.clear(); cnt.clear();
	idx_a = idx_b = 0;
}

void inserta(ll a, ll b) {
	int id;
	auto it = mp_a.find(pr(a, b % a));
	if (it == mp_a.end()) {
		mp_a[pr(a, b % a)] = id = idx_a++;
		res_a.push_back(vector<ll>());
	} else
		id = it->second;
	res_a[id].push_back(b);
}
void insertb(ll a, ll b) {
	int id;
	auto it = mp_b.find(pr(a % b, b));
	if (it == mp_b.end()) {
		mp_b[pr(a % b, b)] = id = idx_b++;
		res_b.push_back(vector<ll>());
	} else
		id = it->second;
	res_b[id].push_back(a);
}
void init(ll a, ll b) {
	cnt[pr(a, b)]++;
	if (a == b) {
		inserta(a, b);
		return ;
	}
	while (a && b) {
		if (a > b) {
			insertb(a, b);
			a %= b;
		} else {
			inserta(a, b);
			b %= a;
		}
	}
}

int trya(ll A, ll B) {
	auto it = mp_a.find(pr(A, B % A));
	if (it == mp_a.end())
		return 0;
	int id = it->second;
	auto &vec = res_a[id];
	int len = vec.size();
	int sp = upper_bound(vec.begin(), vec.end(), B) - vec.begin();
	return len - sp;
}
int tryb(ll A, ll B) {
	auto it = mp_b.find(pr(A % B, B));
	if (it == mp_b.end())
		return 0;
	int id = it->second;
	auto &vec = res_b[id];
	int len = vec.size();
	int sp = upper_bound(vec.begin(), vec.end(), A) - vec.begin();
	return len - sp;
}
void work() {
	clear();
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		ll a, b;
		cin >> a >> b;
		init(a, b);
	}
	for (auto &vec : res_a)
		sort(vec.begin(), vec.end());
	for (auto &vec : res_b)
		sort(vec.begin(), vec.end());
	for (int i = 1; i <= q; i++) {
		ll A, B;
		cin >> A >> B;
		ll ans = 0;
		ans += trya(A, B);
		ans += tryb(A, B);
		auto it = cnt.find(pr(A, B));
		if (it != cnt.end())
			ans += it->second;
		cout << ans << '\n';
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
