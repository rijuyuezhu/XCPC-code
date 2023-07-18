#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAXN = 4e5 + 5;
constexpr int INF = 0x3f3f3f3f;

int n;
int l[MAXN], r[MAXN], lsh[MAXN], _lsh, ans;

void LSH()
{
	sort(lsh + 1, lsh + 1 + _lsh);
	_lsh = unique(lsh + 1, lsh + 1 + _lsh) - lsh - 1;
}

int LSH(int x) 
{
	return lower_bound(lsh + 1, lsh + 1 + _lsh, x) - lsh;
}

struct BIT {
	int tr[MAXN];
	int n;
	int rev;
	void init(int _n, int _rev = 0) 
	{
		n = _n;
		rev = _rev;
		for (int i = 1; i <= n; i++)
			tr[i] = -INF;
	}

	int lowbit(int x) 
	{
		return x & -x;
	}

	void mdy(int x, int v) 
	{
		if (rev)
			x = n + 1 - x;
		for (int i = x; i <= n; i += lowbit(i))
			tr[i] = max(tr[i], v);
	}

	int qry(int x) 
	{
		if (rev)
			x = n + 1 - x;
		int ret = -INF;
		for (int i = x; i; i -= lowbit(i))
			ret = max(ret, tr[i]);
		return ret;
	}
}t1, t2;

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> l[i] >> r[i];
		lsh[++_lsh] = l[i];
		lsh[++_lsh] = r[i];
	}
	LSH();
	for (int i = 1; i <= n; i++) {
		l[i] = LSH(l[i]);
		r[i] = LSH(r[i]);
	}
	t1.init(_lsh, 0);
	t2.init(_lsh, 1);
	ans = 0;
	for (int i = 1; i <= n; i++) {
		int ret = lsh[r[i]] - lsh[l[i]] + 1;
		if (l[i] != 1)
			ret = max(ret, lsh[r[i]] - lsh[l[i]] + 1 + t1.qry(l[i] - 1));
		ret = max(ret, lsh[r[i]] + t2.qry(l[i]));
		ans = max(ans, ret);
		t1.mdy(r[i], ret);
		t2.mdy(r[i], ret - lsh[r[i]]);
	}
	cout << ans << '\n';
	return 0;
}
