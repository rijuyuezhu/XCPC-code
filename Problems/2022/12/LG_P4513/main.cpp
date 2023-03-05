#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
constexpr int MAXN = 5e5 + 5;
int n, m, a[MAXN];
namespace Sgt {
#define ls o << 1
#define rs o << 1 | 1
	struct Val {
		int sum, lval, rval, val;
		void merge(Val a, Val b) {
			sum = a.sum + b.sum;
			lval = max(a.lval, a.sum + b.lval);
			rval = max(b.rval, b.sum + a.rval);
			val = max(max(a.val, b.val), a.rval + b.lval);
		}
	};
	Val e[MAXN << 2];
	void build(int o, int l, int r, int a[]) {
		if(l == r) {
			e[o] = {a[l], a[l], a[l], a[l]};
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, a);
		build(rs, m+1, r, a);
		e[o].merge(e[ls], e[rs]);
	}
	void mdypos(int o, int l, int r, int x, int v) {
		if(l == r) {
			e[o] = {v, v, v, v};
			return ;
		}
		int m = (l + r) >> 1;
		if(x <= m)
			mdypos(ls, l, m, x, v);
		else
			mdypos(rs, m+1, r, x, v);
		e[o].merge(e[ls], e[rs]);
	}
	Val qryrange(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y)
			return e[o];
		int m = (l + r) >> 1;
		if(y <= m)
			return qryrange(ls, l, m, x, y);
		else if(x > m)
			return qryrange(rs, m+1, r, x, y);
		else {
			Val ans;
			ans.merge(qryrange(ls, l, m, x, y), qryrange(rs, m+1, r, x, y));
			return ans;
		}
	}
#undef ls
#undef rs
}
using namespace Sgt;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n, a);
	for(int i = 1; i <= m; i++) {
		int k;
		cin >> k;
		if(k == 1) {
			int a, b;
			cin >> a >> b;
			if(a > b)
				swap(a, b);
			Val ans = qryrange(1, 1, n, a, b);
			cout << ans.val << '\n';
		} else {
			int p, s;
			cin >> p >> s;
			mdypos(1, 1, n, p, s);
		}
	}
	return 0;
}
