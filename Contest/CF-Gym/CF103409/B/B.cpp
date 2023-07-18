#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
constexpr int MAXN = 1e6 + 5;
int n, q, a[MAXN], b[MAXN], x[MAXN], ccnt;
set<int> pos;

namespace BIT {
	int t[MAXN], s[MAXN];
	int lowbit(int x) {return x & -x;}
	void init() {
		for (int i = 1; i <= n; i++) {
			s[i] = s[i-1] + x[i];
			t[i] = s[i] - s[i - lowbit(i)];
		}
	}
	void add(int x, int v) {
		for (int i = x; i <= n; i += lowbit(i))
			t[i] += v;
	}
	int sum(int x) {
		int ret = 0;
		for (int i = x; i; i -= lowbit(i))
			ret += t[i];
		return ret;
	}
	int sum(int x, int y) {
		return sum(y) - sum(x-1);
	}
}

int mdy(int c, int v) {
	auto it = pos.lower_bound(c+1);
	if (it == pos.end())
		return n + 2;
	int pw = *it;
	int l = 1, r = pw - 1, ret = pw;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (BIT::sum(m, pw-1) == pw-1-m+1) {
			r = m - 1;
			ret = m;
		} else {
			l = m + 1;
		}
	}
	ccnt += (pw - 1 - ret + 1 + (ret != 1)) * v;
	return ret;
}

void cancel(int c, int v) {
	if (v == 9) {
		BIT::add(c, -1);
	} else if (v >= 10) {
		mdy(c-1, -1);
		pos.erase(pos.find(c));
	}
}

void enable(int c, int v) {
	if (v == 9) {
		BIT::add(c, 1);
	} else if (v >= 10) {
		pos.insert(c);
		mdy(c-1, 1);
	}
}

void work() {
	int r, c, d;
	cin >> r >> c >> d;
	int lccnt = ccnt;
	int ori_c = (c >= mdy(c, -1) - 1);
	int ori = a[c] + b[c];
	cancel(c, ori);
	if (r == 1)
		a[c] = d;
	else 
		b[c] = d;
	int nwv = a[c] + b[c];
	enable(c, nwv);
	int nwv_c = (c >= mdy(c, 1) - 1);
	int ans = abs(ccnt - lccnt) - (ori_c != nwv_c) + ((ori + ori_c) % 10 != (nwv + nwv_c) % 10);
	cout << (nwv + nwv_c) % 10 << ' ' << ans+ (nwv != ori) << '\n';
}

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		char ch;
		cin >> ch;
		a[i] = ch - '0';
	}
	for (int i = 1; i <= n; i++) {
		char ch;
		cin >> ch;
		b[i] = ch - '0';
	}
	for (int i = 1; i <= n; i++) {
		int s = a[i] + b[i];
		if (s == 9)
			x[i] = 1;
		else if (s >= 10) {
			pos.insert(i);
		}
	}
	BIT::init();
	for(auto c : pos)
		mdy(c-1, 1);
	while(q--)
		work();

			

	return 0;
}
