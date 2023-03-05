#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
using db = double;
constexpr int MAXN = 2e5 + 5;
namespace Sgt {
#define ls o << 1
#define rs o << 1 | 1
	struct Node {
		db ssin, scos, tag;
		void upd(Node a, Node b) {
			ssin = a.ssin + b.ssin;
			scos = a.scos + b.scos;
		}
	}e[MAXN << 2];
	void build(int o, int l, int r, db a[]) {
		e[o].tag = 0;
		if(l == r) {
			e[o] = {sin(a[l]), cos(a[l]), 0};
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, a);
		build(rs, m+1, r, a);
		e[o].upd(e[ls], e[rs]);
	}
	void addpnt(int o, db v) {
		Node t = e[o];
		db cosv = cos(v), sinv = sin(v);
		e[o].ssin = t.ssin * cosv + t.scos * sinv;
		e[o].scos = t.scos * cosv - t.ssin * sinv;
		e[o].tag += v;
	}
	void psd(int o) {
		addpnt(ls, e[o].tag);
		addpnt(rs, e[o].tag);
		e[o].tag = 0;
	}
	void addrange(int o, int l, int r, int x, int y, db v) {
		if(x <= l && r <= y) {
			addpnt(o, v);
			return ;
		}
		psd(o);
		int m = (l + r) >> 1;
		if(x <= m)
			addrange(ls, l, m, x, y, v);
		if(y > m)
			addrange(rs, m+1, r, x, y, v);
		e[o].upd(e[ls], e[rs]);
	}
	Node qryrange(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y) 
			return e[o];
		psd(o);
		int m = (l + r) >> 1;
		if(y <= m)
			return qryrange(ls, l, m, x, y);
		else if(x > m)
			return qryrange(rs, m+1, r, x, y);
		else {
			Node ret;
			ret.upd(qryrange(ls, l, m, x, m), qryrange(rs, m+1, r, m+1, y));
			return ret;
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
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n, a);
	cin >> m;
	for(int i = 1; i <= m; i++) {
		int op;
		cin >> op;
		if(op == 1) {
			int l, r;
			db v;
			cin >> l >> r >> v;
			addrange(1, 1, n, l, r, v);
		} else {
			int l, r;
			cin >> l >> r;
			cout << fixed << setprecision(1) << qryrange(1, 1, n, l, r).ssin << '\n';
		}
	}
	return 0;
}
