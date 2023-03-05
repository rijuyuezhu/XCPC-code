#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
using db = double;
constexpr int MAXN = 1e5 + 5;

namespace Sgt { 
#define ls o << 1
#define rs o << 1 | 1
	struct Node {
		db x, x2, tag;
		void pushup(Node a, Node b) {
			x = a.x + b.x;
			x2 = a.x2 + b.x2;
		}
	}e[MAXN << 2];
	void build(int o, int l, int r, db a[]) {
		e[o].tag = 0;
		if(l == r) {
			e[o] = {a[l], a[l] * a[l], 0};
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, a);
		build(rs, m+1, r, a);
		e[o].pushup(e[ls], e[rs]);
	}
	void addpnt(int o, int l, int r, db k) {
		e[o].x2 += 2 * k * e[o].x + k * k * (r - l + 1);
		e[o].x += k * (r - l + 1);
		e[o].tag += k;
	}
	void psd(int o, int l, int r) {
		int m = (l + r) >> 1;
		addpnt(ls, l, m, e[o].tag);
		addpnt(rs, m+1, r, e[o].tag);
		e[o].tag = 0;
	}
	void addrange(int o, int l, int r, int x, int y, db k) {
		if(x <= l && r <= y) {
			addpnt(o, l, r, k);
			return ;
		}
		psd(o, l, r);
		int m = (l + r) >> 1;
		if(x <= m)
			addrange(ls, l, m, x, y, k);
		if(y > m)
			addrange(rs, m+1, r, x, y, k);
		e[o].pushup(e[ls], e[rs]);
	}
	Node qryrange(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y)
			return e[o];
		psd(o, l, r);
		int m = (l + r) >> 1;
		if(y <= m)
			return qryrange(ls, l, m, x, y);
		else if(x > m)
			return qryrange(rs, m+1, r, x, y);
		else {
			Node ans;
			ans.pushup(qryrange(ls, l, m, x, m), qryrange(rs, m+1, r, m+1, y));
			return ans;
		}
	}
#undef ls
#undef rs
}
using namespace Sgt;

int n, m;
db a[MAXN];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n, a);
	for(int i = 1; i <= m; i++) {
		int op;
		cin >> op;
		if(op == 1) {
			int x, y;
			db k;
			cin >> x >> y >> k;
			addrange(1, 1, n, x, y, k);
		} else if(op == 2) {
			int x, y, len;
			cin >> x >> y;
			len = y - x + 1;
			Node ret = qryrange(1, 1, n, x, y);
			cout << fixed << setprecision(4) << (db)ret.x / len << '\n';
		} else {
			int x, y, len;
			cin >> x >> y;
			len = y - x + 1;
			Node ret = qryrange(1, 1, n, x, y);
			cout << fixed << setprecision(4) << (ret.x2 / len - (ret.x / len) * (ret.x / len)) << '\n';
		}
	}
	return 0;
}
