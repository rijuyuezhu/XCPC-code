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
const int MAXN = 1e6 + 5, MAXM = 1e6 + 5;
int n, m;
int a[MAXN];
namespace Segment_tree {
#define L e[o].ls
#define R e[o].rs
	const int MAXNODE = MAXN << 4;
	struct Node {
		int ls, rs, val;
	}e[MAXNODE];
	int tot;
	void build(int &o, int l, int r, int a[]) {
		o = ++tot;
		if(l == r) {e[o].val = a[l]; return ;}
		int m = (l + r) >> 1; build(L, l, m, a); build(R, m+1, r, a);
	}
	void update(int &o, int pre, int l, int r, int x, int val) {
		o = ++tot; e[o] = e[pre];
		if(l == r) {e[o].val = val; return ;}
		int m = (l + r) >> 1; 
		if(x <= m) update(L, e[pre].ls, l, m, x, val);
		else update(R, e[pre].rs, m+1, r, x, val);
	}
	int query(int o, int l, int r, int x) {
		if(l == r) return e[o].val;
		int m = (l + r) >> 1;
		if(x <= m) return query(L, l, m, x);
		else return query(R, m+1, r, x);
	}

#undef L
#undef R
}
using namespace Segment_tree;
int rt[MAXN];
void init() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
}
void solve() {
	build(rt[0], 1, n, a);
	for(int i = 1; i <= m; i++) {
		int v = read(), opt = read(), l = read();
		if(opt == 1) {
			int val = read();
			update(rt[i], rt[v], 1, n, l, val);
		} else {
			printf("%d\n", query(rt[v], 1, n, l));
			rt[i] = rt[v];
		}
	}
}
int main() {
	init();
	solve();
	return 0;
}
