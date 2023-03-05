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
const int MAXN = 5e5 + 5;
const int P = 1e9 + 21;
const int inv6 = 833333351;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}

namespace Segment_tree {
#define ls o << 1
#define rs o << 1 | 1
	struct Node {
		int mx, mn, hs;
		Node(int v = 0) {
			mx = mn = v; hs = mul(v, v);
		}
		void merge(const Node& a, const Node& b) {
			mx = max(a.mx, b.mx); mn = min(a.mn, b.mn); hs = pls(a.hs, b.hs);
		}
	}e[MAXN << 2];
	void build(int o, int l, int r, int a[]) {
		if(l == r) {e[o] = Node(a[l]); return;}
		int m = (l + r) >> 1;
		build(ls, l, m, a); build(rs, m+1, r, a);
		e[o].merge(e[ls], e[rs]);
	}
	void mdypoint(int o, int l, int r, int x, int v) {
		if(l == r) {e[o] = Node(v); return;}
		int m = (l + r) >> 1;
		if(x <= m) mdypoint(ls, l, m, x, v);
		else mdypoint(rs, m+1, r, x, v);
		e[o].merge(e[ls], e[rs]);
	}
	Node query(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[o];
		int m = (l + r) >> 1;
		if(y <= m) return query(ls, l, m, x, y);
		else if(x > m) return query(rs, m+1, r, x, y);
		else {
			Node ans;
			ans.merge(query(ls, l, m, x, y), query(rs, m+1, r, x, y));
			return ans;
		}
	}
#undef ls
#undef rs
}
using namespace Segment_tree;
int n, m;
int a[MAXN];
int si2(int t) {
	return 1ll * t * (t + 1) % P * (2 * t + 1) % P * inv6 % P;
}
bool check(int l, int r) {
	Node t = query(1, 1, n, l, r);
	return (t.mx - t.mn + 1 == r - l + 1) && (t.hs == mns(si2(t.mx), si2(t.mn-1)));
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	build(1, 1, n, a);
	for(int i = 1; i <= m; i++) {
		int opt = read(), x = read(), y = read();
		if(opt == 1) {
			mdypoint(1, 1, n, x, y);
		} else {
			if(check(x, y)) printf("damushen\n");
			else printf("yuanxing\n");
		}
	}
	return 0;
}
