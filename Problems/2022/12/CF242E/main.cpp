#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int MAXN = 1e5 + 5;
constexpr int MAXB = 20;
// Attention: The allowed bits range from 0 to MAXB-1


struct Sgt {
#define ls o << 1
#define rs o << 1 | 1
	struct Node {
		int sum;
		int tag;
	}e[MAXN << 2];
	void upd(int o) {
		e[o].sum = e[ls].sum + e[rs].sum;
	}
	void build(int o, int l, int r, int *a, int bt) {
		e[o].tag = 0;
		if(l == r) {
			e[o].sum = (a[l] >> bt) & 1;
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, a, bt);
		build(rs, m+1, r, a, bt);
		upd(o);
	}
	void revpnt(int o, int l, int r, int k) {
		if(k) {
			e[o].sum = r - l + 1 - e[o].sum;
			e[o].tag ^= 1;
		}
	}
	void psd(int o, int l, int r) {
		int m = (l + r) >> 1;
		revpnt(ls, l, m, e[o].tag);
		revpnt(rs, m+1, r, e[o].tag);
		e[o].tag = 0;
	}
	void revrange(int o, int l, int r, int x, int y, int k) {
		if(x <= l && r <= y) {
			revpnt(o, l, r, k);
			return ;
		}
		psd(o, l, r);
		int m = (l + r) >> 1;
		if(x <= m)
			revrange(ls, l, m, x, y, k);
		if(y > m)
			revrange(rs, m+1, r, x, y, k);
		upd(o);
	}
	int qryrange(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y)
			return e[o].sum;
		psd(o, l, r);
		int m = (l + r) >> 1;
		if(y <= m)
			return qryrange(ls, l, m, x, y);
		else if(x > m)
			return qryrange(rs, m+1, r, x, y);
		else
			return qryrange(ls, l, m, x, m) + qryrange(rs, m+1, r, m+1, y);
	}
#undef ls
#undef rs
}tr[MAXB];


int n, a[MAXN];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	for(int i = 0; i < MAXB; i++)
		tr[i].build(1, 1, n, a, i);
	int m;
	cin >> m;
	for(int t = 1; t <= m; t++) {
		int op, x, l, r;
		cin >> op;
		if(op == 1) {
			cin >> l >> r;
			ll sum = 0;
			for(int i = 0; i < MAXB; i++)
				sum += ll(tr[i].qryrange(1, 1, n, l, r)) << i;
			cout << sum << '\n';
		} else {
			cin >> l >> r >> x;
			for(int i = 0; i < MAXB; i++)
				if((x >> i) & 1)
					tr[i].revrange(1, 1, n, l, r, (x >> i) & 1);
		}
	}
	return 0;
}
