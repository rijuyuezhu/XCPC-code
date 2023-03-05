#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e4 + 5;
int n, m;
namespace SgtP {
	const int MAXNODE = 2e7 + 5;
	struct Node {
		int ls, rs;
		ll v, a;
	}e[MAXNODE];
	int tot;
	void upd(int p, int l, int r) {e[p].v = e[e[p].ls].v + e[e[p].rs].v + (r-l+1) * e[p].a;}
	void addrange(int& p, int l, int r, int x, int y) {
		if(!p) p = ++tot;
		if(x == l && r == y) {
			e[p].v += (r-l+1); e[p].a++;
			return;
		}
		int m = (l + r) >> 1;
		if(y <= m) addrange(e[p].ls, l, m, x, y);
		else if(x > m) addrange(e[p].rs, m+1, r, x, y);
		else addrange(e[p].ls, l, m, x, m), addrange(e[p].rs, m+1, r, m+1, y);
		upd(p, l, r);
	}
	ll query(int p, int l, int r, int x, int y) {
		if(!p) return 0;
		if(x == l && r == y) return e[p].v;
		int m = (l + r) >> 1; ll ans = (y-x+1) * e[p].a;
		if(y <= m) return query(e[p].ls, l, m, x, y) + ans;
		else if(x > m) return query(e[p].rs, m+1, r, x, y) + ans;
		else return query(e[p].ls, l, m, x, m) + query(e[p].rs, m+1, r, m+1, y) + ans;
	}
}
namespace SgtV {
#define ls p << 1
#define rs p << 1 | 1
	int rt[MAXN << 2];
	void addpnt(int p, int l, int r, int x, int L, int R) {
		SgtP::addrange(rt[p], 1, n, L, R);
		if(l == r) return;
		int m = (l + r) >> 1;
		if(x <= m) addpnt(ls, l, m, x, L, R);
		else addpnt(rs, m+1, r, x, L, R);
	}
	int query(int p, int l, int r, int L, int R, ll k) {
		if(l == r) return l;
		int m = (l + r) >> 1;
		ll rsz = SgtP::query(rt[rs], 1, n, L, R);
		if(k <= rsz) return query(rs, m+1, r, L, R, k);
		else return query(ls, l, m, L, R, k - rsz);
	}
#undef ls
#undef rs
}
int lsh[MAXN], _lsh;
struct Opt {
	int op, l, r; ll c;
}opt[MAXN];

int main() {
	srand(time(0));
	n = read(), m = read();
	for(int i = 1; i <= m; i++) {
		opt[i].op = read(); opt[i].l = read(); opt[i].r = read(); opt[i].c = read();
		if(opt[i].op == 1) lsh[++_lsh] = opt[i].c;
	}
	sort(lsh + 1, lsh + 1 + _lsh); _lsh = unique(lsh + 1, lsh + 1 + _lsh) - lsh - 1;
	for(int i = 1; i <= m; i++) {
		if(opt[i].op == 1) {
			int c = lower_bound(lsh + 1, lsh + 1 + _lsh, opt[i].c) - lsh;
			SgtV::addpnt(1, 1, _lsh, c, opt[i].l, opt[i].r);
		}
		else printf("%d\n", lsh[SgtV::query(1, 1, _lsh, opt[i].l, opt[i].r, opt[i].c)]);
	}
	return 0;
}
