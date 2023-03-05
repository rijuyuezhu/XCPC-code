#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5;
int n, q;
ll a[MAXN];
namespace Sgt {
#define ls p << 1
#define rs p << 1 | 1
	const int MAXNODE = MAXN << 2;
	struct Node {
		ll sum, mn, mx;
		ll tag;
		void merge(const Node& a, const Node& b) {
			sum = a.sum + b.sum;
			mn = min(a.mn, b.mn);
			mx = max(a.mx, b.mx);
		}
	}e[MAXNODE];
	void build(int p, int l, int r) {
		e[p].tag = 0;
		if(l == r) {
			e[p].sum = e[p].mn = e[p].mx = a[l];
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m); build(rs, m+1, r);
		e[p].merge(e[ls], e[rs]);
	}
	void psdtag(int p, int l, int r, ll k) {
		e[p].tag += k; e[p].sum += (r-l+1) * k; e[p].mn += k; e[p].mx += k;
	}
	void psd(int p, int l, int r) {
		int m = (l + r) >> 1;
		if(e[p].tag) {
			psdtag(ls, l, m, e[p].tag);
			psdtag(rs, m+1, r, e[p].tag);
			e[p].tag = 0;
		}
	}
	void addrange(int p, int l, int r, int x, int y, ll k) {
		if(x <= l && r <= y) {
			psdtag(p, l, r, k);
			return ;
		}
		psd(p, l, r);
		int m = (l + r) >> 1;
		if(x <= m) addrange(ls, l, m, x, y, k);
		if(y > m) addrange(rs, m+1, r, x, y, k);
		e[p].merge(e[ls], e[rs]);
	}
	int getdiv(ll v, ll k) {
		if(v >= 0) return v / k;
		else {
			return v % k ? v / k - 1 : v / k;
		}
	}
	void divrange(int p, int l, int r, int x, int y, ll k) {
		if(x <= l && r <= y) {
			if(getdiv(e[p].mx, k) - e[p].mx == getdiv(e[p].mn, k) - e[p].mn) {
				psdtag(p, l, r, getdiv(e[p].mx, k) - e[p].mx);
				return;
			}
		}
		psd(p, l, r);
		int m = (l + r) >> 1;
		if(x <= m) divrange(ls, l, m, x, y, k);
		if(y > m) divrange(rs, m+1, r, x, y, k);
		e[p].merge(e[ls], e[rs]);
	}
	Node query(int p, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[p];
		psd(p, l, r);
		int m = (l + r) >> 1;
		if(y <= m) return query(ls, l, m, x, y);
		else if(x > m) return query(rs, m+1, r, x, y);
		else {
			Node ans;
			ans.merge(query(ls, l, m, x, m), query(rs, m+1, r, m+1, y));
			return ans;
		}
	}
#undef ls
#undef rs
}
using namespace Sgt;
int main() {
	n = read(), q = read();
	for(int i = 0; i < n; i++) a[i] = read();
	build(1, 0, n-1);
	for(int i = 1; i <= q; i++) {
		int k = read(), l = read(), r = read();
		if(k == 1) {
			int c = read();
			addrange(1, 0, n-1, l, r, c);
		} else if(k == 2) {
			int d = read();
			divrange(1, 0, n-1, l, r, d);
		} else {
			Node t = query(1, 0, n-1, l, r);
			printf("%lld\n", k == 3 ? t.mn : t.sum);
		}
	}
	return 0;
}
