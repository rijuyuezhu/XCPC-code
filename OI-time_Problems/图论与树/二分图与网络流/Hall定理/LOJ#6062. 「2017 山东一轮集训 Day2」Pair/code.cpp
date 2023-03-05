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
const int MAXN = 2e5 + 5;
int n, m, h, b[MAXN], a[MAXN], c[MAXN], ans;
namespace Sgt {
#define ls p << 1
#define rs p << 1 | 1
	const int MAXNODE = MAXN << 2;
	struct Node {
		int val, tag;
	}e[MAXNODE];
	void upd(int p) {e[p].val = min(e[ls].val, e[rs].val);}
	void psda(int p, int k) {
		e[p].val += k; e[p].tag += k;
	}
	void psd(int p) {
		if(e[p].tag) {
			psda(ls, e[p].tag);
			psda(rs, e[p].tag);
			e[p].tag = 0;
		}
	}
	void build(int p, int l, int r) {
		e[p].tag = 0;
		if(l == r) {
			e[p].val = l;
			return ;
		}
		int m = (l + r) >> 1;
		build(ls, l, m); build(rs, m+1, r);
		upd(p);
	}
	void addrange(int p, int l, int r, int x, int y, int k) {
		if(x <= l && r <= y) {
			psda(p, k);
			return ;
		}
		psd(p);
		int m = (l + r) >> 1;
		if(x <= m) addrange(ls, l, m, x, y, k);
		if(y > m) addrange(rs, m+1, r, x, y, k);
		upd(p);
	}
#undef ls
#undef rs
}
using namespace Sgt;
int main() {
	n = read(), m = read(), h = read();
	for(int i = 1; i <= m; i++) b[i] = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	sort(b + 1, b + 1 + m);
	for(int i = 1; i <= n; i++) {
		c[i] = m+1;
		int l = 1, r = m;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(a[i] + b[mid] >= h) c[i] = mid, r = mid - 1;
			else l = mid + 1;
		}
	}
	build(1, 0, m);
	for(int i = 1; i <= n; i++) {
		addrange(1, 0, m, m - c[i] + 1, m, -1);
		if(i > m) addrange(1, 0, m, m - c[i-m] + 1, m, 1);
		if(i >= m && e[1].val >= 0) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
