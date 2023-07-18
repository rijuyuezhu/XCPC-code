#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
constexpr int MAXN = 2e5 + 5;
constexpr ll LINF = 1e18;
int n, m;
ll a[MAXN];

void trans(int x, ll v);

namespace Sgt1 {
#define ls o << 1
#define rs o << 1 | 1
	ll sum[MAXN << 2], sz[MAXN << 2], tag[MAXN << 2], flg[MAXN << 2];
	void pushup(int o) {
		sum[o] = sum[ls] + sum[rs];
		sz[o] = sz[ls] + sz[rs];
	}
	void build(int o, int l, int r) {
		tag[o] = 0; flg[o] = 1;
		if (l == r) {
			sum[o] = 0;
			sz[o] = 0;
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m);
		build(rs, m+1, r);
		pushup(o);
	}
	void flpoint(int o, ll fl) {
		sum[o] *= fl;
		tag[o] *= fl;
		flg[o] *= fl;
	}
	void tgpoint(int o, ll tg) {
		sum[o] += sz[o] * tg;
		tag[o] += tg;
	}
	void pushdown(int o) {
		if (flg[o] != 1) {
			flpoint(ls, flg[o]);
			flpoint(rs, flg[o]);
			flg[o] = 1;
		}
		if (tag[o] != 0) {
			tgpoint(ls, tag[o]);
			tgpoint(rs, tag[o]);
			tag[o] = 0;
		}
	}
	ll sumrange(int o, int l, int r, int x, int y) {
		if (x <= l && r <= y)
			return sum[o];
		pushdown(o);
		int m = (l + r) >> 1;
		if (y <= m)
			return sumrange(ls, l, m, x, y);
		else if (x > m)
			return sumrange(rs, m+1, r, x, y);
		else
			return sumrange(ls, l, m, x, m) + sumrange(rs, m+1, r, m+1, y);
	}
	void updrange(int o, int l, int r, int x, int y, ll v) {
		if (x <= l && r <= y) {
			flpoint(o, -1);
			tgpoint(o, v);
			return ;
		}
		pushdown(o);
		int m = (l + r) >> 1;
		if (x <= m)
			updrange(ls, l, m, x, y, v);
		if (y > m)
			updrange(rs, m+1, r, x, y, v);
		pushup(o);
	}
	void insert(int o, int l, int r, int x, ll v) {
		if (l == r) {
			sum[o] = v;
			sz[o] = 1;
			return ;
		}
		pushdown(o);
		int m = (l + r) >> 1;
		if (x <= m)
			insert(ls, l, m, x, v);
		else 
			insert(rs, m+1, r, x, v);
		pushup(o);
	}
	void print(int o, int l, int r) {
		if (l == r) {
			cout << sum[o] << ' ';
			return;
		}
		pushdown(o);
		int m = (l + r) >> 1;
		print(ls, l, m);
		print(rs, m+1, r);
	}

#undef ls
#undef rs
}
namespace Sgt2 {
#define ls o << 1
#define rs o << 1 | 1
	ll mn[MAXN << 2], sum[MAXN << 2], sz[MAXN << 2], tag[MAXN << 2];
	void pushup(int o) {
		mn[o] = min(mn[ls], mn[rs]);
		sum[o] = sum[ls] + sum[rs];
		sz[o] = sz[ls] + sz[rs];
	}
	void build(int o, int l, int r, ll a[]) {
		tag[o] = 0;
		if (l == r) {
			mn[o] = a[l];
			sum[o] = a[l];
			sz[o] = 1;
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, a);
		build(rs, m+1, r, a);
		pushup(o);
	}
	void updpoint(int o, ll tg) {
		sum[o] -= tg * sz[o];
		if (mn[o] != LINF)
			mn[o] -= tg;
		tag[o] += tg;
	}
	void pushdown(int o) {
		if (tag[o]) {
			updpoint(ls, tag[o]);
			updpoint(rs, tag[o]);
			tag[o] = 0;
		}
	}
	void remove(int o, int l, int r, ll ori) {
		if (mn[o] >= 0)
			return;
		if (l == r) {
			trans(l, sum[o]+ori);
			sum[o] = 0;
			mn[o] = LINF;
			sz[o] = 0;
			return;
		}
		pushdown(o);
		int m = (l + r) >> 1;
		remove(ls, l, m, ori);
		remove(rs, m+1, r, ori);
		pushup(o);
	}
	ll sumrange(int o, int l, int r, int x, int y) {
		if (x <= l && r <= y)
			return sum[o];
		pushdown(o);
		int m = (l + r) >> 1;
		if (y <= m)
			return sumrange(ls, l, m, x, y);
		else if (x > m)
			return sumrange(rs, m+1, r, x, y);
		else
			return sumrange(ls, l, m, x, m) + sumrange(rs, m+1, r, m+1, y);
	}
	void updrange(int o, int l, int r, int x, int y, ll v) {
		if (x <= l && r <= y) {
			updpoint(o, v);
			return ;
		}
		pushdown(o);
		int m = (l + r) >> 1;
		if (x <= m)
			updrange(ls, l, m, x, y, v);
		if (y > m)
			updrange(rs, m+1, r, x, y, v);
		pushup(o);
	}
	void print(int o, int l, int r) {
		if (l == r) {
			cout << sum[o] << ' ';
			return;
		}
		pushdown(o);
		int m = (l + r) >> 1;
		print(ls, l, m);
		print(rs, m+1, r);
	}
	
#undef ls
#undef rs
}

void trans(int x, ll v) {
	Sgt1::insert(1, 1, n, x, v);
}
void work() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	Sgt1::build(1, 1, n);
	Sgt2::build(1, 1, n, a);
	for (int i = 1; i <= m; i++) {
		int opt = read(), l = read(), r = read(); ll x;
		if (opt == 1) {
			x = read();
			Sgt2::updrange(1, 1, n, l, r, x);
			Sgt2::remove(1, 1, n, x);
			Sgt1::updrange(1, 1, n, l, r, x);
		} else {
			printf("%lld\n", Sgt1::sumrange(1, 1, n, l, r) + Sgt2::sumrange(1, 1, n, l, r));
		}
	}

}

int main() {
	int T = read();
	while (T--)
		work();
	return 0;
}
