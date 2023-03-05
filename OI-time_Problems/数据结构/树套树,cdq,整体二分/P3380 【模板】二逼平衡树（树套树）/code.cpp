#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
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
const int MAXN = 5e4 + 5;
namespace Treap {
	const int MAXNODE = 3e6 + 5;
	struct Node{int ls, rs, c, s, k, v;}e[MAXNODE];
	int tot;
	void upd(int p) {e[p].s = e[e[p].ls].s + e[e[p].rs].s + e[p].c;}
	void lturn(int& p) {int s = e[p].rs; e[p].rs = e[s].ls; upd(p); e[s].ls = p; upd(p = s);}
	void rturn(int& p) {int s = e[p].ls; e[p].ls = e[s].rs; upd(p); e[s].rs = p; upd(p = s);}
	void ins(int& p, int v) {
		if(!p) e[p = ++tot] = (Node){0, 0, 1, 1, rand(), v};
		else if(e[p].v == v) e[p].c++, upd(p);
		else if(e[p].v > v)
			ins(e[p].ls, v), e[e[p].ls].k < e[p].k ? rturn(p) : upd(p);
		else 
			ins(e[p].rs, v), e[e[p].rs].k > e[p].k ? lturn(p) : upd(p);
	}
	void del(int& p, int v) {
		if(!p) return;
		else if(e[p].v > v) del(e[p].ls, v), upd(p);
		else if(e[p].v < v) del(e[p].rs, v), upd(p);
		else if(e[p].c > 1) e[p].c--, upd(p);
		else if(!e[p].ls) p = e[p].rs;
		else if(!e[p].rs) p = e[p].ls;
		else if(e[e[p].ls].k < e[e[p].rs].k)
			rturn(p), del(e[p].rs, v), upd(p);
		else 
			lturn(p), del(e[p].ls, v), upd(p);
	}
	int bef(int p, int v) {
		if(!p) return 0;
		else if(e[p].v == v) return e[e[p].ls].s;
		else if(e[p].v > v) return bef(e[p].ls, v);
		else return bef(e[p].rs, v) + e[e[p].ls].s + e[p].c;
	}
	int pre(int p, int v) {
		int ans = -2147483647;
		while(p) {
			if(e[p].v < v) {ans = max(ans, e[p].v); p = e[p].rs;}
			else p = e[p].ls;
		}
		return ans;
	}
	int nxt(int p, int v) {
		int ans = 2147483647;
		while(p) {
			if(e[p].v > v) {ans = min(ans, e[p].v); p = e[p].ls;}
			else p = e[p].rs;
		}
		return ans;
	}
}
namespace Sgt {
#define ls p << 1
#define rs p << 1 | 1
	int rt[MAXN << 2];
	void build(int p, int l, int r, int a[]) {
		for(int i = l; i <= r; i++) Treap :: ins(rt[p], a[i]);
		if(l == r) return;
		int m = (l + r) >> 1;
		build(ls, l, m, a); build(rs, m+1, r, a);
	}
	int bef(int p, int l, int r, int x, int y, int v) {
		if(x <= l && r <= y) return Treap :: bef(rt[p], v);
		int m = (l + r) >> 1;
		if(y <= m) return bef(ls, l, m, x, y, v);
		else if(x > m) return bef(rs, m+1, r, x, y, v);
		else return bef(ls, l, m, x, m, v) + bef(rs, m+1, r, m+1, y, v);
	}
	void mdy(int p, int l, int r, int x, int fr, int to) {
		Treap :: del(rt[p], fr); Treap :: ins(rt[p], to);
		if(l == r) return ;
		int m = (l + r) >> 1;
		if(x <= m) mdy(ls, l, m, x, fr, to);
		else mdy(rs, m+1, r, x, fr, to);
	}
	int pre(int p, int l, int r, int x, int y, int v) {
		if(x <= l && r <= y) return Treap :: pre(rt[p], v);
		int m = (l + r) >> 1;
		if(y <= m) return pre(ls, l, m, x, y, v);
		else if(x > m) return pre(rs, m+1, r, x, y, v);
		else return max(pre(ls, l, m, x, m, v), pre(rs, m+1, r, m+1, y, v));
	}
	int nxt(int p, int l, int r, int x, int y, int v) {
		if(x <= l && r <= y) return Treap :: nxt(rt[p], v);
		int m = (l + r) >> 1;
		if(y <= m) return nxt(ls, l, m, x, y, v);
		else if(x > m) return nxt(rs, m+1, r, x, y, v);
		else return min(nxt(ls, l, m, x, m, v), nxt(rs, m+1, r, m+1, y, v));
	}
#undef ls
#undef rs
}
int n, m;
int a[MAXN];
int main() {
	srand(time(0));
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	Sgt :: build(1, 1, n, a);
	for(int i = 1; i <= m; i++) {
		int opt = read();
		if(opt == 1) {
			int l = read(), r = read(), v = read();
			printf("%d\n", Sgt :: bef(1, 1, n, l, r, v) + 1);
		} else if(opt == 2) {
			int l = read(), r = read(), k = read();
			int ans = 0, L = 0, R = 1e8;
			while(L <= R) {
				int m = (L + R) >> 1;
				if(Sgt :: bef(1, 1, n, l, r, m) + 1 <= k) {ans = m; L = m+1;}
				else R = m-1;
			}
			printf("%d\n", ans);
		} else if(opt == 3) {
			int pos = read(), k = read();
			Sgt :: mdy(1, 1, n, pos, a[pos], k); a[pos] = k;
		} else if(opt == 4) {
			int l = read(), r = read(), v = read();
			printf("%d\n", Sgt :: pre(1, 1, n, l, r, v));
		} else {
			int l = read(), r = read(), v = read();
			printf("%d\n", Sgt :: nxt(1, 1, n, l, r, v));
		}
	}
	return 0;
}
