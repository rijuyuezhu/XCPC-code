#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;
const int MAXV = 40005;
const db eps = 1e-9;
int n, cnt;
struct Line {db k, b;}t[MAXN];
db f(int i, db x) {return t[i].k * x + t[i].b;}
bool bt(int a, int b, db x) {
	if(fabs(f(a, x) - f(b, x)) > eps) return f(a, x) > f(b, x);
	return a < b;
}
namespace Sgt {
#define ls o << 1
#define rs o << 1 | 1
	int mn[MAXV << 2];
	void ins(int o, int l, int r, int x, int y, int k) {
		if(x <= l && r <= y) {
			if(bt(k, mn[o], l) && bt(k, mn[o], r)) {mn[o] = k; return ;}
			if(bt(mn[o], k, l) && bt(mn[o], k, r)) return ;
			int m = (l + r) >> 1;
			if(bt(k, mn[o], m)) swap(k, mn[o]);
			if(bt(k, mn[o], l)) ins(ls, l, m, x, y, k);
			else ins(rs, m+1, r, x, y, k);
			return ;
		}
		int m = (l + r) >> 1;
		if(x <= m) ins(ls, l, m, x, y, k);
		if(y > m) ins(rs, m+1, r, x, y, k);
	}
	int qry(int o, int l, int r, int x) {
		if(l == r) return mn[o];
		int m = (l + r) >> 1;
		int ret = x <= m ? qry(ls, l, m, x) : qry(rs, m+1, r, x);
		if(bt(mn[o], ret, x)) ret = mn[o];
		return ret;
	}
#undef ls
#undef rs
}
using namespace Sgt;
int ans;
int main() {
	t[0] = (Line){0, -INF};
	n = read();
	for(int i = 1; i <= n; i++) {
		int opt = read();
		if(opt == 0) {
			int k = (read() + ans - 1) % 39989 + 1;
			printf("%d\n", ans = qry(1, 1, 39989, k));
		} else {
			int x0 = (read() + ans - 1) % 39989 + 1, y0 = (read() + ans - 1) % 1000000000 + 1;
			int x1 = (read() + ans - 1) % 39989 + 1, y1 = (read() + ans - 1) % 1000000000 + 1;
			if(x0 == x1) {
				t[++cnt] = (Line){0, (db)max(y0, y1)};
			} else {
				t[++cnt] = (Line){db(y0 - y1) / (x0 - x1), db(1ll * x0 * y1 - 1ll * x1 * y0) / (x0 - x1)};
			}
			if(x0 > x1) swap(x0, x1);
			ins(1, 1, 39989, x0, x1, cnt);
		}
	}
	return 0;
}
